/*
 * $Header$
 * $Log$
 * Revision 1.1  2001/04/04 05:43:36  wang
 * First commit: compiles on Linux, Amiga, Windows, Windows CE, generic gcc
 *
 * Revision 1.1  1999/11/29 14:58:00  bnv
 * Initial revision
 *
 */

#ifndef __LDEFS_H__
#define __LDEFS_H__

/* ----------- some global data type definitions ------------------ */
typedef unsigned char	byte;
typedef unsigned short	word;
typedef unsigned long	dword;
typedef int		bool;

/* ---------------- comonly used definitions ----------------- */
#ifndef FALSE
#	define FALSE	0
#	define TRUE	1
#endif
#ifndef OFF
#	define OFF	0
#	define ON	1
#endif
#ifndef NO
#	define NO	0
#	define YES	1
#endif

#ifndef PI
#	define PI	3.14159265358979323844
#endif
#define PIover180	1.74532925199433E-02
#define PIunder180	5.72957795130823E+01
#define Ln10		2.30258509299405
#define ONEoverLn10	0.43429448190325

#ifdef __MSDOS__
#	define BREAK	asm int 3;
#endif

/* --- BIT definitions --- */
#define MASK1	0x0001
#define MASK2	0x0003
#define MASK3	0x0007
#define MASK4	0x000f
#define MASK5	0x001f
#define MASK6	0x003f
#define MASK7	0x007f
#define MASK8	0x00ff
#define MASK9	0x01ff
#define MASK10	0x03ff
#define MASK11	0x07ff
#define MASK12	0x0fff
#define MASK13	0x1fff
#define MASK14	0x3fff
#define MASK15	0x7fff
#define MASK16	0xffff

#define BIT0	0x0001
#define BIT1	0x0002
#define BIT2	0x0004
#define BIT3	0x0008
#define BIT4	0x0010
#define BIT5	0x0020
#define BIT6	0x0040
#define BIT7	0x0080
#define BIT8	0x0100
#define BIT9	0x0200
#define BIT10	0x0400
#define BIT11	0x0800
#define BIT12	0x1000
#define BIT13	0x2000
#define BIT14	0x4000
#define BIT15	0x8000
#define BIT16	0x10000L

/* ------------------ comonly used macros -------------------- */
#define	ISPRINT(c)	((c)>=' ' && (c)<='~' && (c)!='\'')
/*#define ISSPACE(c)	((c==0x09) || (c==0x0D) || (c==0x20))*/
#define HEXVAL(x)	(((x)>='A')? \
				((((x)>='a')? ((x)&(0xDF)) : (x)) -'A'+10) :\
				((x)-'0'))
#define CTL(a)		(('a') & 0x1F)

#define SWAP(a,b)	a ^= b ^= a ^= b;

#define DIMENSION(p)	(sizeof(p) / sizeof(p[0]))
#define ABS(a)		(((a)<0)?-(a):(a))

#ifndef MAX
#	define MAX(a,b)	(((a)>(b))?(a):(b))
#	define MIN(a,b)	(((a)<(b))?(a):(b))
#endif

#define MAX3(a,b,c)	MAX(MAX(a,b),c)
#define MAX4(a,b,c,d)	MAX(MAX3(a,b,c),d)

#define MIN3(a,b,c)	MIN(MIN(a,b),c)
#define MIN4(a,b,c,d)	MIN(MIN3(a,b,c),d)

#define RANGE(a,x,b)	((x)<(a)?(a): ((x)>(b)?(b):(x)))
#define IN_RANGE(a,x,b)	(((a) <= (x)) && ((x) <= (b)))

#define TRUNC(a)	((a)>=0? (int)(a) : (int)((a)-1))
#define ROUND(a)	((a)>=0? (int)((a)+0.5): -(int)(0.5-(a)))
#define CEILING(a)	((a)==(int)(a)? (int)(a): \
			(a)>0? (int)(1+(int)(a)): -(int)(1+(int)(-(a))))
#define FRAC(x)		((x)-(float)((int)(x)))
#define SIGN(x)		((x)>0? 1:(((x)==0)?0:-1))
#define SQR(x)		((x)*(x))

#define RAD(a)		((a)*PIover180)
#define DEG(a)		((a)*PIunder180)

#define COSD(a)		cos(RAD(a))
#define SIND(a)		sin(RAD(a))
#define TAND(a)		tan(RAD(a))

#define LOG(x)		(log(x)*ONEoverLn10)
#define EXP10(x)	exp((x)*Ln10)

#ifndef __BORLANDC__
#	define huge
#endif

#endif
