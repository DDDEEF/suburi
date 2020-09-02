typedef struct Validator{
  bool (*const validate)(struct Validator *pThis, int val);
}Validator;

typedef struct{
  Validator base;
  const int min;
  const int max;
}RangeValidator;

typedef struct{
  Validator base;
  int previousValue;
}PreviousValueValidator;

typedef struct{
  int top;
  const size_t size;
  int *const pBuf;
  Validator * const pValidator;
}Stack;

bool validateRange(Validator *pThis, int val);
bool validatePrevious(Validator *pThis, int val);

#define newRangeValidator(min, max) { \
  {validateRange}, (min), (max)       \
}                                     \

#define newPreviousValueValidator {   \
  {validatePrevious}, 0               \
}

#define newStackWithValidator(buf, pValidator){ \
  0, sizeof(buf) / sizeof(int), (buf),          \
  pValidator                                    \
}
