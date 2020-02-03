/*
 * 翻訳段階サンプルコード
 * マクロ展開とプログマ
 */

#include <stdio.h>

#define PRAGMA_STR(n) _Pragma(#n)
#define PRAGMA(n) PRAGMA_STR(pack(n))

int main(void){
  char *s = "\x1b[43m"
            "test"
            "\x1b[0m";

  PRAGMA(1);
  printf("%s\n", s);

  return 0;
}
