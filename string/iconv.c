#include <stdio.h>
#include <string.h>
#include <iconv.h>

int main(){
  char eucstr[512] = "あいうえおabcde";
  char sjisstr[512];
  iconv_t cd;
  size_t sleft;
  size_t dleft;
  size_t status;
  char *sp;
  char *dp;

  if((cd = iconv_open("SHIFT-JIS", "EUC-JP")) == (iconv_t*)-1){
    perror("iconv_open");
    return(-1);
  }
  sleft = strlen(eucstr);
  dleft = sizeof(sjisstr) - 1;
  for(sp = eucstr, dp = sjisstr; *sp != '\0'; ){
    status = iconv(cd, &sp, &sleft, &dp, &dleft);
    fprintf(stderr, "[%zu]\n", status);
  }
  iconv_close(cd);
  *dp = '\0';
  printf("sjisstr = %s\n", sjisstr);

  if((cd = iconv_open("EUC-JP", "SHIFT-JIS")) == (iconv_t*)-1){
    perror("iconv_open");
    return(-1);
  }
  sleft = strlen(sjisstr);
  dleft = sizeof(eucstr) - 1;
  for(sp = sjisstr, dp = eucstr; *sp != '\0'; ){
    status = iconv(cd, &sp, &sleft, &dp, &dleft);
    fprintf(stderr, "<%zu>\n", status);
  }
  iconv_close(cd);
  *dp = '\0';
  printf("eucstr = %s\n", eucstr);

  return(0);
}
