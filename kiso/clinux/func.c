#include <stdio.h>

void sub(void){
  printf("%s %d\n", __FILE__, __LINE__);
  printf("%s\n", __func__);
}

int main(void){
  sub();

  return 0;
}
