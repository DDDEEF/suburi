#include <stdbool.h>
#include "stack1.h"
#include <stdio.h>

int buf[16];
int top = 0;

bool isStackFull(void){
  return top == sizeof(buf) / sizeof(int);
}

bool isStackEmpty(void){
  return top == 0;
}

bool push(int val){
  if(isStackFull()) return false;
  buf[top++] = val;
  return true;
}

bool pop(int *pRet){
  if(isStackEmpty()) return false;
  *pRet = buf[--top];
  return true;
}

void main(void){
  int ret;
  int *pRet = &ret;
  push(1);
  push(2);
  pop(pRet);
  printf("result = %d\n", *pRet);
}
