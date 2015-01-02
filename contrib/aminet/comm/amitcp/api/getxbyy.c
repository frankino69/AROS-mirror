/*
 * Copyright (c) 1993 AmiTCP/IP Group, <amitcp-group@hut.fi>
 *                    Helsinki University of Technology, Finland.
 *                    All rights reserved.
 * 
 * Created: Mon Apr 19 12:01:27 1993 too
 * Last modified: Thu Mar 24 21:02:19 1994 too
 *
 * HISTORY
 * $Log$
 * Revision 1.2  2001/12/26 19:30:19  henrik
 * Aros version
 *
 * Revision 1.1  2001/12/25 22:21:39  henrik
 *
 * Revision 1.11  1994/03/26  09:48:48  too
 * Fixed bug in getservbyname() to check given protocol string.
 * Cleaned getXbyname() calls to use matchAlias() function instead
 * of separate `for' loops, removing the need of `gotos'.
 *
 * Revision 1.10  1993/06/12  22:58:21  too
 * Moved allocDataBuffer into allocdatabuffer.[hc]
 *
 * Revision 1.9  1993/06/07  12:37:20  too
 * Changed inet_ntoa, netdatabase functions and WaitSelect() use
 * separate buffers for their dynamic buffers
 *
 * Revision 1.8  1993/06/01  16:37:20  too
 * removed reduntant hostbuf.h include. includes api/gethtbynamadr.h for
 * some prototypes
 *
 * Revision 1.7  1993/05/14  11:34:59  ppessi
 * Fixed NetDataBase locking.
 *
 * Revision 1.7  1993/05/14  11:34:59  ppessi
 * Fixed NetDataBase locking.
 *
 * Revision 1.6  93/05/05  16:09:40  16:09:40  puhuri (Markus Peuhkuri)
 * Fixes for final demo.
 * 
 * Revision 1.5  93/05/04  14:08:54  14:08:54  too (Tomi Ollila)
 * Changed local api function names to the same as the names given
 * to API programmer, but w/ starting _
 * 
 * Revision 1.4  93/05/04  12:12:04  12:12:04  jraja (Jarno Tapio Rajahalme)
 * fix.
 * 
 * Revision 1.3  93/05/02  17:28:52  17:28:52  jraja (Jarno Tapio Rajahalme)
 * Added Obtain & ReleaseSemaphores around NDB usage,
 * moved Forbid()/Permit() inner.
 * 
 * Revision 1.2  93/04/28  13:49:06  13:49:06  too (Tomi Ollila)
 * Moved macro HOSTBUF and inline function stpcpy() to hostbuf.h
 * includes kern/amiga_netdb.h instead of kern/amiga_config.h
 * 
 * Revision 1.1  93/04/27  10:23:20  10:23:20  too (Tomi Ollila)
 * Initial revision
 * 
 *
 */

#include <conf.h>

#include <sys/param.h>
#include <sys/systm.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <kern/amiga_includes.h>

#include <api/amiga_api.h>
#include <api/amiga_libcallentry.h>
#include <kern/amiga_netdb.h>
#include <api/allocdatabuffer.h>

#include <api/gethtbynamadr.h> /* prototypes (NO MORE BUGS HERE) */

int strcasecmp(const char *, const char *);

#if __SASC
#define strcasecmp stricmp
#endif


static long copyGenent(struct SocketBase * libPtr, 
		       struct DataBuffer * DB,
		       struct GenentNode *ent)
{
  long diff;

  if (allocDataBuffer(DB, ent->gn_EntSize) == FALSE) {
    writeErrnoValue(libPtr, ENOMEM);
    return 0;
  }
  
  /*
   * how much to add to old pointers
   */
  diff = (caddr_t)DB->db_Addr - (caddr_t)&ent->gn_Ent;

  /*
   * copy given ent verbatim
   */
  bcopy((caddr_t)&ent->gn_Ent, DB->db_Addr, ent->gn_EntSize);

