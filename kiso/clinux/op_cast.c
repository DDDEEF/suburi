/*
 * キャスト演算子
 */ 

#include <stdio.h>

int main(void){
  char *cp = NULL;
  int *ip = NULL;
  void *vp = NULL;

  cp = ip;          //警告あり(型が違うため)
  cp = (char *)ip;  //警告なし(キャストにより)
  cp = vp;          //警告なし(voidはどの型にも代入できる)

  return 0;
}
