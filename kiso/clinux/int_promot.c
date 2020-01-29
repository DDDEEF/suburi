/*
 * 汎整数拡張
 */

#include <stdio.h>

int main(void){
  char a;
  int ix;
  int iy;
  unsigned char c;
  unsigned char d;

  /* (1) */
  a = 0x80;   // signed char に変化しているから注意
  ix = 0x81;
  iy = a + ix;  // aがintに格上げ
  printf("%0x + %0x = %0x\n\n", a, ix, iy);

  /* (2-1) */
  c = 0x7f;
  d = (~c)>>4;    // intに格上げして右シフト
  printf("%0x\n\n", d); // 0x08にはならない

  /* (2-2) */
  c = 0x7f;
  ix = ~c;  //ffffff80
  printf("ix %0x\n", ix);
  ix = ix >> 4; //fffffff8
  printf("ix %0x\n", ix);
  iy = ix & 0xff; //f8
  printf("iy %0x\n", iy);
  d = iy; //f8
  printf("d %0x\n", d);

  return 0;
}