  return diff;
}

 
/*
 * Host queries if Nameserver is not in use *****************************
 */

/*
 * Match name in aliaslist, used by `...byname()' -queries
 */

static BOOL matchAlias(char ** aliases, const char * name)
{
  for ( ; *aliases != 0; aliases++)
    if (strcmp(*aliases, name) == 0)
      return TRUE;

  return FALSE;
}
  

/*
 * Makehostent() must be called when NDB_Semaphore is obtained.
 */
static struct hostent * makehostent(struct SocketBase * libPtr,
				    struct HostentNode * ent)
{
  long diff;
  short i;

  if ((diff = copyGenent(libPtr, &libPtr->hostents,
			 (struct GenentNode *)ent)) == 0)
    return NULL; /* failed to allocate memory */

  /*
   * patch pointers
   */
#define HOSTENT ((struct hostent *)libPtr->hostents.db_Addr)
  HOSTENT->h_name += diff;

  HOSTENT->h_aliases = (char **)((caddr_t)HOSTENT->h_aliases + diff);
  for (i = 0; HOSTENT->h_aliases[i]; i++)
    HOSTENT->h_aliases[i] += diff;
  /* NULL remains null */

  HOSTENT->h_addr_list = (char **)((caddr_t)HOSTENT->h_addr_list + diff);
  for (i = 0; HOSTENT->h_addr_list[i]; i++)
    HOSTENT->h_addr_list[i] += diff;
  /* NULL remains null */

  return HOSTENT;
#undef HOSTENT
}


struct hostent * _gethtbyname(struct SocketBase * libPtr,
			      const char * name)
{
  struct HostentNode * entNode;
  struct hostent * host;

  LOCK_R_NDB(NDB);

  for (entNode = (struct HostentNode *)NDB->ndb_Hosts.mlh_Head;
       entNode->hn_Node.mln_Succ;
       entNode = (struct HostentNode *)entNode->hn_Node.mln_Succ)
    if (strcasecmp(entNode->hn_Ent.h_name, (char *)name) == 0 ||
	matchAlias(entNode->hn_Ent.h_aliases, name)) {
      host = makehostent(libPtr, entNode);
      UNLOCK_NDB(NDB);
      return host;
    }
  UNLOCK_NDB(NDB);
  writeErrnoValue(libPtr, 0);
  return NULL;
}


struct hostent * _gethtbyaddr(struct SocketBase * libPtr,
			      const char * addr, int len, int type)
{
  struct HostentNode * entNode;
  struct hostent * host;

  LOCK_R_NDB(NDB);
  for (entNode = (struct HostentNode *)NDB->ndb_Hosts.mlh_Head;
       entNode->hn_Node.mln_Succ;
       entNode = (struct HostentNode *)entNode->hn_Node.mln_Succ)
    if (entNode->hn_Ent.h_addrtype == type &&
	! bcmp(entNode->hn_Ent.h_addr, addr, len)) {
      host = makehostent(libPtr, entNode);
      UNLOCK_NDB(NDB);
      return host;
    }
  UNLOCK_NDB(NDB);
  writeErrnoValue(libPtr, 0);
  return NULL;
}


/*
 * Network queries ****************************************************
 */


/*
 * Makenetent() must be called when NDB_Semaphore is obtained.
 */
static struct netent * makenetent(struct SocketBase * libPtr,
				  struct NetentNode * ent)
{
  long diff;
  short i;

  if ((diff = copyGenent(libPtr, &libPtr->netents,
			 (struct GenentNode *)ent)) == 0)
    return NULL;

  /*
   * patch pointers
   */
#define NETENT ((struct netent *)libPtr->netents.db_Addr)
  NETENT->n_name += diff;

  NETENT->n_aliases = (char **)((caddr_t)NETENT->n_aliases + diff);
  for (i = 0; NETENT->n_aliases[i]; i++)
    NETENT->n_aliases[i] += diff;
  /* NULL remains null */

