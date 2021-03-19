#include "mylib.h"

/* 末尾の改行'\n'を'\0'に置き換える                  */
/* str    改行文字で終わっているかもしれない文字列   */
/* len    処理の制限                                 */
/* return 与えられた文字列の先頭アドレス             */
char *chop_newline(char *str, int len)
{
  int n = strlen(str);

  /* 末尾が改行文字なら削る */
  if(n < len && str[n-1] == '\n'){
    str[n-1] = '\0';
  }

  /* 先頭番地を返す */
  return str;
}