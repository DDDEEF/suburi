#include <stdio.h>

int main(void){
  unsigned char value = 240;
  
  value = value >> 3; /* 3bit右へシフト */

  printf("before = 240, after = %d\n", value);
}
