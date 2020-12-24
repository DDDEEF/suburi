#include <stdio.h>
#include <string.h>

/* 1.ポインタ変数が持つアドレスを整数型に変換 */
/* 2.その整数に数値と足す */
/* 3.整数型からポインタ型へ戻す */
/* 4.そのポインタ変数の指す値へアクセス */
/* 5.うまくいく... */

int main(){
  unsigned char* Addr;
  unsigned char test[1000];
  Addr = test;

  test[0] = 123;
  printf("test[0]  : value[%d] address[0x%x]  Addr[0]  : value[%d] address[0x%x]\n",test[0], &test[0], Addr[0], &Addr[0]);

  test[999] = 151;
  printf("test[999]: value[%d] address[0x%x]  Addr[999]: value[%d] address[0x%x]\n",test[999], &test[999], Addr[999], &Addr[999]);

  unsigned long dstAddr = (unsigned long)Addr;
  
  printf("before dstAddr value[0x%x]\n", dstAddr);
  dstAddr += 999;
  printf("after  dstAddr value[0x%x]\n", dstAddr);

  printf("dstAddr valude[%d]\n", *((unsigned char*)dstAddr));
}
