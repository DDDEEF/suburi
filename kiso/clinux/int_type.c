#include <stdio.h>
#include <stdbool.h>

int main(void){
  long long int val;
  _Bool a, b;

  // long long int型
  val = ((long long)1 << 32);
  printf("%lld(%llx)\n", val, val);

  // ブール型
  a = true;
  b = false;
  printf("%d %d\n", a, b);

  return 0;
}
