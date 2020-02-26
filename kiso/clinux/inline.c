#include <stdio.h>

inline void sub(void){
  printf("%s\n", __func__);
}
extern void sub(void);

static inline void sub2(void){
  printf("%s\n", __func__);
}

int main(void){
  sub();
  sub2();

  return 0;
}
