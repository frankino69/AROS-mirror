/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2006 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/
#include "SDL_config.h"

/* Handle the event stream, converting Amiga events into SDL events */
#include "SDL.h"

#include "SDL_syswm.h"
#include "../SDL_sysvideo.h"
#include "../../events/SDL_sysevents.h"
#include "../../events/SDL_events_c.h"
#include "SDL_cgxvideo.h"
#include "SDL_cgxmodes_c.h"
#include "SDL_cgximage_c.h"
#include "SDL_cgxwm_c.h"
#include "SDL_cgxmouse_c.h"
#include "SDL_cgxevents_c.h"


/* The translation tables from an Amiga keysym to a SDL keysym */
static SDLKey 		MISC_keymap[256];

struct IOStdReq*	SDL_ConReq=NULL;
struct MsgPort*		SDL_ConPort=NULL;

SDL_keysym *CGX_TranslateKey(int code, UWORD qualifier, SDL_keysym *keysym)
{
	struct InputEvent event;
	long actual;
	char buffer[5];

	static struct Device *ConsoleDevice=NULL;

	/* Get the raw keyboard scancode */
	keysym->scancode = code;
	keysym->sym = MISC_keymap[code];

	if(!ConsoleDevice)
	{
		if((SDL_ConPort=CreateMsgPort()))
		{
			if((SDL_ConReq=CreateIORequest(SDL_ConPort,sizeof(struct IOStdReq))))
			{
				if(!OpenDevice("console.device",-1,(struct IORequest *)SDL_ConReq,0))
					ConsoleDevice=(struct Device *)SDL_ConReq->io_Device;
				else
				{
					DeleteIORequest(SDL_ConReq);
					SDL_ConReq=NULL;
				}
			}
			else
			{
				DeleteMsgPort(SDL_ConPort);
				SDL_ConPort=NULL;
			}
		}
	}
	/* Get the translated SDL virtual keysym */
	if ( keysym->sym==SDLK_UNKNOWN )
	{
		if(ConsoleDevice)
		{
			event.ie_Qualifier=0;
			event.ie_Class=IECLASS_RAWKEY;
			event.ie_SubClass=0L;
			event.ie_Code=code & ~(IECODE_UP_PREFIX);
			event.ie_X=event.ie_Y=0;
			event.ie_EventAddress=NULL;
			event.ie_NextEvent=NULL;
			event.ie_Prev1DownCode=event.ie_Prev1DownQual=event.ie_Prev2DownCode=event.ie_Prev2DownQual=0;

			if( (actual=RawKeyConvert(&event,buffer,5,NULL))==1)
			{
				keysym->sym = (buffer[0] & 0xFF);
				D(bug("Converted rawcode %ld to <%lc>\n",code,*buffer));
				// Buffering for successive calls
				MISC_keymap[code]= (buffer[0] & 0xFF);
			}
			else D(bug("Warning (%ld) character conversion!\n",actual));
		}

	}
	keysym->mod = KMOD_NONE;

	/* If UNICODE is on, get the UNICODE value for the key */
	/*Bad hack, only ascii values are returned, RawKeyConvert doesn't return unicode or? */
	keysym->unicode = 0;
	if ( SDL_TranslateUNICODE )
	{
		if(ConsoleDevice)
		{
			event.ie_Class = IECLASS_RAWKEY;
			event.ie_SubClass = 0;
			event.ie_Code  = code & ~(IECODE_UP_PREFIX);
			event.ie_Qualifier = qualifier;
			event.ie_EventAddress = NULL;

			actual = RawKeyConvert(&event, buffer, 5, 0);
			
			if ((actual == 1) && (keysym->sym!=SDLK_UNKNOWN)) keysym->unicode = (buffer[0] & 0xFF);
		}
	}
	return(keysym);
}

static int CGX_GetButton(int code)
{
	switch(code)
	{
		case IECODE_MBUTTON:
			return SDL_BUTTON_MIDDLE;
		case IECODE_RBUTTON:
			return SDL_BUTTON_RIGHT;
		default:
			return SDL_BUTTON_LEFT;
	}
}

static int CGX_FocusActivate(_THIS, BOOL activate)
{
	int posted = 0;
	int val = activate ? 1 : 0;

	posted = SDL_PrivateAppActive(val, SDL_APPMOUSEFOCUS);
	posted |= SDL_PrivateAppActive(val, SDL_APPINPUTFOCUS);
	this->hidden->FocusActive = val;

	return posted;
}

