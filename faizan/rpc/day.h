/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DAY_H_RPCGEN
#define _DAY_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define DAYPRG 0x085
#define DAYVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define day 1
extern  char ** day_1(void *, CLIENT *);
extern  char ** day_1_svc(void *, struct svc_req *);
extern int dayprg_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define day 1
extern  char ** day_1();
extern  char ** day_1_svc();
extern int dayprg_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DAY_H_RPCGEN */
