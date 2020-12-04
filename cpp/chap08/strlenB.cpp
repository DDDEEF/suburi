#include <cstddef>

size_t strlen(const char *s){
  const char *p = s;

  while(*s){
    s++;
  }
  return s - p;
}

//ポインタ同士の引き算は、符号付整数型であるptrdiff_t型である。
//size_tは符号無し整数型
