#include <stdio.h>

char *sub(void){
  char s[] = "test";

  printf("%s\n", s);

  return s;
}

int main(void){
  printf("%s\n", sub());

  return 0;
}
