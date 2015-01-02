/* 
 *     XaoS, a fast portable realtime fractal zoomer 
 *                  Copyright (C) 1996,1997 by
 *
 *      Jan Hubicka          (hubicka@paru.cas.cz)
 *      Thomas Marsh         (tmarsh@austin.ibm.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/*#define DRAW */
#ifdef _plan9_
#include <u.h>
#include <libc.h>
#include <stdio.h>
#else
#include <stdlib.h>
#include <stdio.h>
//#ifndef _MAC
#if !defined(_MAC) && !defined(AROS)
#include <malloc.h>
#endif
#ifdef __EMX__
#include <float.h>
#include <sys/cdefs.h>
#endif
#include <aconfig.h>
#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif
#include <math.h>
#include <string.h>
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#endif
#include <config.h>
#ifndef _plan9_
/*#undef NDEBUG */
#include <assert.h>
#endif
#endif
#include <fconfig.h>
#define SLARGEITER
#include <filter.h>
#include <zoom.h>
#include <archaccel.h>
#include <complex.h>		/*for myabs */
#include <plane.h>
#include <btrace.h>
#include <xthread.h>
#include "calculate.h"		/*an inlined calulate function */

#define ASIZE 16
#define ALIGN(x) (((x)+ASIZE-1)&(~(ASIZE-1)))
static int nsymetrized;
static unsigned char *tmpdata, *tmpdata1;
struct realloc_s
  {
    number_t possition;
    number_t price;
    int plus;
    int recalculate;
    int symto;
    int symref;
    int dirty;
#ifndef _plan9_
#include "alignhack.h"
#endif
  };
typedef struct realloc_s realloc_t;


typedef struct zoom_context
  {
    number_t *xpos, *ypos;
    int newcalc;
    int forversion;
    int forpversion;
    realloc_t *reallocx, *reallocy;
    int uncomplette;
    int changed;
  }
zoom_context;
#define getzcontext(f) ((zoom_context *)((f)->data))
#define getfcontext(f) ((f)->fractalc)

#define callwait() if(cfilter.wait_function!=NULL) cfilter.wait_function(&cfilter);
#define tcallwait() if(!xth_nthread(task)&&cfilter.wait_function!=NULL) cfilter.wait_function(&cfilter);
#define setuncomplette(i) (getzcontext(&cfilter)->uncomplette=i)
#define incuncomplette() (getzcontext(&cfilter)->uncomplette++)
#define setchanged(i) (getzcontext(&cfilter)->changed=i)


static zoom_context czoomc;
struct filter cfilter;
#ifdef STATISTICS
static int tocalculate = 0, avoided = 0;
static int nadded = 0, nsymetry = 0, nskipped = 0;
int nperi = 0;
#endif


/*first of all inline driver section */
/*If you think this way is ugly, I must agree. Please let me know
 *about better one that allows to generate custom code for 8,16,24,32
 *bpp modes and use of static variables
 */
#include <c256.h>
#define fill2 fill2_8
#define dosymetry2 dosymetry2_8
#define calcline calcline_8
#define calccolumn calccolumn_8
#include "zoomd.c"

#include <truecolor.h>
#define fill2 fill2_32
#define dosymetry2 dosymetry2_32
#define calcline calcline_32
#define calccolumn calccolumn_32
#include "zoomd.c"

#include <true24.h>
#define fill2 fill2_24
#define dosymetry2 dosymetry2_24
#define calcline calcline_24
#define calccolumn calccolumn_24
#include "zoomd.c"

#include <hicolor.h>
#define fill2 fill2_16
#define dosymetry2 dosymetry2_16
#define calcline calcline_16
#define calccolumn calccolumn_16
#include "zoomd.c"

#define calcline(a) drivercall(cimage,calcline_8(a),calcline_16(a),calcline_24(a),calcline_32(a));
#define calccolumn(a) drivercall(cimage,calccolumn_8(a),calccolumn_16(a),calccolumn_24(a),calccolumn_32(a));


struct dyn_data
  {
    int price;
    struct dyn_data *previous;
  };

#define FPMUL 64		/*Let multable fit into pentium cache */
#define RANGES 2		/*shift equal to x*RANGE */
#define RANGE 4

#define DSIZEHMASK (0x7)	/*mask equal to x%(DSIZE) */
#define DSIZE (2*RANGE)
#define DSIZES (RANGES+1)	/*shift equal to x*DSIZE */


#define adddata(n,i) (dyndata+(((n)<<DSIZES)+(((i)&(DSIZEHMASK)))))
#define getbest(i) (dyndata+((size)<<DSIZES)+(i))
#define nosetadd ((size*2)<<DSIZES)

#ifdef __POWERPC__
#  undef USE_MULTABLE
#else
#  define USE_MULTABLE 1
#endif

#ifdef USE_MULTABLE
#define PRICE(i,i1) (assert(abs((i)-(i1))<RANGE*FPMUL),mulmid[(i)-(i1)])
#else
#define PRICE(i,i1) (((i)-(i1)) * ((i)-(i1)))
#endif
#define NEWPRICE (FPMUL*FPMUL*(RANGE)*(RANGE))

#define NOSETMASK ((unsigned int)0x80000000)
#define END NULL
#define MAXPRICE INT_MAX
int dynsize = sizeof (struct dyn_data);
#ifndef INT_MIN
#define INT_MIN (- INT_MAX - 1)
#endif
#define IRANGE FPMUL*RANGE

#ifdef USE_MULTABLE
static int multable[RANGE * FPMUL * 2];
static int *mulmid;
#endif

/*Functions looks trought rows/columns marked for calculation and tries to use
 *some symetrical one instead
 */

/*FIXME should be threaded...but thread overhead should take more work than
 *do it in one, since it is quite simple and executes just in case fractal
 *on the screen is symetrical and it is quite rare case...who knows
 */
