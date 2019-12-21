#include <stdio.h>
#include <string.h>
#include <iconv.h>

int main(){
  char utf8str[512] = "あいうえおabcde";
  char sjisstr[512];
  iconv_t cd;
  size_t sleft;
  size_t dleft;
  size_t status;
  char *sp;
  char *dp;

  /* 固有のUTF-8文字列をSJISに変換 */
  if((cd = iconv_open("SHIFT-JIS", "UTF-8")) == (iconv_t*)-1){
    perror("iconv_open");
    return(-1);
  }
  sleft = strlen(utf8str);
  dleft = sizeof(sjisstr) - 1;
  for(sp = utf8str, dp = sjisstr; *sp != '\0'; ){
    status = iconv(cd, &sp, &sleft, &dp, &dleft);
    fprintf(stderr, "[%zu]\n", status);
  }
  iconv_close(cd);
  *dp = '\0';
  printf("sjisstr = %s\n", sjisstr);

  /* UTF-8に戻す */
  if((cd = iconv_open("UTF-8", "SHIFT-JIS")) == (iconv_t*)-1){
    perror("iconv_open");
    return(-1);
  }
  sleft = strlen(sjisstr);
  dleft = sizeof(utf8str) - 1;
  for(sp = sjisstr, dp = utf8str; *sp != '\0'; ){
    status = iconv(cd, &sp, &sleft, &dp, &dleft);
    fprintf(stderr, "<%zu>\n", status);
  }
  iconv_close(cd);
  *dp = '\0';
  printf("utf8str = %s\n", utf8str);

  return(0);
}
