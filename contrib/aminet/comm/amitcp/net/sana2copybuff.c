/*
 * Copyright (c) 1993 AmiTCP/IP Group, <amitcp-group@hut.fi>,
 *                    Helsinki University of Technology, Finland.
 *                    All rights reserved.
 *
 * sana2copybuff.c - Buffer Management Routines for Sana-II Interfaces
 *
 * Last modified: Sun Nov  7 01:37:49 1993 ppessi
 *
 * HISTORY
 * $Log$
 * Revision 1.1  2001/12/25 22:28:13  henrik
 * amitcp
 *
 * Revision 1.15  1993/12/20  18:06:41  jraja
 * Added more robust version of ioip_alloc_mbuf().
 * Added more detail to "mbuf chain short" message.
 *
 * Revision 1.13  1993/11/06  23:39:15  ppessi
 * Added more information to "mbuf chain short" error message.
 *
 * Revision 1.12  1993/06/04  11:16:15  jraja
 * Fixes for first public release.
 *
 * Revision 1.11  1993/05/16  21:09:43  ppessi
 * RCS version changed.
 *
 * Revision 1.10  1993/05/05  16:10:38  puhuri
 * Fixed cluster allocation code.
 *
 * Revision 1.9  93/04/26  11:53:11  11:53:11  too (Tomi Ollila)
 * Changed include paths of amiga_api.h, amiga_libcallentry.h and amiga_raf.h
 * from kern to api
 * 
 * Revision 1.8  93/04/24  22:46:13  22:46:13  jraja (Jarno Tapio Rajahalme)
 * Removed Define for USECLUSTERS
 * 
 * Revision 1.7  93/04/13  22:22:56  22:22:56  jraja (Jarno Tapio Rajahalme)
 * Changed return from buffer allocation function back to recent form.
 * 
 * Revision 1.6  93/04/12  09:20:40  09:20:40  jraja (Jarno Tapio Rajahalme)
 * Changed reserved mbuf chain so that all mbufs after the header have 
 * clusters.
 * 
 * Revision 1.5  93/04/05  17:46:26  17:46:26  jraja (Jarno Tapio Rajahalme)
 * Changed spl storage variables to spl_t.
 * Changed every .c file to use conf.h.
 * 
 * Revision 1.4  93/03/20  07:11:55  07:11:55  ppessi (Pekka Pessi)
 * Fixed mbuf allocating for headers
 * 
 * Revision 1.3  93/03/05  19:51:16  19:51:16  jraja (Jarno Tapio Rajahalme)
 * Fixed includes (again).
 * 
 * Revision 1.2  93/02/28  22:21:57  22:21:57  ppessi (Pekka Pessi)
 * Made to compile; used RAFn macros.
 * 
 * Revision 1.1  93/02/25  14:34:29  14:34:29  ppessi (Pekka Pessi)
 * Initial revision
 */

#include <conf.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/syslog.h>
#include <sys/synch.h>

#include <net/if.h>

#if INET
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#endif

#include <net/if_sana.h>
#include <api/amiga_raf.h>

/*
 * allocate mbufs for the size MTU at free_chain for read request
 */
#if 0 /* old one */
BOOL
ioip_alloc_mbuf(struct IOIPReq *s2rp, ULONG MTU)
{
  register struct mbuf *m, *n;
  register int len = 0;

  n = s2rp->ioip_reserved;

  /* Check for packet header */
  if (n && (n->m_flags & M_PKTHDR)) {
    /* There is already a full packet  */
    return TRUE;
  }

  /* Prepend by a packet header */
  MGETHDR(m, M_NOWAIT, MT_HEADER);
  if (m) { 
    m->m_len = len = MHLEN;
    s2rp->ioip_reserved = m;
    m->m_next = n;
    
    /* Find the end of the free chain */ /* ASSUME THAT THESE HAVE CLUSTERS */
    while (n = m->m_next) {
      len += n->m_len; m = n;
    } 
    
    /*
     * add new (cluster)mbufs to get the desired size
     */
    while (len < MTU) {
      MGET(n, M_NOWAIT, MT_DATA);
      if (n != NULL) {
	MCLGET(n, M_NOWAIT);
	if (n->m_ext.ext_buf != NULL) {
	  n->m_len = n->m_ext.ext_size;
	  len += n->m_ext.ext_size;
	}
	else {
	  m_free(n);
	  break;
	}
	m = m->m_next = n;
      }
      else
	break;
    }
    
    s2rp->ioip_reserved->m_pkthdr.len = len;
  }
  if (len < MTU) { 
    m_freem(s2rp->ioip_reserved);
    s2rp->ioip_reserved = NULL;
    return FALSE;
  }

  return TRUE;
}
#else
BOOL
ioip_alloc_mbuf(struct IOIPReq *s2rp, ULONG MTU)
{
  register struct mbuf *m, *n;
  register int len;

  /*
   * s2rp->ioip_reserved is either NULL, or an mbuf chain, possibly having
   * packet header in the first one.
   */
  n = s2rp->ioip_reserved;

  /* Check for packet header */
  if (n && (n->m_flags & M_PKTHDR)) {
    /*
     * chain already has the packet header
     */
    m = n;
    len = m->m_len;
  }
  else {
    /* Prepend by a packet header */
    MGETHDR(m, M_NOWAIT, MT_HEADER);
    if (m) { 
      m->m_len = len = MHLEN;
      s2rp->ioip_reserved = m;
      m->m_next = n;
    }
    else
      goto fail;
  }
  /*
   * Now m points to the start of the mbuf chain. The first mbuf has
   * a packet header. 
   */

  /* Find the end of the free chain */ /* ASSUME THAT THESE HAVE CLUSTERS */
  while (n = m->m_next) {
    len += n->m_len; m = n;
  } 
    
  /*
   * Now len has the total length of the mbuf chain, add new 
   * (cluster)mbufs to get the desired size (MTU).
   */
  while (len < MTU) {
    MGET(n, M_NOWAIT, MT_DATA);
    if (n != NULL) {
      MCLGET(n, M_NOWAIT);
      if (n->m_ext.ext_buf != NULL) {
	len += n->m_len = n->m_ext.ext_size;
      }
      else {
	m_free(n);
        goto fail;
      }
      m = m->m_next = n;
    }
    else
      goto fail;
  }
  s2rp->ioip_reserved->m_pkthdr.len = len;
  return TRUE;

 fail:
  m_freem(s2rp->ioip_reserved);
  s2rp->ioip_reserved = NULL;
  return FALSE;
}
#endif