static void			/*INLINE */
preparesymetries (register realloc_t * realloc, CONST int size, register int symi, number_t sym, number_t step)
{
  register int i;
  register int istart = 0;
  number_t fy, ftmp;
  realloc_t *r = realloc, *reallocs;

  sym *= 2;
  i = 2 * symi - size;
  if (i < 0)
    i = 0;
  realloc += i;

  for (; i <= symi; i++, realloc++)
    {				/*makes symetries */
      int j, min = 0;
      number_t dist = INT_MAX, tmp1;

      if (realloc->symto != -1)
	continue;

      fy = realloc->possition;
      realloc->symto = 2 * symi - i;

      if (realloc->symto >= size - RANGE)
	realloc->symto = size - RANGE - 1;

      dist = RANGE * step;
      min = RANGE;
      reallocs = &r[realloc->symto];
      j = realloc->symto - istart > RANGE ? -RANGE : -realloc->symto + istart;

      if (realloc->recalculate)
	{
	  for (; j < RANGE && realloc->symto + j < size - 1; j++)
	    {
	      ftmp = sym - (reallocs + j)->possition;
	      if ((tmp1 = myabs (ftmp - fy)) < dist)
		{
		  if ((realloc == r || ftmp > (realloc - 1)->possition) &&
		      (ftmp < (realloc + 1)->possition))
		    {
		      dist = tmp1;
		      min = j;
		    }
		}
	      else if (ftmp < fy)
		break;
	    }

	}
      else
	{
	  for (; j < RANGE && realloc->symto + j < size - 1; j++)
	    {
	      if (!realloc->recalculate)
		continue;
	      ftmp = sym - (reallocs + j)->possition;
	      if ((tmp1 = myabs (ftmp - fy)) < dist)
		{
		  if ((realloc == r || ftmp > (realloc - 1)->possition) &&
		      (ftmp < (realloc + 1)->possition))
		    {
		      dist = tmp1;
		      min = j;
		    }
		}
	      else if (ftmp < fy)
		break;
	    }
	}
      realloc->symto += min;

      if (min == RANGE || realloc->symto <= symi ||
	  (reallocs = reallocs + min)->symto != -1 || reallocs->symref != -1)
	{
	  realloc->symto = -1;
	  continue;
	}

      if ( /*myabs(fy - (sym - reallocs->possition)) < RANGE*step */ 1)
	{
	  if (!realloc->recalculate)
	    {
	      realloc->symto = -1;
	      if (reallocs->symto != -1 || !reallocs->recalculate)
		continue;
	      reallocs->plus = realloc->plus;
	      reallocs->symto = i;
	      nsymetrized++;
	      istart = realloc->symto - 1;
	      reallocs->dirty = 1;
	      realloc->symref = reallocs - r;
	      STAT (nadded -= reallocs->recalculate);
	      reallocs->recalculate = 0;
	      reallocs->possition = sym - realloc->possition;
	    }
	  else
	    {
	      if (reallocs->symto != -1)
		{
		  realloc->symto = -1;
		  continue;
		}
	      istart = realloc->symto - 1;
	      STAT (nadded -= realloc->recalculate);
	      nsymetrized++;
	      realloc->dirty = 1;
	      realloc->plus = reallocs->plus;
	      realloc->recalculate = 0;
	      reallocs->symref = i;
	      realloc->possition = sym - reallocs->possition;
	    }
	  STAT (nsymetry++);
	}
      else
	realloc->symto = -1;

#ifndef NDEBUG
      if (realloc->symto < -1 || realloc->symto >= size)
	{
	  printf ("Internal error #22");
	  assert (0);
	}
      if (reallocs->symto < -1 || reallocs->symto >= size)
	{
	  printf ("Internal error #22");
	  assert (0);
	}
#endif
    }

}
static /*INLINE */ void
newpossitions (realloc_t * realloc, int size, number_t begin1, number_t end1, number_t * fpos, int yend)
{
  realloc_t *rs, *re, *rend;
  number_t step = size / (end1 - begin1);
  number_t start;
  number_t end;
  rend = realloc + size;
  rs = realloc - 1;
  re = realloc;
  while (rs < rend - 1)
    {
      re = rs + 1;
      if (re->recalculate)
	{
	  while (re < rend && re->recalculate)
	    re++;

	  if (re == rend)
	    end = end1;
	  else
	    end = re->possition;

	  if (rs == realloc - 1)
	    {
	      start = begin1;
	      if (start > end)
		start = end;
	    }
	  else
	    start = rs->possition;

	  if (re == rend && start > end)
	    end = start;

	  if (re - rs == 2)
	    end = (end - start) * 0.5;
	  else
	    end = (end - start) / (re - rs);


	  switch (yend)
	    {
	    case 1:
	      for (rs++; rs < re; rs++)
		{
		  start += end, rs->possition = start;
		  rs->price = 1 / (1 + myabs (fpos[rs - realloc] - start) * step);
		}
	      break;
	    case 2:
	      for (rs++; rs < re; rs++)
		{
		  start += end, rs->possition = start;
		  rs->price = (myabs (fpos[rs - realloc] - start) * step);
		  if (rs == realloc || rs == rend - 1)
		    rs->price *= 500;
		}
	      break;
	    default:
	      for (rs++; rs < re; rs++)
		{
		  start += end, rs->possition = start;
		  rs->price = 1;
		}
	      break;
	    }
	}
      rs = re;
    }
}

/* This is the main reallocation algorithm described in xaos.info
 * It is quite complex since many loops are unrooled and uses custom
 * fixedpoint
 *
 * Takes approx 30% of time so looking for way to do it threaded.
 * Let me know :)
 */
