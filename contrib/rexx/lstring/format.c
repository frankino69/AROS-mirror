/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:37  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.3  1999/11/26 09:56:55  bnv
 * Changed: Use of swprintf in CE version.
 *
 * Revision 1.2  1999/06/10 14:09:24  bnv
 * Added the possibility to use the E,F or G format of C printf
 *
 * Revision 1.1  1998/07/02 17:18:00  bnv
 * Initial Version
 *
 */

#include <lstring.h>

/* ---------------- Lformat ------------------ */
void
Lformat( const PLstr to, const PLstr from,
	long before, long after, long expp, long expt )
{
/****************
	Lstr tmp,Integer,Befo,Afte,Mantissa,Exponent;
	long i,j,Point,Afters;
	int  Sign,ShowExp;

	LINITSTR(tmp);
	LINITSTR(Integer);
	LINITSTR(Befo);
	LINITSTR(Afte);
	LINITSTR(Mantissa);
	LINITSTR(Exponent);

	Lspace(&tmp,from,0,' ');	// * trim spaces *

	for (i=0; i<LLEN(tmp); i++)	// * split in Mantissa 'E' Exponent *
		if (LSTR(tmp)[i]=='e' || LSTR(tmp)[i]=='E') {
			Lsubstr(&Exponent,&tmp,i+2,0,' ');
			Lsubstr(&Mantissa,&tmp,1,i,' ');
			goto Lfo10;
		}
	Lstrcpy(&Mantissa,&tmp);
Lfo10:
	Sign = (LLSTR(Mantissa)[0] == '-');
	if (Sign) {
		Lstrcpy(&tmp,&Mantissa);
		Lsubstr(&Mantissa,&tmp,2,0,' ');
	}

	for (i=0; i<LLEN(Mantissa); i++)
		if (LSTR(Mantissa)[i]=='.') {
			Lleft(&Befo,&Mantissa,i,' ');
			Lsubstr(&Afte,&Mantissa,i+2,0,' ');
			goto Lfo20;
		}
	Lstrcpy(&Befo,&Mantissa);
Lfo20:
	Point = LLEN(Befo);

	// * Sign, Mantissa and Exponent now reflect the number. Befo, Afte
	// * and Point reflect Mantissa *

	// * The fourth and fifth argument allow for exponential notation.
	// * Decide whether exponential form to be used, setting ShowExp. *

	ShowExp = 0;
	L2INT(&Exponent);

	if (expp>=0 || expt>=0) {
		if (expt<0) expt = digits.level;
		// * decide whether exponential form to be used. *
		if ((Point + LINT(Exponent)) > expt)
			ShowExp = 1;	// * Digits before rule. *
		LeftOfPoint = 0;
		if (LLEN(Befo) > 0)
			LeftOfPoint = Befo;	// * Value left of the point *

		// * Digits after point rule for exponentiation *
		// * Count zeros to right of point *
		z = 0;
		while (LSTR(Afte)[z] == '0') z++;
		if ((LeftOfPoint=0) && ((z-LINT(Exponent)) > 5)) ShowExp = 1

		// * An extra rule for exponential form *
		if (expp=0) ShowExp = 0;

		// * Construct the exponential part of the result. *
		if (ShowExp) {
			LINT(Exponent) = LINT(Exponent) + (Point-1);
			Point = 1;	// * As required for scientific *
			if (digits.form = ENGINEERING)
				while (LINT(Exponent)%3 != 0) {
					Point++;
					LINT(Exponent) -= 1;
				}
		} else
			Point += LINT(Exponent);
	} else {
		// * If expp and expt are not given, exponential notation
		// *  will be used if the original number+0 done by
		// *  checkArgs led to it. *
		if (LINT(Exponent))
			ShowExp = 1;
	}

	Lstrcpy(&Integer,&Befo);
	Lstrcat(&Integer,&Afte);
	if (Point<1) {	// * Add extra zeros on the left *
		Lstrcpy(&tmp,&Integer);
		Lstrset(&Integer,1-Point,'0');
		Lstrcat(&Integer,&tmp);
		Point = 1;
	}

	If (Point>LLEN(Integer)) {	// * and maybe on the right *
		Lleft(&tmp,&Integer,Point,'0');
		Lstrcpy(&Integer,&tmp);
	}
	// *  Deal with right of decimal point first since that can affect
	//   the left. Ensure the requested number of digits there. *
	Afters = LLEN(Integer) - Point;
	if (after==0) after = Afters;
	// * make Afters match the requested after *
	if (Afters<after) {
		Lleft(&tmp,&Integer,LLEN(Integer)+after-Afters,'0');
		Lstrcpy(&Integer,&tmp);
	}

......

	LFREESTR(tmp);
	LFREESTR(Integer);
	LFREESTR(befo);
	LFREESTR(afte);
	LFREESTR(mantissa);
	LFREESTR(exponent);
*********************/
	double	r;

	r = Lrdreal(from);
	Lfx(to,(size_t)(before+after+10));
	LTYPE(*to) = LSTRING_TY;

	if (before<0) before = 0;
	if (after<0)  after  = 0;
	if (after) before += (after+1);
#ifndef WCE
	sprintf(LSTR(*to),
		(expp<=0)? "%#*.*lf":
			(expp==1)? "%#*.*lG" : "%#*.*lE",
		(int)before,(int)after,r);
	LLEN(*to) = STRLEN(LSTR(*to));
#else
	{
		TCHAR	buf[20];
//	GCVT(r,before,LSTR(*to));
		swprintf(buf,(expp<=0)? TEXT("%#*.*lf"):
			(expp==1)? TEXT("%#*.*lG") : TEXT("%#*.*lE"),
			(int)before,(int)after,r);
		wcstombs(LSTR(*to),buf,LLEN(*to)=wcslen(buf));
	}
#endif
} /* Lformat */