static int CGX_IsMouseInsideDrawArea(int mouseX, int mouseY, struct Window * wnd)
{
	if ((mouseX < (wnd->BorderLeft)) ||
		(mouseX > (wnd->Width - wnd->BorderRight)))
		return 0;
	if ((mouseY < (wnd->BorderTop)) ||
		(mouseY > (wnd->Height - wnd->BorderBottom)))
		return 0;
		
	return 1;
}

/* 
 * FocusActive handling:
 *   How to loose focus:
 *     - If !GrabMouse and WindowActive and Exit window drawing area
 *     - ALT + TAB = IDCMP_IACTIVEWINDOW
 *   How to gain focus:
 *     - If WindowActive and Enter window drawing area and !ExplicitFocusActivation
 *     - Open SDL_FULLSCREEN mode (indirect via clearing ExplicitFocusFlag)
 *     - If ExplicitFocusActivation and Click in window drawing area
 */
static int CGX_DispatchEvent(_THIS, struct IntuiMessage *msg)
{
	int class=msg->Class,code=msg->Code;
	int posted;

	posted = 0;
	switch (class) {
	    /* Gaining app & mouse focus */
	    case IDCMP_ACTIVEWINDOW:
			this->hidden->WindowActive = 1;
			break;

	    /* Loosing app & mouse focus */
	    case IDCMP_INACTIVEWINDOW:
	    	/* If mouse is grabbed, request explicit activation */
	    	if (this->hidden->GrabMouse)
	    		this->hidden->ExplicitFocusActivation = 1;
			posted = CGX_FocusActivate(this, FALSE);
			this->hidden->WindowActive = 0;
			break;

	    /* Mouse motion */
	    case IDCMP_MOUSEMOVE:
			if ( SDL_VideoSurface )
			{
				int new_x, new_y, dx = 0, dy = 0;
				
				if (currently_fullscreen)
				{
					/* Center display on screen */
					dx = (SDL_Display->Width - this->screen->w)/2;
					dy = (SDL_Display->Height - this->screen->h)/2;
				}
				
				/* Check for activation/deactivation of App */
				if (this->hidden->WindowActive)
				{
					/* Exit only if not grabbed */
					if (this->hidden->FocusActive && !this->hidden->GrabMouse &&
						!CGX_IsMouseInsideDrawArea(msg->MouseX, msg->MouseY, SDL_Window))
						posted |= CGX_FocusActivate(this, FALSE);

					/* Enter only if not explicit focus activation needed */
					if (!this->hidden->FocusActive && !this->hidden->ExplicitFocusActivation &&
						CGX_IsMouseInsideDrawArea(msg->MouseX, msg->MouseY, SDL_Window))
						posted |= CGX_FocusActivate(this, TRUE);
				}

				/* These are coords "inside" AROS window (without borders) */
				new_x = msg->MouseX - SDL_Window->BorderLeft;
				new_y = msg->MouseY - SDL_Window->BorderTop;

				if (this->hidden->FocusActive && this->hidden->GrabMouse)
				{
					if (!this->hidden->CursorVisible)
					{
						/* This is a special case in SDL documentation. When
						   GrabMouse and !CursonVisible, always post relative
						   move events. Always warp to center of screen. */
						int center_x = this->screen->w / 2;
						int center_y = this->screen->h / 2;

						if ((new_x == center_x) && (new_y == center_y))
						{
							/* Do nothing - this is a signal generated by warp call. */
						}
						else
						{
							int rel_x = msg->MouseX - this->hidden->LastMouseX;
							int rel_y = msg->MouseY - this->hidden->LastMouseY;

							/* 	Workaround:
							 * 	Send "recall" event only when cursor leaves 1/2 of inner area
							 	of window. Sending the event each mouse event casues an increasing
							 	stall with DoIO call. The root cause of this stall is unknown.
							 	The workaround seems to avoid the stall. */
							if ((new_x < center_x / 2) || (new_x > (center_x * 3 / 2)) ||
								(new_y < center_y / 2) || (new_y > (center_y * 3 / 2)))
								CGX_WarpWMCursor(this, center_x, center_y);
							posted |= SDL_PrivateMouseMotion(0, 1, rel_x, rel_y);
						}
					}
					else
					{
						BOOL dowarp = FALSE;
									
						if (new_x - dx  < 0)
						{
							dowarp = TRUE;
							new_x = dx;
						}
						else if (new_x - dx > this->screen->w - 1)
						{
							dowarp = TRUE;
							new_x = dx + this->screen->w - 1;
						}
					
						if (new_y - dy < 0)
						{
							dowarp = TRUE;
							new_y = 0;
						}
						else if (new_y - dy > this->screen->h - 1)
						{
							dowarp = TRUE;
							new_y = dy + this->screen->h - 1;
						}

						if (dowarp) CGX_WarpWMCursor(this, new_x, new_y);
						posted |= SDL_PrivateMouseMotion(0, 0, new_x - dx, new_y - dy);
					}
				}
				else
					posted |= SDL_PrivateMouseMotion(0, 0, new_x - dx, new_y - dy);

				this->hidden->LastMouseX = msg->MouseX;
				this->hidden->LastMouseY = msg->MouseY;
			}
	    	break;

	    
		case IDCMP_MOUSEBUTTONS:
			/* Mouse button press? */
			if(!(code&IECODE_UP_PREFIX))
			{
				/* Explicit focus activation case */
				if (this->hidden->ExplicitFocusActivation && 
					CGX_IsMouseInsideDrawArea(msg->MouseX, msg->MouseY, SDL_Window))
				{
					this->hidden->ExplicitFocusActivation = 0;
					posted |= CGX_FocusActivate(this, TRUE);
				}
				else
				{
					posted |= SDL_PrivateMouseButton(SDL_PRESSED, 
							CGX_GetButton(code), 0, 0);
				}
			}
			/* Mouse button release? */
			else
			{
				code&=~IECODE_UP_PREFIX;
				posted = SDL_PrivateMouseButton(SDL_RELEASED,
						CGX_GetButton(code), 0, 0);
			}
			break;

	    case IDCMP_RAWKEY:
			/* Mouse wheel support */
			if (code == RAWKEY_NM_WHEEL_UP)
			{
				posted = SDL_PrivateMouseButton(SDL_PRESSED,
							SDL_BUTTON_WHEELUP, 0, 0);
				posted |= SDL_PrivateMouseButton(SDL_RELEASED,
							SDL_BUTTON_WHEELUP, 0, 0);
				break;
			}
			
			if (code == RAWKEY_NM_WHEEL_DOWN)
			{
				posted = SDL_PrivateMouseButton(SDL_PRESSED,
							SDL_BUTTON_WHEELDOWN, 0, 0);
				posted |= SDL_PrivateMouseButton(SDL_RELEASED,
							SDL_BUTTON_WHEELDOWN, 0, 0);
				break;
			}

		    if( !(code&IECODE_UP_PREFIX) )
		    {
				/* Key press */
				SDL_keysym keysym;
				posted = SDL_PrivateKeyboard(SDL_PRESSED,
					CGX_TranslateKey(code, msg->Qualifier, &keysym));
		    }
		    else
		    {
				/* Key release */
				SDL_keysym keysym;
				code&=~IECODE_UP_PREFIX;
				posted = SDL_PrivateKeyboard(SDL_RELEASED,
					CGX_TranslateKey(code, msg->Qualifier, &keysym));
		    }
		    break;

	    /* Have we been resized? */
	    case IDCMP_NEWSIZE:
			SDL_PrivateResize(SDL_Window->Width-SDL_Window->BorderLeft-SDL_Window->BorderRight,
		                  SDL_Window->Height-SDL_Window->BorderTop-SDL_Window->BorderBottom);

			break;

	    /* Have we been requested to quit? */
	    case IDCMP_CLOSEWINDOW:
			posted = SDL_PrivateQuit();
			break;

	    /* Do we need to refresh ourselves? */

	    default: {
			/* Only post the event if we're watching for it */
			if ( SDL_ProcessEvents[SDL_SYSWMEVENT] == SDL_ENABLE ) {
				SDL_SysWMmsg wmmsg;

				SDL_VERSION(&wmmsg.version);

				posted = SDL_PrivateSysWMEvent(&wmmsg);
			}
			}
			break;
	}
	ReplyMsg((struct Message *)msg);

	return(posted);
}