static /*INLINE */ void
mkrealloc_table (number_t * fpos, realloc_t * realloc, CONST int size, CONST number_t begin, CONST number_t end, number_t sym, unsigned char *tmpdata)
{
  int i, ps, ps1 = 0, pe;
  register int p;
  int bestprice = MAXPRICE;
  realloc_t *r = realloc;
  struct dyn_data *dyndata;
  int yend, y;
  register struct dyn_data **best;
  struct dyn_data **best1, **tmp;
  register int *pos;
  number_t step, tofix;
  int symi = -1;
  int lastplus = 0;
  struct dyn_data *data;
  register struct dyn_data *previous = NULL, *bestdata = NULL;
  register int myprice;
#ifdef STATISTICS
  nadded = 0, nsymetry = 0, nskipped = 0;
#endif

  pos = (int *) tmpdata;
  best = (struct dyn_data **) (tmpdata + ALIGN ((size + 2) * sizeof (int)));
  best1 = (struct dyn_data **) (tmpdata + ALIGN ((size + 2) * sizeof (int)) + ALIGN (size * sizeof (struct dyn_data **)));
  dyndata = (struct dyn_data *) (tmpdata + ALIGN ((size + 2) * sizeof (int)) + 2 * ALIGN (size * sizeof (struct dyn_data **)));

  tofix = size * FPMUL / (end - begin);
  pos[0] = INT_MIN;
  pos++;
  for (i = size - 1; i >= 0; i--)
    {
      pos[i] = (fpos[i] - begin) * tofix;	/*first convert everything into fixedpoint */
      if (i < size - 1 && pos[i] > pos[i + 1])	/*Avoid processing of missordered rows.
						   They should happend because of limited
						   precisity of FP numbers */
	pos[i] = pos[i + 1];
    }
  pos[size] = INT_MAX;
  step = (end - begin) / (number_t) size;
  if (begin > sym || sym > end)	/*calculate symetry point */
    symi = -2;
  else
    {
      symi = (sym - begin) / step;

    }

  ps = 0;
  pe = 0;
  y = 0;

  /* This is first pass that fills table dyndata, that holds information
   * about all ways algorithm thinks about. Correct way is discovered at
   * end by looking backward and determining witch way algorithm used to
   * calculate minimal value*/

  for (i = 0; i < size; i++, y += FPMUL)
    {
      bestprice = MAXPRICE;
      p = ps;			/*just inicialize parameters */

      tmp = best1;
      best1 = best;
      best = tmp;

      yend = y - IRANGE;
      if (yend < -FPMUL)	/*do no allow lines outside screen */
	yend = -FPMUL;

      while (pos[p] <= yend)	/*skip lines out of range */
	p++;
#ifdef _UNDEFINED_
      if (pos[p - 1] > yend)	/*warning...maybe this is the bug :) */
	p--, assert (0);
#endif
      ps1 = p;
      yend = y + IRANGE;

      /*First try case that current line will be newly calculated */

      /*Look for best way how to connect previous lines */
      if (ps != pe && p > ps)
	{			/*previous point had lines */
	  assert (p >= ps);
	  if (p < pe)
	    {
	      previous = best[p - 1];
	    }
	  else
	    previous = best[pe - 1];
	  myprice = previous->price;	/*find best one */
	}
      else
	{
	  if (i > 0)
	    {			/*previous line had no lines */
	      previous = getbest (i - 1);
	      myprice = previous->price;
	    }
	  else
	    previous = END, myprice = 0;
	}

      data = getbest (i);	/*find store possition */
      myprice += NEWPRICE;
      bestdata = data;
      data->previous = previous;
      bestprice = myprice;	/*calculate best available price */
      data->price = myprice;	/*store data */
      assert (bestprice >= 0);	/*FIXME:tenhle assert muze FAILIT! */
#ifdef _UNDEFINED_
      if (yend > end + FPMUL)	/*check bounds */
	yend = end + FPMUL;
#endif
      data = adddata (p, i);	/*calcualte all lines good for this y */

      /* Now try all acceptable connection and calculate best possibility
       * with this connection
       */
      if (ps != pe)
	{			/*in case that previous had also possitions */
	  int price1 = INT_MAX;
	  /*At first line of previous interval we have only one possibility
	   *don't connect previous line at all.
	   */
	  if (p == ps)
	    {			/*here we must skip previous point */
	      if (pos[p] != pos[p + 1])
		{
		  previous = getbest (i - 1);
		  myprice = previous->price;
		  myprice += PRICE (pos[p], y);		/*store data */
		  if (myprice < bestprice)
		    {		/*calcualte best */
		      bestprice = myprice, bestdata = data;
		      data->price = myprice;
		      data->previous = previous;
		    }
		}
	      assert (bestprice >= 0);
	      assert (myprice >= 0);
	      best1[p] = bestdata;
	      data += DSIZE;
	      p++;
	    }

	  previous = NULL;
	  price1 = myprice;
	  while (p < pe)
	    {			/*this is area where intervals of current point and previous one are crossed */
	      if (pos[p] != pos[p + 1])		/*This loops is evaluated approx 6 times more than rest of code */
		{
		  if (previous != best[p - 1])	/*True in more 2/3 of cases */
		    {

		      previous = best[p - 1];
		      price1 = myprice = previous->price;

		      /*In case we found revolutional point, we should think
		       *about changing our gusesses in last point too - don't
		       *connect it at all, but use this way instead*/
		      if (myprice + NEWPRICE < bestprice)	/*true in approx 2/3 of cases */
			{
			  bestprice = myprice + NEWPRICE, bestdata = data - DSIZE;
			  (bestdata)->price = bestprice;
			  (bestdata)->previous = previous + nosetadd;
			  best1[p - 1] = bestdata;
			}
		    }
		  else
		    myprice = price1;

		  myprice += PRICE (pos[p], y);		/*calculate price of new connection */

		  if (myprice < bestprice)	/*2/3 of cases */
		    {		/*if it is better than previous, store it */
		      bestprice = myprice, bestdata = data;
		      data->price = myprice;
		      data->previous = previous;
		    }
		  else if (pos[p] > y)
		    {
		      best1[p] = bestdata;
		      data += DSIZE;
		      p++;
		      break;
		    }

		}

	      assert (myprice >= 0);
	      assert (bestprice >= 0);	/*FIXME:tenhle assert FAILI! */

	      best1[p] = bestdata;
	      data += DSIZE;
	      p++;
	    }
	  while (p < pe)
	    {			/*this is area where intervals of current point and previous one are crossed */
	      if (pos[p] != pos[p + 1])		/*This loops is evaluated approx 6 times more than rest of code */
		{
		  if (previous != best[p - 1])	/*True in more 2/3 of cases */
		    {

		      previous = best[p - 1];
		      myprice = previous->price;

		      /*In case we found revolutional point, we should think
		       *about changing our gusesses in last point too - don't
		       *connect it at all, but use this way instead*/
		      if (myprice + NEWPRICE < bestprice)	/*true in approx 2/3 of cases */
			{
			  bestprice = myprice + NEWPRICE, bestdata = data - DSIZE;
			  (bestdata)->price = bestprice;
			  (bestdata)->previous = previous + nosetadd;
			  best1[p - 1] = bestdata;
			}
		      myprice += PRICE (pos[p], y);	/*calculate price of new connection */
		      if (myprice < bestprice)	/*2/3 of cases */
			{	/*if it is better than previous, store it */
			  bestprice = myprice, bestdata = data;
			  data->price = myprice;
			  data->previous = previous;
			}
		    }
		}

	      assert (myprice >= 0);
	      assert (bestprice >= 0);	/*FIXME:tenhle assert FAILI! */

	      best1[p] = bestdata;
	      data += DSIZE;
	      p++;
	    }

	  /* OK...we passed crossed area. All next areas have same previous
	   * situation so our job is easier
	   * So find the best solution once for all od them
	   */
	  if (p > ps)
	    {
	      assert (p >= ps);	/*find best one in previous */
	      previous = best[p - 1];
	      price1 = previous->price;
	    }
	  else
	    {
	      previous = getbest (i - 1);
	      price1 = previous->price;
	    }

	  /* Since guesses for "revolutional point" was allways one
	   * step back, we need to do last one*/
	  if (price1 + NEWPRICE < bestprice && p > ps1)
	    {
	      myprice = price1 + NEWPRICE;
	      bestprice = myprice, bestdata = data - DSIZE;
	      (bestdata)->price = myprice;
	      (bestdata)->previous = previous + nosetadd;
	      best1[p - 1] = bestdata;
	      myprice -= NEWPRICE;
	    }

	  while (pos[p] < yend)
	    {
	      if (pos[p] != pos[p + 1])
		{
		  myprice = price1;
		  myprice += PRICE (pos[p], y);		/*store data */
		  if (myprice < bestprice)
		    {		/*calcualte best */
		      bestprice = myprice, bestdata = data;
		      data->price = myprice;
		      data->previous = previous;
		    }
		  else if (pos[p] > y)
		    break;
		}

	      assert (bestprice >= 0);
	      assert (myprice >= 0);

	      best1[p] = bestdata;
	      data += DSIZE;
	      p++;
	    }
	  while (pos[p] < yend)
	    {
	      best1[p] = bestdata;
	      p++;
	    }
	}
      else
	{
	  /* This is second case - previous y was not mapped at all.
	   * Situation is simplier now, since we know that behind us is
	   * large hole and our decisions don't affect best solution for
	   * previous problem. Se we have just one answer
	   * Situation is similiar to latest loop in previous case
	   */
	  int myprice1;		/*simplified loop for case that previous
				   y had no lines */
	  if (pos[p] < yend)
	    {
	      if (i > 0)
		{
		  previous = getbest (i - 1);
		  myprice1 = previous->price;
		}
	      else
		previous = END, myprice1 = 0;
	      while (pos[p] < yend)
		{
		  if (pos[p] != pos[p + 1])
		    {
		      myprice = myprice1 + PRICE (pos[p], y);
		      if (myprice < bestprice)
			{
			  data->price = myprice;
			  data->previous = previous;
			  bestprice = myprice, bestdata = data;
			}
		      else if (pos[p] > y)
			break;
		    }
		  assert (bestprice >= 0);
		  assert (myprice >= 0);
		  best1[p] = bestdata;
		  p++;
		  data += DSIZE;
		}
	      while (pos[p] < yend)
		{
		  best1[p] = bestdata;
		  p++;
		}
	    }
	}
      /*previous = ps; *//*store possitions for next loop */
      ps = ps1;
      ps1 = pe;
      pe = p;
    }


  assert (bestprice >= 0);

  realloc = realloc + size;
  yend = (begin > fpos[0]) && (end < fpos[size - 1]);

  if (pos[0] > 0 && pos[size - 1] < size * FPMUL)
    yend = 2;



  /*This part should be made threaded quite easily...but does it worth
   *since it is quite simple loop 0...xmax
   */
  for (i = size; i > 0;)
    {				/*and finally traces the path */
      struct dyn_data *bestdata1;
      realloc--;
      i--;
      realloc->symto = -1;
      realloc->symref = -1;
      bestdata1 = bestdata->previous;

      if (bestdata1 >= dyndata + nosetadd || bestdata >= dyndata + ((size) << DSIZES))
	{
	  if (bestdata1 >= dyndata + nosetadd)
	    bestdata1 -= nosetadd;

	  realloc->recalculate = 1;
	  STAT (nadded++);
	  realloc->dirty = 1;
	  lastplus++;

	  if (lastplus >= size)
	    lastplus = 0;

	  realloc->plus = lastplus;

	}
      else
	{
	  p = (bestdata - dyndata) >> DSIZES;
	  assert (p >= 0 && p < size);
	  realloc->possition = fpos[p];
	  realloc->plus = p;
	  realloc->dirty = 0;
	  realloc->recalculate = 0;
	  lastplus = p;
	}
      bestdata = bestdata1;
    }



  newpossitions (realloc, size, begin, end, fpos, yend);
  realloc = r;
  if (symi <= size && symi >= 0)
    {
      preparesymetries (r, size, symi, sym, step);
    }


  STAT (printf ("%i added %i skipped %i mirrored\n", nadded, nskipped, nsymetry));
  STAT (nadded2 += nadded;
	nskipped2 += nskipped;
	nsymetry2 += nsymetry);
}