  return NETENT;
#undef NETENT
}  


struct netent * SAVEDS RAF2(_getnetbyname,
		     struct SocketBase *,	libPtr,	a6,
		     const char *,		name,	a0)
#if 0
{
#endif
  struct NetentNode * entNode;
  struct netent * net;
  
  CHECK_TASK2();

  LOCK_R_NDB(NDB);
  for (entNode = (struct NetentNode *)NDB->ndb_Networks.mlh_Head;
       entNode->nn_Node.mln_Succ;
       entNode = (struct NetentNode *)entNode->nn_Node.mln_Succ)
    if (strcmp(entNode->nn_Ent.n_name, name) == 0 ||
	matchAlias(entNode->nn_Ent.n_aliases, name)) {
      net = makenetent(libPtr, entNode);
      UNLOCK_NDB(NDB);
      return net;
    }
  UNLOCK_NDB(NDB);
  writeErrnoValue(libPtr, 0);
  return NULL;
}

struct netent * SAVEDS RAF3(_getnetbyaddr,
		     struct SocketBase *,	libPtr,	a6,
		     long,			netw,	d0,
		     long,			type,	d1)
#if 0
{
#endif
  struct NetentNode * entNode;
  struct netent * net;

  CHECK_TASK2();

  LOCK_R_NDB(NDB);
  for (entNode = (struct NetentNode *)NDB->ndb_Networks.mlh_Head;
       entNode->nn_Node.mln_Succ;
       entNode = (struct NetentNode *)entNode->nn_Node.mln_Succ)
    if (entNode->nn_Ent.n_addrtype == type && entNode->nn_Ent.n_net == netw) {
      net = makenetent(libPtr, entNode);
      UNLOCK_NDB(NDB);
      return net;
    }
  UNLOCK_NDB(NDB);
  writeErrnoValue(libPtr, 0);
  return NULL;
}


/*
 * Service queries ****************************************************
 */

/*
 * Makeservent() must be called when NDB_Semaphore is obtained.
 */
static struct servent * makeservent(struct SocketBase * libPtr,
				    struct ServentNode * ent)
{
  long diff;
  short i;

  if ((diff = copyGenent(libPtr, &libPtr->servents,
			 (struct GenentNode *)ent)) == 0)
    return NULL;

  /*
   * patch pointers
   */
#define SERVENT ((struct servent *)libPtr->servents.db_Addr)
  SERVENT->s_name += diff;

  SERVENT->s_aliases = (char **)((caddr_t)SERVENT->s_aliases + diff);
  for (i = 0; SERVENT->s_aliases[i]; i++)
    SERVENT->s_aliases[i] += diff;
  /* NULL remains null */

  SERVENT->s_proto += diff;

  return SERVENT;
#undef SERVENT
}  


/*
 * findservent is needed for external call.
 */
struct ServentNode * findServentNode(struct NetDataBase * ndb,
				     const char * name, const char * proto)
{
  struct ServentNode * entNode;
  
  for (entNode = (struct ServentNode *)ndb->ndb_Services.mlh_Head;
       entNode->sn_Node.mln_Succ;
       entNode = (struct ServentNode *)entNode->sn_Node.mln_Succ)
    if ((strcmp(entNode->sn_Ent.s_name, name) == 0 ||
	 matchAlias(entNode->sn_Ent.s_aliases, name)) &&
	(proto == NULL || strcmp(entNode->sn_Ent.s_proto, proto) == 0))
      return entNode;

  return NULL;
}
  


struct servent * SAVEDS RAF3(_getservbyname,
		     struct SocketBase *,	libPtr,	a6,
		     const char *,		name,	a0,
		     const char *,		proto,	a1)