void CGX_PumpEvents(_THIS)
{
	struct IntuiMessage *m;
	
	if (SDL_Window)
		while (( m=(struct IntuiMessage *)GetMsg(SDL_Window->UserPort) )) 
		{
			CGX_DispatchEvent(this, m );
		}
}

void CGX_InitOSKeymap(_THIS)
{
	int i;

	/* Map the miscellaneous keys */
	for ( i=0; i<SDL_arraysize(MISC_keymap); ++i )
		MISC_keymap[i] = SDLK_UNKNOWN;

	MISC_keymap[RAWKEY_BACKSPACE	] = SDLK_BACKSPACE;
	MISC_keymap[RAWKEY_TAB			] = SDLK_TAB;
	MISC_keymap[RAWKEY_DELETE		] = SDLK_DELETE;
	MISC_keymap[RAWKEY_RETURN		] = SDLK_RETURN;
	MISC_keymap[RAWKEY_ESCAPE		] = SDLK_ESCAPE;
	MISC_keymap[RAWKEY_KP_0			] = SDLK_KP0;		/* Keypad 0-9 */
	MISC_keymap[RAWKEY_KP_1			] = SDLK_KP1;
	MISC_keymap[RAWKEY_KP_2			] = SDLK_KP2;
	MISC_keymap[RAWKEY_KP_3			] = SDLK_KP3;
	MISC_keymap[RAWKEY_KP_4			] = SDLK_KP4;
	MISC_keymap[RAWKEY_KP_5			] = SDLK_KP5;
	MISC_keymap[RAWKEY_KP_6			] = SDLK_KP6;
	MISC_keymap[RAWKEY_KP_7			] = SDLK_KP7;
	MISC_keymap[RAWKEY_KP_8			] = SDLK_KP8;
	MISC_keymap[RAWKEY_KP_9			] = SDLK_KP9;
	MISC_keymap[RAWKEY_KP_DECIMAL	] = SDLK_KP_PERIOD;
	MISC_keymap[0x5A				] = SDLK_NUMLOCK;
	MISC_keymap[0x5B				] = SDLK_KP_DIVIDE;
	MISC_keymap[0x5C				] = SDLK_KP_MULTIPLY;
	MISC_keymap[0x5D				] = SDLK_KP_MINUS;
	MISC_keymap[RAWKEY_KP_PLUS		] = SDLK_KP_PLUS;
	MISC_keymap[RAWKEY_KP_ENTER		] = SDLK_KP_ENTER;
	MISC_keymap[RAWKEY_UP			] = SDLK_UP;
	MISC_keymap[RAWKEY_DOWN			] = SDLK_DOWN;
	MISC_keymap[RAWKEY_RIGHT		] = SDLK_RIGHT;
	MISC_keymap[RAWKEY_LEFT			] = SDLK_LEFT;
	MISC_keymap[RAWKEY_PAGEUP		] = SDLK_PAGEUP;
	MISC_keymap[RAWKEY_PAGEDOWN		] = SDLK_PAGEDOWN;
	MISC_keymap[RAWKEY_F1			] = SDLK_F1;
	MISC_keymap[RAWKEY_F2			] = SDLK_F2;
	MISC_keymap[RAWKEY_F3			] = SDLK_F3;
	MISC_keymap[RAWKEY_F4			] = SDLK_F4;
	MISC_keymap[RAWKEY_F5			] = SDLK_F5;
	MISC_keymap[RAWKEY_F6			] = SDLK_F6;
	MISC_keymap[RAWKEY_F7			] = SDLK_F7;
	MISC_keymap[RAWKEY_F8			] = SDLK_F8;
	MISC_keymap[RAWKEY_F9			] = SDLK_F9;
	MISC_keymap[RAWKEY_F10			] = SDLK_F10;
	MISC_keymap[RAWKEY_F11			] = SDLK_F11;		/* F11 is hard mapped to HELP	on AROS */
	MISC_keymap[RAWKEY_F12			] = SDLK_F12;		/* F12 is hard mapped to RSUPER	on AROS */
	MISC_keymap[RAWKEY_CAPSLOCK		] = SDLK_CAPSLOCK;
	MISC_keymap[RAWKEY_RSHIFT		] = SDLK_RSHIFT;
	MISC_keymap[RAWKEY_LSHIFT		] = SDLK_LSHIFT;
	MISC_keymap[RAWKEY_CONTROL		] = SDLK_LCTRL;  	/* There is only one control key on an amiga keyboard! */
	MISC_keymap[RAWKEY_RALT			] = SDLK_RALT;
	MISC_keymap[RAWKEY_LALT			] = SDLK_LALT;
	MISC_keymap[RAWKEY_LAMIGA		] = SDLK_LSUPER; 	/* Left "Windows" i.e "Amiga"*/
	MISC_keymap[RAWKEY_RAMIGA		] = SDLK_RSUPER; 	/* Right "Windows i.e "Amiga"*/
	MISC_keymap[RAWKEY_HELP			] = SDLK_HELP;
	MISC_keymap[RAWKEY_INSERT		] = SDLK_INSERT;
	MISC_keymap[RAWKEY_HOME			] = SDLK_HOME;
	MISC_keymap[RAWKEY_END			] = SDLK_END;
}
