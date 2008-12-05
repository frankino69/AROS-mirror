/****************************************************************
***
*** Main c file for locale
***
*** This file has been generated by Localizer 1.0
***
*****************************************************************/

#include <libraries/locale.h>
#include <proto/locale.h>

static LONG CatVersion = 18.3;

struct LocStr
{
    LONG   ID;
    STRPTR Str;
};

const struct LocStr _MSG_BT_COLLAPSE = {0,"Collapse"};
const struct LocStr _MSG_BT_COLLAPSE_KEY = {1,"e"};
const struct LocStr _MSG_BT_EXPAND = {2,"Expand"};
const struct LocStr _MSG_BT_EXPAND_KEY = {3,"n"};
const struct LocStr _MSG_BT_OPENCOPYRIGHT = {4,"Copyright"};
const struct LocStr _MSG_BT_OPENCOPYRIGHT_KEY = {5,"r"};
const struct LocStr _MSG_BT_OPENSAMPLE = {6,"Sample (b)"};
const struct LocStr _MSG_BT_OPENSAMPLE_KEY = {7,"b"};
const struct LocStr _MSG_CLOSED = {8,"Closed:"};
const struct LocStr _MSG_CLOSED_KEY = {9,"c"};
const struct LocStr _MSG_COPYRIGHT = {10,"Copyright"};
const struct LocStr _MSG_COPYRIGHTTEXT = {11,"\033c\033bNListtree.mcc %s\033n\n\033cCopyright �1999-2000 by Carsten Scholling\nAll rights reserved.\n\n\nFor developer information, bug reports and suggestions please send an email to:\n\n\033c\033bcs@aphaso.de\033n\n\nAlso check out my homepage:\n\033bhttp://www.aphaso.de\n"};
const struct LocStr _MSG_DRAW = {12,"Draw:"};
const struct LocStr _MSG_DRAW_KEY = {13,"d"};
const struct LocStr _MSG_LINES = {14,"Lines:"};
const struct LocStr _MSG_LINES_KEY = {15,"l"};
const struct LocStr _MSG_LV_SHORTHELP = {16,"This NListtree object reacts on\nthe preferences changes."};
const struct LocStr _MSG_OPEN = {17,"Open:"};
const struct LocStr _MSG_OPEN_AUTOSCROLL = {18,"Open scroll:"};
const struct LocStr _MSG_OPEN_AUTOSCROLL_KEY = {19,"s"};
const struct LocStr _MSG_OPEN_KEY = {20,"o"};
const struct LocStr _MSG_PREFS = {21,"Preferences"};
const struct LocStr _MSG_REMEMBER_STATUS = {22,"Remember:"};
const struct LocStr _MSG_REMEMBER_STATUS_KEY = {23,"m"};
const struct LocStr _MSG_SAMPLE = {24,"NListtree sample"};
const struct LocStr _MSG_SHADOW = {25,"Shadow:"};
const struct LocStr _MSG_SHADOW_KEY = {26,"w"};
const struct LocStr _MSG_SHORTHELP_CLOSED_IMAGE = {27,"Image for a closed node."};
const struct LocStr _MSG_SHORTHELP_DRAWPEN = {28,"Custom draw color."};
const struct LocStr _MSG_SHORTHELP_LINEPEN = {29,"Custom line color."};
const struct LocStr _MSG_SHORTHELP_OPEN_AUTOSCROLL = {30,"Auto scroll listview when opening\nnodes to fit in visible area."};
const struct LocStr _MSG_SHORTHELP_OPEN_IMAGE = {31,"Image for an opened node."};
const struct LocStr _MSG_SHORTHELP_REMEMBER_STATUS = {32,"Remember status of nodes\nafter closing."};
const struct LocStr _MSG_SHORTHELP_SHADOWPEN = {33,"Custom shadow color."};
const struct LocStr _MSG_SHORTHELP_SPACE = {34,"Number of space pixels."};
const struct LocStr _MSG_SHORTHELP_SPECIAL_IMAGE = {35,"Special image."};
const struct LocStr _MSG_SHORTHELP_STYLE = {36,"Global style of the tree."};
const struct LocStr _MSG_SPACE = {37,"Space:"};
const struct LocStr _MSG_SPACE_KEY = {38,"p"};
const struct LocStr _MSG_SPECIAL = {39,"Special:"};
const struct LocStr _MSG_SPECIAL_KEY = {40,"a"};
const struct LocStr _MSG_STR_PREFS_IMAGESLINES = {41,"Images/Lines"};
const struct LocStr _MSG_STR_PREFS_STYLE = {42,"Style"};
const struct LocStr _MSG_STYLE = {43,"Style:"};
const struct LocStr _MSG_STYLE_INSERTED = {44,"Inserted"};
const struct LocStr _MSG_STYLE_KEY = {45,"y"};
const struct LocStr _MSG_STYLE_LINES = {46,"Lines"};
const struct LocStr _MSG_STYLE_LINES3D = {47,"Lines 3D"};
const struct LocStr _MSG_STYLE_MAC = {48,"Mac"};
const struct LocStr _MSG_STYLE_NORMAL = {49,"Normal"};
const struct LocStr _MSG_STYLE_WIN98 = {50,"Win98"};
const struct LocStr _MSG_STYLE_WIN98PLUS = {51,"Win98+"};
const struct LocStr _MSG_WIN_TITLE_CLOSED_IMAGE = {52,"Adjust 'closed node' image"};
const struct LocStr _MSG_WIN_TITLE_DRAWPEN = {53,"Adjust `Draw' pen"};
const struct LocStr _MSG_WIN_TITLE_LINEPEN = {54,"Adjust `Lines' pen"};
const struct LocStr _MSG_WIN_TITLE_OPEN_IMAGE = {55,"Adjust 'opened node' image"};
const struct LocStr _MSG_WIN_TITLE_SHADOWPEN = {56,"Adjust `Shadow' pen"};
const struct LocStr _MSG_WIN_TITLE_SPECIAL_IMAGE = {57,"Adjust special image"};
const struct LocStr _MSG_BT_CLOSE = {58,"Close"};
const struct LocStr _MSG_BT_CLOSE_KEY = {59,"c"};
const struct LocStr _MSG_STYLE_GLOW = {60,"Glow"};
const struct LocStr _MSG_DUMMY = {61," "};

static struct Catalog *Catalog = NULL;

/******************************************************************************/
void OpenCat(struct Locale *);
void CloseCat(void);
STRPTR GetString(APTR);

/******************************************************************************/

void OpenCat(struct Locale * Loc)
{
    if(LocaleBase != NULL && Catalog == NULL)
    {
        Catalog=OpenCatalog(Loc,(STRPTR)"NListtree.mcp.catalog",
                            OC_BuiltInLanguage,"english",
                            OC_Version,CatVersion,
                            TAG_DONE);
    }
}

void CloseCat(void)
{
    if(LocaleBase!=NULL)
    {
        CloseCatalog(Catalog);
    }
    Catalog=NULL;
}

STRPTR GetString(APTR CatStr)
{
    STRPTR DefStr;
    LONG StrNum;

    StrNum=((struct LocStr *)CatStr)->ID;
    DefStr=((struct LocStr *) CatStr)->Str;

    return(Catalog ? (STRPTR)GetCatalogStr(Catalog,StrNum,DefStr) : DefStr);
}
