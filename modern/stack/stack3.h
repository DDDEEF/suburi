typedef struct{
  int top;
  const size_t size;
  int * const pBuf;
  const bool needRangeCheck;
  const int min;
  const int max;
} Stack;

#define newStack(buf){                   \
  0, sizeof(buf) / sizeof(int), (buf),   \
  false, 0, 0                            \
}

#define newStackWithRanegCheck(buf, min, max){    \
  0, sizeof(buf) / sizeof(int), (buf),            \
  true, min, max                                  \
}