/*
 * Copy data from an mbuf chain starting from the beginning,
 * continuing for "n" bytes, into the indicated continuous buffer.
 *
 * NOTE: this WILL be called from INTERRUPTS, so compile with stack checking
 *       disabled and use __saveds if near data is needed.
 */
static BOOL __saveds __interrupt RAF3(m_copy_from_mbuf,
				      BYTE*,          to,   a0,
				      struct IOIPReq*,from, a1,
				      ULONG,          n,    d0)
#if 0
{
#endif
  register struct mbuf *m = from->ioip_packet;
  register unsigned count;

  while (n > 0) 
    {
#if DIAGNOSTIC
      if (m == 0) 
	{
	  log(LOG_ERR, "m_copy_from_buff: mbuf chain short");
	  return FALSE;
	}
#endif
      count = MIN(m->m_len, n);
      bcopy(mtod(m, caddr_t), to, count);
      n -= count;
      to += count;
      m = m->m_next;
    }
  return TRUE;
}

/*
 * Copy data from an continuous buffer 'from' to preallocated mbuf chain
 * starting from the beginning, continuing for "n" bytes.
 * Mbufs in the preallocated chain must have their m_len field set to maximum
 * amount of data that they can have.
 * 
 * NOTE: this WILL be called from INTERRUPTS, so compile with stack checking
 *       disabled and use __saveds if near data is needed.
 */
static BOOL __saveds __interrupt RAF3(m_copy_to_mbuf,
				      struct IOIPReq*,to,   a0,
				      BYTE*,          from, a1,
				      ULONG,          n,    d0)
#if 0
{
#endif
  register struct mbuf *f, *m = to->ioip_reserved;
  unsigned totlen = n;

#if DIAGNOSTIC
  if (!(m->m_flags & M_PKTHDR)) {
    log(LOG_ERR, "m_copy_to_buff: mbuf chain has no header");
    return FALSE;
  }
#endif

  while (n > 0) {
#if DIAGNOSTIC
    if (m == 0) {
      log(LOG_ERR, "m_copy_to_buff: mbuf chain short, "
	  "packet len =%lu, reserved =%lu, "
	  "wiretype =%lu, mtu =%lu",
	  totlen, to->ioip_reserved->m_pkthdr.len,
	  to->ioip_s2.ios2_PacketType,
	  (ULONG)to->ioip_if->ss_if.if_mtu);
      return FALSE;
    }
#endif
    if (n < m->m_len)
      m->m_len = n;
    bcopy(from, mtod(m, caddr_t), m->m_len);
    from += m->m_len;
    n -= m->m_len;
    if (n > 0)
      m = m->m_next;
  }

  /*
   * move the packet to the field 'ioip_packet',
   * set total length of the packet and terminate it.
   */
  f = m->m_next;		/* first free mbuf */
  m->m_next = NULL;		/* terminate the chain */

  to->ioip_packet = to->ioip_reserved;
  to->ioip_packet->m_pkthdr.len = totlen; /* set packet length */
  to->ioip_reserved = f;		/* leftover mbufs */

  /*
   * More mbuf flags and interface pointer must be set later
   */
  return TRUE;
}

struct TagItem buffermanagement[3] = {
    { S2_CopyToBuff,   (ULONG)m_copy_to_mbuf },
    { S2_CopyFromBuff, (ULONG)m_copy_from_mbuf },
    { TAG_END, }
};

