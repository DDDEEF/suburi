#include <sys/types.h>
#include <dirent.h>
#include <rpc/rpc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <rpcsvc/rusers.h>

#define BUF_SIZE  8192
#define RLS_PROG  ((u_long)0x20000000)  //プログラム番号(0x20000000〜0x3FFFFFFFが使用可能)
#define RLS_VER   ((u_long)1)           //バージョン番号
#define RLS_PROC  ((u_long)1)           //関数番号

int registerrpc(u_long, u_long, u_long, char *(*)(), xdrproc_t, xdrproc_t);
char **do_rls(char **);

char **do_rls(char **buf){
  DIR *dirp;
  struct dirent *dp;
  char tmp[512];
  int len;
  char *ptr;
  static char *ret_buf = NULL;

  if(ret_buf != NULL){
    free(ret_buf);
    ret_buf = NULL;
  }
  ret_buf = (char *)calloc(BUF_SIZE, sizeof(char));

  dirp = opendir(*buf);
  if(dirp == NULL){
    strcpy(ret_buf, "opendir error\n");
    fprintf(stderr, "ret_buf = %lu:%s\n", strlen(ret_buf), ret_buf);
    return(&ret_buf);
  }
  ptr = ret_buf;
  while((dp = readdir(dirp))){
    snprintf(tmp, sizeof(tmp), "%s/%s\n", *buf, dp->d_name);
    len = strlen(tmp);
    if((ptr + len) >= (ret_buf + BUF_SIZE)){
      fprintf(stderr, "*** buffer full ***\n");
      break;
    }
    strcpy(ptr, tmp);
    ptr += len;
  }
  *ptr = '\0';

  closedir(dirp);

  fprintf(stderr, "ret_buf = %lu:%s\n", strlen(ret_buf), ret_buf);
  return(&ret_buf);
}

int main(){
  if(registerrpc(RLS_PROG, RLS_VER, RLS_PROC, (char *(*)())do_rls, (xdrproc_t)xdr_wrapstring, (xdrproc_t)xdr_wrapstring) == -1){
    perror("registerrpc");
    return(-1);
  }
  fprintf(stderr, "RLS_PROG = %lx:%ld\n", RLS_PROG, RLS_PROG);
  svc_run();
  return(0);
}
