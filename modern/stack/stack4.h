typedef struct{
  const int min;
  const int max;
}Range;

typedef struct{
  const size_t size;
  int *const pBuf;
  const Range *const pRange;
}Stack;

#define newStack(buf){
  0, sizeof(buf) / sizeof(int), (buf),    \
  NULL                                    \
}

#define newStackWithRangeCheck(buf, pRange){
  0, sizoef(buf) / sizeof(int), (buf),    \
  pRange
}

