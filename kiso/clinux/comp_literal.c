#include <stdio.h>

int main(void){
  // 配列とポインタ
  int s[] = {2, 4};
  int *sp = s;
  // 複合リテラル
  int *p = (int []){2, 4};

  printf("%d %d\n", sp[0], sp[1]);
  printf("%d %d\n", p[0], p[1]);

  return 0;
}
