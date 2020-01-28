/*
 * ビット演算子
 */

#include <stdio.h>

int main(void){
  int num = 0xf0f0f0f0;
  unsigned int unum = 0xf0f0f0f0f;
  unsigned char buf = 0x8f;
  unsigned long val;

  // numは算術シフト unumは論理シフトになる。
  printf("%0x %0x\n", num >> 1, unum >> 1);

  // buf<<24はsigned intに拡張された後、unsigned longに拡張される。
  val = buf << 24;
  printf("%016lx\n", val);

  // buf<<24はunsigned longで計算される。
  val = (unsigned long)buf << 24;
  printf("%016lx\n", val);

  return 0;
}
