#include <stdio.h>
#include <string.h>
#include <iconv.h>
#include "log.h"
#include "jconv.h"

/* EUC-JP を SJIS 変換関数 */
int ujtosj(char *to, int tosize, char *from){
  iconv_t cd;
  size_t sleft;
  size_t dleft;
  size_t status;
  char *sp;
  char *dp;

  if((cd = iconv_open("SJIS", "eucJP")) == (iconv_t*)-1){
    SyslogPerror(LOG_ERR, "iconv_open");
    return(-1);
  }

  sleft = strlen(from);
  dleft = tosize - 1;
  for(sp = from, dp = to; *sp != '\0'; ){
    if((status = iconv(cd, &sp, &sleft, &dp, &dleft)) == (size_t)(-1)){
      SyslogPerror(LOG_ERR, "iconv");
      iconv_close(cd);
      return(-1);
    }
  }
  iconv_close(cd);
  *dp = '\0';

  return(0);
}

/* SJIS を EUC-JP 変換関数 */
int sjtouj(char *to, int tosize, char *from){
  iconv_t cd;
  size_t sleft;
  size_t dleft;
  size_t status;
  char *sp;
  char *dp;

  if((cd = iconv_open("eucJP", "SJIS")) == (iconv_t*)-1){
    SyslogPerror(LOG_ERR, "iconv_open");
    return(-1);
  }

  sleft = strlen(from);
  dleft = tosize - 1;
  for(sp = from, dp = to; *sp != '\0'; ){
    if((status = iconv(cd, &sp, &sleft, &dp, &dleft)) == (size_t)(-1)){
      SyslogPerror(LOG_ERR, "iconv");
      iconv_close(cd);
      return(-1);
    }
  }
  iconv_close(cd);
  *dp = '\0';

  return(0);
}
