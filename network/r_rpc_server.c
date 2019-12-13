#include <rpc/rpc.h>
#include <sys/dir.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include "rls.h"

rls_res *rls_1_svc(nametype *dirname, struct svc_req *req){
  namelist nl;
  namelist *nlp;
  static rls_res res;   /* must be static! */
  static DIR *dirp = NULL;
  struct direct *d;

  if(dirp){
    xdr_free((xdrproc_t)xdr_rls_res, (char *)&res);
  }
  dirp = opendir(*dirname);
  if(dirp == NULL){
    res.err_no = errno;
    return(&res);
  }
  nlp = (&res.rls_res_u.list);
  while((d = readdir(dirp))){
    nl = (*nlp) = (namenode *)malloc(sizeof(namenode));
    nl->name = strdup(d->d_name);
    nlp = (&nl->pNext);
  }
  (*nlp) = NULL;
  res.err_no = 0;
  closedir(dirp);

  return(&res);
}
