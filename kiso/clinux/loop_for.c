/*
 * forループ
 */

#include <stdio.h>

int main(void){
  int i = 100;

  printf("%d\n", i);
  for(i = 0; i < 10; i++){
    printf("%d ", i);
  }

  printf("\n%d\n", i);

  return 0;
}
