#include <stdio.h>
#include <strings.h>
#include <rpc/rpc.h>
#include <stdlib.h>

#define BUF_SIZE  8192
#define RLS_PROG  ((u_long)0x20000000)
#define RLS_VER   ((u_long)1)
#define RLS_PROC  ((u_long)1)

int call_rls(char *host, char *buf, char **ans){
  int callrpc(char *, unsigned long, unsigned long, unsigned long, xdrproc_t, char *, xdrproc_t, char *);
  bool_t xdr_rls();
  enum clnt_stat clnt_stat;

  clnt_stat = callrpc(host, RLS_PROG, RLS_VER, RLS_PROC, (xdrproc_t)xdr_wrapstring, (char *)&buf, (xdrproc_t)xdr_wrapstring, (char *)ans);
  if(clnt_stat != 0){
    clnt_perrno(clnt_stat);
  }
  return(0);
}

int main(int argc, char *argv[]){
  char buf[BUF_SIZE];
  char *ans = NULL;

  if(argc <= 2){
    fprintf(stderr, "rls hostname path\n");
    exit(-1);
  }
  strcpy(buf, argv[2]);
  call_rls(argv[1], buf, &ans);
  if(ans != NULL){
    free(ans);
    ans = NULL;
  }else{
    printf("ans = NULL\n");
  }
  return(0);
}