static int plus1;
/* 
 * this function prepares fast moving table for moveoldpoints
 * see xaos.info for details. It is not threaded since it is quite
 * fast.
 */
static /*INLINE */ void
preparemoveoldpoints (void)
{
  int *size, *siz;
  int *start, *startptr;
  int *sizend;
  realloc_t *rx, *rend1;
  size = (int *) tmpdata;
  start = (int *) (tmpdata + ALIGN (cimage.width * sizeof (int)));

  plus1 = 0;

  startptr = start;
  siz = size;
  for (rx = czoomc.reallocx, rend1 = rx + cimage.width;
       rx < rend1; rx++)
    if ((rx->dirty) && plus1 < cimage.width + 1)
      plus1++;
    else
      break;
  *startptr = czoomc.reallocx->plus;
  *siz = 0;
  rend1--;
  while (rend1->dirty)
    {
      if (rend1 == czoomc.reallocx)
	return;
      rend1--;
    }
  rend1++;
  for (; rx < rend1; rx++)
    {
      if ((rx->dirty || rx->plus == *startptr + *siz) && *startptr + *siz < cimage.width)
	(*siz)++;
      else
	{
	  if (*siz)
	    {
	      if (!(*startptr + *siz < cimage.width) && !rx->dirty)
		{
		  int i;
		  if (rx == rend1)
		    break;
		  for (i = 0; rx->dirty && rx < rend1; rx++)
		    i++;
		  siz++, startptr++;
		  *siz = i;
		  *startptr = rx->plus - i;
		  if (*startptr < 0)
		    {
		      /*FIXME remove this */
		      printf ("Internal program error #232\n");
		      exit (-1);
		    }
		}
	      else
		{
		  siz++, startptr++;
		  *startptr = rx->plus;
		}
	    }
	  else
	    *startptr = rx->plus;
	  assert (rx->plus >= 0 && rx->plus < cimage.width);
	  *siz = 1;
	}

    }
  if (*siz)
    sizend = siz + 1;
  else
    sizend = siz;
  *sizend = 0;
  if (cimage.bytesperpixel != 1)
    {
      for (startptr = start, siz = size; siz < sizend; siz++, startptr++)
	{
	  *siz *= cimage.bytesperpixel;
	  *startptr *= cimage.bytesperpixel;
	}
      plus1 *= cimage.bytesperpixel;
    }
}
static /*INLINE */ void
moveoldpoints (void *data, struct taskinfo *task, int r1, int r2)
{
  unsigned char *vline, *vbuff;
  int *size, *siz;
  int *start, *startptr;
  realloc_t *ry, *rend;
  int i = r1;

  size = (int *) tmpdata;
  start = (int *) (tmpdata + ALIGN (cimage.width * sizeof (int)));

  for (ry = czoomc.reallocy + r1, rend = czoomc.reallocy + r2; ry < rend; ry++, i++)
    {
      if (!ry->dirty)
	{
	  assert (ry->plus >= 0 && ry->plus < cimage.height);
	  vbuff = cimage.currlines[i] + plus1;
	  vline = cimage.oldlines[ry->plus];
	  for (startptr = start, siz = size; *siz; siz++, startptr++)
	    {
	      memcpy (vbuff, vline + *startptr, *siz), vbuff += *siz;
	    }
	}
    }
}

