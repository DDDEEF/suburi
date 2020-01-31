#include <stdio.h>

int main(void){
  char *s = "ABCD";   //文字列リテラル
  char a[] = "ABCD";  //配列

  printf("sizeof s=%d a=%d\n", sizeof(s), sizeof(a));

  printf("s=%s a=%s\n", s, a);
  a[0] = 'X';
  printf("s=%s a=%s\n", s, a);
  s[0] = 'X';   // SEGVで落ちる
  printf("s=%s a=%s\n", s, a);

  return 0;
}
