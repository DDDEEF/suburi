bool validateRange(Validator *p, int val){
  RangeValidator *pThis = (RangeValidator *)p;
  return pThis->min <= val && val <= pThis->max;
}

bool validatePrevious(Validator *p, int val){
  PreviousValueValidator *pThis = (PreviousValueValidator *)p;
  if(val < pThis->previousValue) return false;
  pThis->previousValue = val;
  return true;
}

RangeValidator validator = newRangeValidator(0, 9);
Stack stack = newStackWithValidator(buf, &validator.base);
