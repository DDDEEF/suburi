/*
 * 変数のデータ型 
 */

#include <stdio.h>

int main(void){
  char c;
  short s;
  int i;
  long l;
  long long ll;
  void *pv;
  int *pi;
  long *pl;

  /* 整数型のサイズ */
  printf("char %d short %d int %d long %d long long %d\n", sizeof(c), sizeof(s), sizeof(i), sizeof(l), sizeof(ll));

  /* ポインタのサイズ */
  printf("void* %d int* %d long* %d\n", sizeof(pv), sizeof(pi), sizeof(pl));

  return 0;
}

