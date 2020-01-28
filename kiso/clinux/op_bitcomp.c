/*
 * 単項演算子
 */

#include <stdio.h>

int main(void){
  int val;
  int mask = 0x03;

  val = 0xdeadbeef;

  printf("%x\n", val & mask);
  printf("%x\n", val & ~mask);

  return 0;
}

