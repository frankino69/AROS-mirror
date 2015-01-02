#ifndef _RSTAT_H_RPCGEN
#define _RSTAT_H_RPCGEN
/*
    Copyright � 2003-2004, The AROS Development Team. All rights reserved.
    $Id$
*/

/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#define RPCGEN_VERSION	199506

#include <rpc/rpc.h>

#ifndef FSCALE
/*
 * Scale factor for scaled integers used to count load averages.
 */
#define FSHIFT  8               /* bits to right of fixed binary point */
#define FSCALE  (1<<FSHIFT)

#endif /* ndef FSCALE */
#define CPUSTATES 4
#define DK_NDRIVE 4

struct rstat_timeval {
	u_int tv_sec;
	u_int tv_usec;
};
typedef struct rstat_timeval rstat_timeval;
#ifdef __cplusplus
extern "C" bool_t xdr_rstat_timeval(XDR *, rstat_timeval*);
#elif defined(__STDC__)
extern  bool_t xdr_rstat_timeval(XDR *, rstat_timeval*);
#else /* Old Style C */
bool_t xdr_rstat_timeval();
#endif /* Old Style C */


struct statstime {
	int cp_time[CPUSTATES];
	int dk_xfer[DK_NDRIVE];
	u_int v_pgpgin;
	u_int v_pgpgout;
	u_int v_pswpin;
	u_int v_pswpout;
	u_int v_intr;
	int if_ipackets;
	int if_ierrors;
	int if_oerrors;
	int if_collisions;
	u_int v_swtch;
	int avenrun[3];
	rstat_timeval boottime;
	rstat_timeval curtime;
	int if_opackets;
};
typedef struct statstime statstime;
#ifdef __cplusplus
extern "C" bool_t xdr_statstime(XDR *, statstime*);
#elif defined(__STDC__)
extern  bool_t xdr_statstime(XDR *, statstime*);
#else /* Old Style C */
bool_t xdr_statstime();
#endif /* Old Style C */


struct statsswtch {
	int cp_time[CPUSTATES];
	int dk_xfer[DK_NDRIVE];
	u_int v_pgpgin;
	u_int v_pgpgout;
	u_int v_pswpin;
	u_int v_pswpout;
	u_int v_intr;
	int if_ipackets;
	int if_ierrors;
	int if_oerrors;
	int if_collisions;
	u_int v_swtch;
	u_int avenrun[3];
	rstat_timeval boottime;
	int if_opackets;
};
typedef struct statsswtch statsswtch;
#ifdef __cplusplus
extern "C" bool_t xdr_statsswtch(XDR *, statsswtch*);
#elif defined(__STDC__)
extern  bool_t xdr_statsswtch(XDR *, statsswtch*);
#else /* Old Style C */
bool_t xdr_statsswtch();
#endif /* Old Style C */


struct stats {
	int cp_time[CPUSTATES];
	int dk_xfer[DK_NDRIVE];
	u_int v_pgpgin;
	u_int v_pgpgout;
	u_int v_pswpin;
	u_int v_pswpout;
	u_int v_intr;
	int if_ipackets;
	int if_ierrors;
	int if_oerrors;
	int if_collisions;
	int if_opackets;
};
typedef struct stats stats;
#ifdef __cplusplus
extern "C" bool_t xdr_stats(XDR *, stats*);
#elif defined(__STDC__)
extern  bool_t xdr_stats(XDR *, stats*);
#else /* Old Style C */
bool_t xdr_stats();
#endif /* Old Style C */


#define RSTATPROG ((u_long)100001)
#define RSTATVERS_TIME ((u_long)3)

#ifdef __cplusplus
#define RSTATPROC_STATS ((u_long)1)
extern "C" statstime * rstatproc_stats_3(void *, CLIENT *);
extern "C" statstime * rstatproc_stats_3_svc(void *, struct svc_req *);
#define RSTATPROC_HAVEDISK ((u_long)2)
extern "C" u_int * rstatproc_havedisk_3(void *, CLIENT *);
extern "C" u_int * rstatproc_havedisk_3_svc(void *, struct svc_req *);

#elif defined(__STDC__)
#define RSTATPROC_STATS ((u_long)1)
extern  statstime * rstatproc_stats_3(void *, CLIENT *);
extern  statstime * rstatproc_stats_3_svc(void *, struct svc_req *);
#define RSTATPROC_HAVEDISK ((u_long)2)
extern  u_int * rstatproc_havedisk_3(void *, CLIENT *);
extern  u_int * rstatproc_havedisk_3_svc(void *, struct svc_req *);

#else /* Old Style C */
#define RSTATPROC_STATS ((u_long)1)
extern  statstime * rstatproc_stats_3();
extern  statstime * rstatproc_stats_3_svc();
#define RSTATPROC_HAVEDISK ((u_long)2)
extern  u_int * rstatproc_havedisk_3();
extern  u_int * rstatproc_havedisk_3_svc();
#endif /* Old Style C */
#define RSTATVERS_SWTCH ((u_long)2)

#ifdef __cplusplus
extern "C" statsswtch * rstatproc_stats_2(void *, CLIENT *);
extern "C" statsswtch * rstatproc_stats_2_svc(void *, struct svc_req *);
extern "C" u_int * rstatproc_havedisk_2(void *, CLIENT *);
extern "C" u_int * rstatproc_havedisk_2_svc(void *, struct svc_req *);

#elif defined(__STDC__)
extern  statsswtch * rstatproc_stats_2(void *, CLIENT *);
extern  statsswtch * rstatproc_stats_2_svc(void *, struct svc_req *);
extern  u_int * rstatproc_havedisk_2(void *, CLIENT *);
extern  u_int * rstatproc_havedisk_2_svc(void *, struct svc_req *);

#else /* Old Style C */
extern  statsswtch * rstatproc_stats_2();
extern  statsswtch * rstatproc_stats_2_svc();
extern  u_int * rstatproc_havedisk_2();
extern  u_int * rstatproc_havedisk_2_svc();
#endif /* Old Style C */
#define RSTATVERS_ORIG ((u_long)1)

#ifdef __cplusplus
extern "C" stats * rstatproc_stats_1(void *, CLIENT *);
extern "C" stats * rstatproc_stats_1_svc(void *, struct svc_req *);
extern "C" u_int * rstatproc_havedisk_1(void *, CLIENT *);
extern "C" u_int * rstatproc_havedisk_1_svc(void *, struct svc_req *);

#elif defined(__STDC__)
extern  stats * rstatproc_stats_1(void *, CLIENT *);
extern  stats * rstatproc_stats_1_svc(void *, struct svc_req *);
extern  u_int * rstatproc_havedisk_1(void *, CLIENT *);
extern  u_int * rstatproc_havedisk_1_svc(void *, struct svc_req *);

#else /* Old Style C */
extern  stats * rstatproc_stats_1();
extern  stats * rstatproc_stats_1_svc();
extern  u_int * rstatproc_havedisk_1();
extern  u_int * rstatproc_havedisk_1_svc();
#endif /* Old Style C */

#endif /* !_RSTAT_H_RPCGEN */
