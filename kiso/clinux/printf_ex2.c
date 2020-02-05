#include <stdio.h>
#include <unistd.h>

int main(void){
  daemon(0, 0);

  printf("hello, world.\n");

  return 0;
}
