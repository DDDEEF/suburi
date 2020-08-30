typedef struct Validator{
  bool (* const validate)(struct Validator *pThis, int val);
  void *const pData;
}Validator;

typedef struct {
  const int min;
  const int max;
}Range;

typedef struct{
  int previousValue;
}PreviousValue;

#define reangeValidator(pRange){  \
  validateRange,                  \
  pRange                          \
}

#define previousValidator(pPrevious){ \
  validatePrevious,                   \
  pPrevious                           \
}

bool validateRange(Validator *pThis, int val){
  Range *pRange = (Range *)(pThis->pData);
  return pRange->min <= val && val <= pRange->max;
}

bool validatePrevious(Validator *pThis, int val){
  PreviousValue *pPrevious = (PreviousValue *)pThis->pData;
  if(val < pPrevious->previousValue) return false;
  pPrevious->previousValue = val;
  return true;
}

/*
使い方
Range range = {0, 9};
Validator validator = rangeValidator(&range);
*/