#if 0
{
#endif
  struct ServentNode * entNode;
  struct servent * serv;
  
  CHECK_TASK2();

  LOCK_R_NDB(NDB);
  if ((entNode = findServentNode(NDB, name, proto)) != NULL) {
    serv = makeservent(libPtr, entNode);
    UNLOCK_NDB(NDB);
    return serv;
    }
  UNLOCK_NDB(NDB);
  writeErrnoValue(libPtr, 0);
  return NULL;
}

struct servent * SAVEDS RAF3(_getservbyport,
		     struct SocketBase *,	libPtr,	a6,
		     LONG,			port,	d0,
		     const char *,		proto,	a0)
#if 0
{
#endif
  struct ServentNode * entNode;
  struct servent * serv;
  
  CHECK_TASK2();

  LOCK_R_NDB(NDB);
  for (entNode = (struct ServentNode *)NDB->ndb_Services.mlh_Head;
       entNode->sn_Node.mln_Succ;
       entNode = (struct ServentNode *)entNode->sn_Node.mln_Succ)
    if (entNode->sn_Ent.s_port == port &&
	(proto == NULL || strcmp(entNode->sn_Ent.s_proto, proto) == 0)) {
      serv = makeservent(libPtr, entNode);
      UNLOCK_NDB(NDB);
      return serv;
    }

  UNLOCK_NDB(NDB);
  writeErrnoValue(libPtr, 0);
  return NULL;
}


/*
 * Protocol queries ****************************************************
 */

/*
 * Makeprotoent() must be called when NDB_Semaphore is obtained.
 */
static struct protoent * makeprotoent(struct SocketBase * libPtr,
				      struct ProtoentNode * ent)
{
  long diff;
  short i;

  if ((diff = copyGenent(libPtr, &libPtr->protoents,
			 (struct GenentNode *)ent)) == 0)
    return NULL;

  /*
   * patch pointers
   */
#define PROTOENT ((struct protoent *)libPtr->protoents.db_Addr)
  PROTOENT->p_name += diff;

  PROTOENT->p_aliases = (char **)((caddr_t)PROTOENT->p_aliases + diff);
  for (i = 0; PROTOENT->p_aliases[i]; i++)
    PROTOENT->p_aliases[i] += diff;
  /* NULL remains null */

  return PROTOENT;
#undef PROTOENT
}  

struct protoent * SAVEDS RAF2(_getprotobyname,
		       struct SocketBase *,	libPtr,	a6,
		       const char *,		name,	a0)
#if 0
{
#endif
  struct ProtoentNode * entNode;
  struct protoent * proto;
  
  CHECK_TASK2();

  LOCK_R_NDB(NDB);
  for (entNode = (struct ProtoentNode *)NDB->ndb_Protocols.mlh_Head;
       entNode->pn_Node.mln_Succ;
       entNode = (struct ProtoentNode *)entNode->pn_Node.mln_Succ)
    if (strcmp(entNode->pn_Ent.p_name, name) == 0 ||
	matchAlias(entNode->pn_Ent.p_aliases, name)) {
      proto = makeprotoent(libPtr, entNode);
      UNLOCK_NDB(NDB);
      return proto;
    }
  UNLOCK_NDB(NDB);
  writeErrnoValue(libPtr, 0);
  return NULL;
}

struct protoent * SAVEDS RAF2(_getprotobynumber,
		       struct SocketBase *,	libPtr,	a6,
		       long,			protoc,	a0)
#if 0
{
#endif
  struct ProtoentNode * entNode;
  struct protoent * proto;

  CHECK_TASK2();

  LOCK_R_NDB(NDB);
  for (entNode = (struct ProtoentNode *)NDB->ndb_Protocols.mlh_Head;
       entNode->pn_Node.mln_Succ;
       entNode = (struct ProtoentNode *)entNode->pn_Node.mln_Succ)
    if (entNode->pn_Ent.p_proto == protoc) {
      proto = makeprotoent(libPtr, entNode);
      UNLOCK_NDB(NDB);
      return proto;
    }

  UNLOCK_NDB(NDB);
  writeErrnoValue(libPtr, 0);
  return NULL;
}
