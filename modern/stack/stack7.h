typedef struct Validator{
  bool (* const validate)(struct Validator *pThis, int val);
}Validator;

typedef struct{
  Validator base;
  const int min;
  const int max;
}RangeValidator;

typedef struct{
  int top;
  const size_t size;
  int *const pBuf;
  Validator *const pValidator;
}Stack;

bool validateRange(Validator *pThis, int val);

#define newStackWithValidator(buf, pValidator){ \
  0, sizeof(buf) / sizeof(int), (buf),          \
  pValidator                                    \
}

#define newRangeValidator(min, max){  \
  {validateRange}, (min), (max)       \
}

int buf[16];
RangeValidator validator = newRangeValidator(0, 9);
Stack stack = newStackWithValidator(buf, &validator.base);
push(&stack, 123);