static /*INLINE */ void
calculatenew (void *data, struct taskinfo *task, int r1, int r2)
{
  int s;
  realloc_t *rx, *ry, *rend;
  /*int s3; */

  if (!xth_nthread (task))
    {
      STAT (tocalculate = 0);
      STAT (avoided = 0);
      cfilter.pass = "Solid guessing 1";
      cfilter.max = 0;
      cfilter.pos = 0;
    }

  /* We don't need to wory about race conditions here, since only
   * problem that should happend is incorrectly counted number
   * of lines to do...
   *
   * I will fix that problem later, but I think that this information
   * should be quite useless at multithreaded systems so it should
   * be a bit inaccurate. Just need to take care in percentage
   * displayers that thinks like -100% or 150% should happend
   */
  if (!xth_nthread (task))
    {
      for (ry = czoomc.reallocy, rend = ry + cimage.height; ry < rend; ry++)
	{
	  if (ry->recalculate)
	    cfilter.max++;
	}
    }
  tcallwait ();
  for (s = 0; s < 2; s++)
    {
      for (ry = czoomc.reallocy + s, rend = ry + cimage.height - s; ry < rend; ry += 2)
	{
	  xth_lock (0);
	  if (ry->recalculate == 1)
	    {
	      ry->recalculate = 2;
	      xth_unlock (0);
	      setchanged (1);
	      ry->dirty = 0;
	      calcline (ry);
	      cfilter.pos++;
	      tcallwait ();
	      if (cfilter.interrupt)
		return;
	    }
	  else
	    {
	      xth_unlock (0);
	    }
	}			/*for ry */
    }				/*for s */
  if (!xth_nthread (task))
    {
      cfilter.max = 0;
      cfilter.pass = "Solid guessing 2";
      cfilter.pos = 0;
      for (rx = czoomc.reallocx, rend = rx + cimage.width; rx < rend; rx++)
	{
	  if (rx->recalculate)
	    {
	      cfilter.max++;
	    }
	}
    }
  for (s = 0; s < 2; s++)
    {
      for (rx = czoomc.reallocx + s, rend = rx + cimage.width - s; rx < rend; rx += 2)
	{
	  xth_lock (0);
	  if (rx->recalculate == 1)
	    {
	      rx->recalculate = 2;
	      xth_unlock (0);
	      setchanged (1);
	      rx->dirty = 0;
	      calccolumn (rx);
	      cfilter.pos++;
	      tcallwait ();
	      if (cfilter.interrupt)
		return;
	    }
	  else
	    {
	      xth_unlock (0);
	    }
	}
    }
  STAT (printf ("Avoided caluclating of %i points from %i and %2.2f%% %2.2f%%\n", avoided, tocalculate, 100.0 * (avoided) / tocalculate, 100.0 * (tocalculate - avoided) / cimage.width / cimage.height));
  STAT (
	 avoided2 += avoided;
	 tocalculate2 += tocalculate;
	 frames2 += 1);
}

// static void
// addprices (realloc_t * r, realloc_t * r2) REGISTERS (3);
static void
addprices (realloc_t * r, realloc_t * r2)
{
  realloc_t *r3;
  while (r < r2)
    {
      r3 = r + (((int) (r2 - r)) >> 1);
      r3->price = (r2->possition - r3->possition) * (r3->price);
      if (r3->symref != -1)
	r3->price = r3->price / 2;
      addprices (r, r3);
      r = r3 + 1;
    }
}

/* We can't do both symetryies (x and y) in one loop at multithreaded
 * systems,since we need to take care to points at the cross of symetrized
 * point/column
 */
