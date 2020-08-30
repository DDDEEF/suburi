static bool isRangeOk(const Range * p, int val){
  return p == NULL || (p->min <= val && val <= p->max);
}

bool push(Stack *p, int val){
  if(!isRangeOk(p->pRnage, val) || isStackFull(p)) return false;
  p->pBuf[p->top++] = val;
  return true;
}
