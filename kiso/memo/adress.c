#include <stdio.h>

int func(int value, int *ptr){
  printf("func()\n");
  printf("value[%d] &value[0x%x] ptr[0x%0x] &ptr[0x%x]\n", value, &value, ptr, &ptr);
}

int main(void){
  int value = 0;
  int *ptr;
  ptr = &value;

  printf("main()\n");
  printf("value[%d] &value[0x%x] *ptr[%d] ptr[0x%0x] &ptr[0x%x]\n", value, &value,  *ptr, ptr, &ptr);

  func(value, ptr);
}
