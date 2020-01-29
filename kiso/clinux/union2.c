/*
 * 共用体を使わないバージョン
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>

struct sample_un{
  unsigned char reg;
};

int main(void){
  struct sample_un data;
  int i;
  int val;

  memset(&data, 0, sizeof(data));

  printf("sizeof %d\n", sizeof(data));
  printf("offset reg %d\n", offsetof(struct sample_un, reg));

  data.reg = 0xc8;

  printf("0x%02x = ", data.reg);
  for(i = 0; i < 8; i++){
    val = data.reg & (1 << (7-i));
    printf("%d", val ? 1 : 0);
  }
  printf("\n");

  return 0;
}
