#include <stdio.h>

int sum(int x, int y){
  return x + y;
}

int mul(int x, int y){
  return x * y;
}

void keisan(int (*calc)(int, int)){
  int x = 10;
  int y = 20;
  printf("%d\n", (*calc)(x, y));
}

int main(void){
  keisan(sum);
  keisan(mul);
}
