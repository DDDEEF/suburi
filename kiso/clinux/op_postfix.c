/*
 * 後置演算子
 */
#include <stdio.h>

//              01234567890AB
char g_str[] = "hello, world.";

int main(void){
  char *cp = g_str;
  int *ip = (int *)g_str;
  long *lp = (long *)g_str;

  printf("cp %p ip %p lp %p\n", cp, ip, lp);
  printf("cp=%s ip=%s lp=%s\n\n", cp, ip, lp);
  cp++;
  ip++;
  lp++;

  printf("cp %p ip %p lp %p\n", cp, ip, lp);
  printf("cp=%s ip=%s lp=%s\n\n", cp, ip, lp);
  cp--;
  ip--;
  lp--;

  printf("cp %p ip %p lp %p\n", cp, ip, lp);
  printf("cp=%s ip=%s lp=%s\n\n", cp, ip, lp);

  return 0;
}
