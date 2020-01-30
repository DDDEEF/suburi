/*
 * do-whileのマクロ
 */

#include <stdio.h>

#define SUB(n) do{\
  n++;\
  n *= 10;\
}while(0)

int main(void){
  int a = 3;

  printf("%d\n", a);
  if(a > 0){
    SUB(a);
  }else{
    a = 0;
  }
  printf("%d\n", a);

  return 0;
}
