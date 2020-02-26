#include <stdio.h>
#include <stdlib.h>

size_t sub(int n){
  char *buf[n*2];     // 可変長配列

  return sizeof(buf);
}

int main(int argc, char **argv){
  if(argc == 2){
    size_t ret = sub(atoi(argv[1]));
    printf("%u\n", ret);
  }

  return 0;
}
