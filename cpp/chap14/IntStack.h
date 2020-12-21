#ifndef ___IntStack
#define ___IntStack

#include <iostream>

class IntStack{
  int nelem;
  int* stk;
  int ptr;
public:
  explicit IntStack(int sz) : nelem(sz), ptr(0){ stk = new int[nelem]; }
  IntStack(const IntStack& x){
    nelem = x.nelem;
    ptr = x.ptr;
    stk = new int[nelem];
    for(int i = 0; i < nelem; i++){
      stk[i] = x.stk[i];
    }
  }
  ~IntStack() { delete[] stk; }
  int size() const { return nelem; }
  bool empty() const { return ptr == 0; }
  IntStack& operator=(const IntStack& x){
    if(&x != this){
      if(nelem != x.nelem){
        delete[] stk;
        nelem = x.nelem;
        ptr = x.ptr;
        stk = new int[nelem];
      }
      for(int i = 0; i < ptr; i++){
        stk[i] = x.stk[i];
      }
    }
    return *this;
  }
  void push(int x){ if(ptr < nelem) stk[ptr++] = x; }
  int pop(){ if(ptr > 0) return stk[--ptr]; else throw 1; }
};

#endif
