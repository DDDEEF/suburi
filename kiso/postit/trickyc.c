#include <stdio.h>

int pop(int *lstack, int *left){
  *left = 10;
  *lstack = 20;
  
  return 100; 
}

int main(){
  int pl;
  int lstack;
  int left;

  pl = (pop(&lstack, &left), left);

  printf("pl = %d\n", pl);
}