static /*INLINE */ void
dosymetry (void *data, struct taskinfo *task, int r1, int r2)
{
  unsigned char **vbuff = cimage.currlines + r1;
  realloc_t *ry, *rend;
  int linesize = cimage.width * cimage.bytesperpixel;

  for (ry = czoomc.reallocy + r1, rend = czoomc.reallocy + r2; ry < rend; ry++)
    {
      if (!(ry->symto >= 0 || ry->symto == -1))
	printf ("%i %i", (int) ry->symto, (int) (ry - czoomc.reallocy));	/*FIXME remove this! */
      assert (ry->symto >= 0 || ry->symto == -1);
      if (ry->symto >= 0)
	{
	  assert (ry->symto < cimage.height);
	  if (!czoomc.reallocy[ry->symto].dirty)
	    {
	      memcpy (*vbuff, cimage.currlines[ry->symto], linesize);
	      ry->dirty = 0;
	    }
	}
      vbuff++;
    }
}

static /*INLINE */ void
fillx (void)
{
  pixel_t **vbuffs;
  realloc_t *ry, *rend;
  int height = 0;
  vbuffs = (pixel_t **) tmpdata;
  for (ry = czoomc.reallocy, rend = ry + cimage.height; ry < rend; ry++)
    if (!ry->dirty)
      vbuffs[height] = cimage.currlines[ry - czoomc.reallocy], height++;
  drivercall (cimage,
	      xth_function (fill2_8, vbuffs + height, cimage.width),
	      xth_function (fill2_16, vbuffs + height, cimage.width),
	      xth_function (fill2_24, vbuffs + height, cimage.width),
	      xth_function (fill2_32, vbuffs + height, cimage.width));
  xth_sync ();
}
static /*INLINE */ void
filly (void *data, struct taskinfo *task, int rr1, int rr2)
{
  register unsigned char **vbuff = cimage.currlines;
  realloc_t *ry, *r1, *r2, *rend, *rend2, *rs = NULL;
  int linesize = cimage.width * cimage.bytesperpixel;

  ry = czoomc.reallocy + rr1;
  while (ry > czoomc.reallocy && ry->dirty)
    ry--;
  for (rend = czoomc.reallocy + rr2, rend2 = czoomc.reallocy + cimage.height; ry < rend; ry++)
    {
      if (ry->dirty)
	{
	  incuncomplette ();
	  r1 = ry - 1;
	  for (r2 = ry + 1; r2->dirty && r2 < rend2; r2++);
	  if (r2 == rend2 && (rr2 != cimage.height||ry==0))
	    return;
	  while (ry->dirty && ry < rend2)
	    {
	      if (r1 < czoomc.reallocy)
		rs = r2;
	      else if (r2 >= rend2)
		rs = r1;
	      else if (ry->possition - r1->possition < r2->possition - ry->possition)
		rs = r1;
	      else
		rs = r2;
	      memcpy (vbuff[ry - czoomc.reallocy], vbuff[rs - czoomc.reallocy], linesize);
	      ry->dirty = 0;
	      ry->possition = rs->possition;
	      ry++;
	    }
	}
    }
}
/*Well, clasical simple quicksort. Should be faster than library one
 *because of reduced number of function calls :)
 */
static INLINE void myqsort(realloc_t **start, realloc_t **end)
{
  number_t med;
  realloc_t **left=start,**right=end-1;
  while(1) {

    /*Quite strange caluclation of median, but should be
     *as good as Sedgewick middle of three method and is faster*/
    med=((*start)->price+(*(end-1))->price)*0.5;

    /*Avoid one comparsion*/
    if(med>(*start)->price) {
      realloc_t *tmp;
      tmp=*left;
      *left=*right;
      *right=tmp;
    }
    right--;
    left++;

    while(1)
    { realloc_t *tmp;

      while(left<right&&(*left)->price>med) left++;
      while(left<right&&med>(*right)->price) right--;

      if(left<right) {
	tmp=*left;
	*left=*right;
	*right=tmp;
	left++;
	right--;
      } else break;
    }
    if(left-start>1) myqsort(start,left);
    if(end-right<=2) return;
    left=start=right;
    right=end-1;
  }
}
static int tocalcx, tocalcy;
static void
processqueue (void *data, struct taskinfo *task, int r1, int r2)
{
  realloc_t **tptr = (realloc_t **) data, **tptr1 = (realloc_t **) tmpdata;
  realloc_t *r, *end;
  end = czoomc.reallocx + cimage.width;

  while (tptr1 < tptr && (!cfilter.interrupt || tocalcx == cimage.width || tocalcy == cimage.height))
    {
      xth_lock (0);
      r = *tptr1;
      if (r != NULL)
	{
	  *tptr1 = NULL;
	  xth_unlock (0);
	  cfilter.pos++;
	  if (tocalcx < cimage.width - 2 && tocalcy < cimage.height - 2)
	    cfilter.readyforinterrupt = 1;
	  tcallwait ();
	  if (r >= czoomc.reallocx && r < end)
	    {
	      r->dirty = 0;
	      tocalcx--;
	      calccolumn (r);
	    }
	  else
	    {
	      r->dirty = 0;
	      tocalcy--;
	      calcline (r);
	    }
	}
      else
	{
	  xth_unlock (0);
	}
      tptr1++;
    }
}
/*
 * Another long utnthreaded code. It seems to be really long and
 * ugly, but believe or not it takes just about 4% of calculation time,
 * so why to worry about? :)
 *
 * This code looks for columns/lines to calculate, adds them into queue,
 * sorts it in order of significancy and then calls parrel processqueue,
 * that does the job.
 */
