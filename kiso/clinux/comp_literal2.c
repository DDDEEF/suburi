#include <stdio.h>

// 複合リテラル(グローバル変数)
int *g_p = (int []){1, 3};

int *sub(void){
  // 複合リテラルを返す?
  return (int []){0, 9};
}

int main(void){
  // 複合リテラル(ローカル変数)
  int *p = (int []){2, 4};
  int *q;

  printf("g_p %p p %p\n", g_p, q);

  q = sub();
  printf("%p %d %d\n", q, q[0], q[1]);

  getchar();

  return 0;
}