static void
calculatenewinterruptible (void)
{
  int tocalcx = 0, tocalcy = 0;
  realloc_t *r, *r2, *end, *end1;
  realloc_t **table, **tptr;

  /*tptr = table = (realloc_t **) malloc (sizeof (*table) * (cimage.width + cimage.height)); */
  tptr = table = (realloc_t **) tmpdata;
  end = czoomc.reallocx + cimage.width;

  STAT (tocalculate = 0);
  STAT (avoided = 0);

  cfilter.pass = "Solid guessing";

  for (r = czoomc.reallocx; r < end; r++)
    if (r->dirty)
      tocalcx++, setchanged (1);

  for (r = czoomc.reallocx; r < end; r++)
    {
      if (r->recalculate)
	{
	  for (r2 = r; r2->recalculate && r2 < end; r2++)
	    *(tptr++) = r2;
	  if (r2 == end)
	    /*(r2 - 1)->price = 0, */ r2--;
	  addprices (r, r2);
	  r = r2;
	}
    }

  end1 = czoomc.reallocy + cimage.height;

  for (r = czoomc.reallocy; r < end1; r++)
    if (r->dirty)
      tocalcy++, setchanged (1);

  for (r = czoomc.reallocy; r < end1; r++)
    {
      if (r->recalculate)
	{
	  for (r2 = r; r2->recalculate && r2 < end1; r2++)
	    *(tptr++) = r2;
	  if (r2 == end1)
	    /*(r2 - 1)->price = 0, */ r2--;
	  addprices (r, r2);
	  r = r2;
	}
    }
  if(table!=tptr) {

  if(tptr-table>1)
    myqsort (table, tptr);

  cfilter.pos = 0;
  cfilter.max = tptr - table;
  cfilter.incalculation = 1;
  callwait ();

  xth_function (processqueue, tptr, 1);

  callwait ();
  }

  cfilter.pos = 0;
  cfilter.max = 0;
  cfilter.pass = "Procesing symetries";
  cfilter.incalculation = 0;
  callwait ();

  xth_sync ();
  if (nsymetrized)
    {
      xth_function (dosymetry, NULL, cimage.height);
      xth_sync ();
      drivercall (cimage,
		  xth_function (dosymetry2_8, NULL, cimage.width),
		  xth_function (dosymetry2_16, NULL, cimage.width),
		  xth_function (dosymetry2_24, NULL, cimage.width),
		  xth_function (dosymetry2_32, NULL, cimage.width));
      xth_sync ();
    }
  if (cfilter.interrupt)
    {
      cfilter.pass = "reducing resolution";
      fillx ();
      xth_function (filly, NULL, cimage.height);
    }
  xth_sync ();

  STAT (printf ("Avoided caluclating of %i points from %i and %2.2f%% %2.2f%%\n", avoided, tocalculate, 100.0 * (avoided) / tocalculate, 100.0 * (tocalculate - avoided) / cimage.width / cimage.height));
  STAT (
	 avoided2 += avoided;
	 tocalculate2 += tocalculate;
	 frames2 += 1);
}
void
init_tables (struct filter *f)
{
  int i;
  zoom_context *c = getzcontext (f);

  /*c->dirty = 2; */
  for (i = 0; i < f->image->width + 1; i++)
    c->xpos[i] = (-f->fractalc->rs.nc+f->fractalc->rs.mc) + f->fractalc->rs.mc;
  for (i = 0; i < f->image->height + 1; i++)
    c->ypos[i] = (-f->fractalc->rs.ni+f->fractalc->rs.mi) + f->fractalc->rs.mi;
}


static int
alloc_tables (struct filter *f)
{
  zoom_context *c = getzcontext (f);
  c->xpos = (number_t *) malloc ((f->image->width + 8) * sizeof (*c->xpos));
  if (c->xpos == NULL)
    return 0;
  c->ypos = (number_t *) malloc ((f->image->height + 8) * sizeof (*c->ypos));
  if (c->ypos == NULL)
    {
      free ((void *) c->xpos);
      return 0;
    }
  c->reallocx = (realloc_t *) malloc (sizeof (realloc_t) * (f->image->width + 8));
  if (c->reallocx == NULL)
    {
      free ((void *) c->xpos);
      free ((void *) c->ypos);
      return 0;
    }
  c->reallocy = (realloc_t *) malloc (sizeof (realloc_t) * (f->image->height + 8));
  if (c->reallocy == NULL)
    {
      free ((void *) c->xpos);
      free ((void *) c->ypos);
      free ((void *) c->reallocx);
      return 0;
    }
  return 1;
}

static void
free_tables (struct filter *f)
{
  zoom_context *c = getzcontext (f);
  if (c->xpos != NULL)
    free ((void *) c->xpos), c->xpos = NULL;
  if (c->ypos != NULL)
    free ((void *) c->ypos), c->ypos = NULL;
  if (c->reallocx != NULL)
    free ((void *) c->reallocx), c->reallocx = NULL;
  if (c->reallocy != NULL)
    free ((void *) c->reallocy), c->reallocy = NULL;
}
static void
free_context (struct filter *f)
{
  zoom_context *c;
  c = getzcontext (f);
  free_tables (f);
  free ((void *) c);
}

static zoom_context *
make_context (void)
{
  zoom_context *new_ctxt;

  new_ctxt = (zoom_context *) calloc (sizeof (zoom_context), 1);
  if (new_ctxt == NULL)
    return NULL;
  new_ctxt->forversion = -1;
  new_ctxt->newcalc = 1;
  new_ctxt->reallocx = NULL;
  new_ctxt->reallocy = NULL;
  new_ctxt->xpos = NULL;
  new_ctxt->ypos = NULL;
  new_ctxt->uncomplette = 0;
  return (new_ctxt);
}
static void
startbgmkrealloc (void *data, struct taskinfo *task, int r1, int r2)
{
  mkrealloc_table (czoomc.ypos, czoomc.reallocy, cimage.height, cfractalc.rs.ni, cfractalc.rs.mi, cursymetry.ysym, tmpdata1);
}
static int
do_fractal (struct filter *f, int flags, int time)
{
  number_t *posptr;
  int maxres;
  int size;
  int rflags = 0;
  realloc_t *r, *rend;

  f->image->flip (f->image);
  cfilter = *f;
  set_fractalc (f->fractalc, f->image);

  if (getzcontext (f)->forversion != f->fractalc->version ||
      getzcontext (f)->newcalc ||
      getzcontext (f)->forpversion != f->image->palette->version)
    {
      clear_image (f->image);
      free_tables (f);
      alloc_tables (f);
      init_tables (f);
      getzcontext (f)->newcalc = 0;
      getzcontext (f)->forversion = getfcontext (f)->version;
      getzcontext (f)->forpversion = f->image->palette->version;
      czoomc = *getzcontext (f);
      if (BTRACEOK && !(flags & INTERRUPTIBLE))
	{
	  if (!boundarytraceall (czoomc.xpos, czoomc.ypos))
	    getzcontext (f)->newcalc = 1;
	  f->flags &= ~ZOOMMASK;
	  return CHANGED;
	}
    }
  else
    rflags |= INEXACT;

  czoomc = *getzcontext (f);

  setuncomplette (0);
  setchanged (0);

  maxres = cimage.width;
  if (maxres < cimage.height)
    maxres = cimage.height;
  size = ALIGN ((maxres) * (DSIZE + 1) * sizeof (struct dyn_data)) + 2 * ALIGN (maxres * sizeof (struct dyn_data **)) + ALIGN ((maxres + 2) * sizeof (int));
#ifdef HAVE_ALLOCA
  tmpdata = alloca (size);
#else
  tmpdata = malloc (size);
#endif
  if (tmpdata == NULL)
    {
      fprintf (stderr, "XaoS fatal error:Could not allocate memory for temporary data of size %i.\n"
	       "I am unable to handle this problem so please resize to smaller window\n", size);
      return 0;
    }
  if (nthreads != 1)
    {
#ifdef HAVE_ALLOCA
      tmpdata1 = alloca (size);
#else
      tmpdata1 = malloc (size);
#endif
      if (tmpdata1 == NULL)
	{
	  fprintf (stderr, "XaoS fatal error:Could not allocate memory for temporary data of size %i.\n"
		   "I am unable to handle this problem so please resize to smaller window\n", size);
	  return 0;
	}
    }
  else
    tmpdata1 = tmpdata;

  cfilter.incalculation = 0;
  cfilter.readyforinterrupt = 0;
  cfilter.interrupt = 0;

  nsymetrized = 0;
  cfilter.max = 0;
  cfilter.pos = 0;
  cfilter.pass = "Making y realloc table";
  xth_bgjob (startbgmkrealloc, NULL);

  cfilter.pass = "Making x realloc table";
  mkrealloc_table (czoomc.xpos, czoomc.reallocx, cimage.width, cfractalc.rs.nc, cfractalc.rs.mc, cursymetry.xsym, tmpdata);

  callwait ();

  cfilter.pass = "Moving old points";
  callwait ();
  preparemoveoldpoints ();
  xth_sync ();
  xth_function (moveoldpoints, NULL, cimage.height);

  cfilter.pass = "Starting calculation";
  callwait ();
  xth_sync ();
  if (flags & INTERRUPTIBLE)
    calculatenewinterruptible ();
  else
    {
      xth_function (calculatenew, NULL, 1);
      if (cfilter.interrupt)
	{
	  init_tables (f);
	  getzcontext (f)->newcalc = 1;
#ifndef HAVE_ALLOCA
	  free (tmpdata);
	  if (nthreads != 1)
	    free (tmpdata1);
#endif
	  return CHANGED | UNCOMPLETTE;
	}
      cfilter.pos = 0;
      cfilter.max = 0;
      cfilter.pass = "Procesing symetries";
      callwait ();
      xth_sync ();
      if (nsymetrized)
	{
	  xth_function (dosymetry, NULL, cimage.height);
	  xth_sync ();
	  drivercall (cimage,
		      xth_function (dosymetry2_8, NULL, cimage.width),
		      xth_function (dosymetry2_16, NULL, cimage.width),
		      xth_function (dosymetry2_24, NULL, cimage.width),
		      xth_function (dosymetry2_32, NULL, cimage.width));
	  xth_sync ();
	}
    }
  for (r = czoomc.reallocx, posptr = czoomc.xpos, rend = czoomc.reallocx + cimage.width;
       r < rend; r++, posptr++)
    {
      *posptr = r->possition;
    }
  for (r = czoomc.reallocy, posptr = czoomc.ypos, rend = czoomc.reallocy + cimage.height;
       r < rend; r++, posptr++)
    {
      *posptr = r->possition;
    }
#ifdef STATISTICS
  STAT (printf ("Statistics: frames %i\n"
		"mkrealloctable: added %i, symetry %i\n"
		"calculate loop: tocalculate %i avoided %i\n"
		"calculate:calculated %i inside %i\n"
		"iters inside:%i iters outside:%i periodicty:%i\n"
		,frames2, nadded2, nsymetry2, tocalculate2, avoided2, ncalculated2, ninside2, niter2, niter1, nperi));
#endif
  f->flags &= ~ZOOMMASK;
  if (getzcontext (f)->uncomplette)
    rflags |= UNCOMPLETTE, f->flags |= UNCOMPLETTE;
  if (getzcontext (f)->uncomplette > (cimage.width + cimage.height) / 2)
    f->flags |= LOWQUALITY;
  if (getzcontext (f)->changed)
    rflags |= CHANGED;
#ifndef HAVE_ALLOCA
  free (tmpdata);
  if (nthreads != 1)
    free (tmpdata1);
#endif
  return rflags;
}


static struct filter *
getinstance (struct filteraction *a)
{
  struct filter *f = createfilter (a);
  f->data = make_context ();
  f->name = "Zooming engine";
  return (f);
}
static void
destroyinstance (struct filter *f)
{
  free_context (f);
  free (f);
}
static int
requirement (struct filter *f, struct requirements *r)
{
  r->nimages = 2;
  r->supportedmask = C256 | TRUECOLORS | TRUECOLOR24 | HICOLOR | REALCOLOR | LARGEITER | SMALLITER | GRAYSCALE;
  r->flags = IMAGEDATA | TOUCHIMAGE;
  return (f->next->action->requirement (f->next, r));
}

static int
initialize (struct filter *f, struct initdata *i)
{
#ifdef USE_MULTABLE
  if (!multable[0])
    {
      int i;
      mulmid = multable + RANGE * FPMUL;
      for (i = -RANGE * FPMUL; i < RANGE * FPMUL; i++)
	mulmid[i] = i * i;
    }
#endif
  inhermisc (f, i);
  if (i->image != f->image || datalost (f, i))
    getzcontext (f)->forversion = -1, f->image = i->image;
  f->imageversion = i->image->version;
  return (1);
}

struct filteraction zoom_filter =
{
  "XaoS's zooming engine",
  "zoom",
  0,
  getinstance,
  destroyinstance,
  do_fractal,
  requirement,
  initialize,
  convertupgeneric,
  convertdowngeneric,
  NULL,
};
