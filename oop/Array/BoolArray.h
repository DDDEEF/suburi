#ifndef ___Class_Template_Array_Bool
#define ___Class_Template_Array_Bool

#include <limits>
#include "Array.h"

template<> class Array<bool>{
  typedef unsigned char BYTE;
  static const int CHAR_BITS = std::numeric_limits<unsigned char>::digits;

  int nelem;
  int velem;
  BYTE* vec;
  static int size_of(int sz){ return (sz + CHAR_BITS - 1) / CHAR_BITS; }
public:
  class BitOfByteRef{
    BYTE& vec;
    int idx;
  public:
    BitOfByteRef(BYTE& r, int i) : vec(r), idx(i) {}
    operator bool() const { return vec >> idx & 1U; }
    BitOfByteRef& operator=(bool b){
      if(b){
        vec |= 1U << idx;
      }else{
        vec &= ~(1U << idx);
      }
      return *this;
    }
    BitOfByteRef& operator=(BitOfByteRef& r){
      return *this = (bool)r;
    }
  };
  class IdxRngErr{
    const Array* ident;
    int index;
  public:
    IdxRngErr(const Array* p, int i) : ident(p), index(i) {}
    int Index() const { return index; }
  };

  explicit Array(int sz, bool v = bool()) : nelem(sz), velem(size_of(sz)){
    vec = new BYTE[velem];
    for(int i = 0; i < velem; i++){
      vec[i] = v;
    }
  }

  Array(const Array<bool>& x){
    if(&x == this){
      nelem = 0;
      vec = NULL;
    }else{
      nelem = x.nelem;
      velem = x.velem;
      vec = new BYTE[velem];
      for(int i = 0; i < velem; i++){
        vec[i] = x.vec[i];
      }
    }
  }
  ~Array(){ delete[] vec; }
  int size() const { return nelem; }
  Array& operator=(const Array<bool>& x){
    if(&x != this){
      if(velem != x.velem){
        delete[] vec;
        velem = x.velem;
        vec = new BYTE[velem];
      }
      nelem = x.nelem;
      for(int i = 0; i < velem; i++){
        vec[i] = x.vec[i];
      }
    }
    return *this;
  }

  BitOfByteRef operator[](int i){
    if(i < 0 || i >= nelem){
      throw IdxRngErr(this, i);
    }
    return BitOfByteRef(vec[i / CHAR_BITS], (i & (CHAR_BITS - 1)));
  }

  bool operator[](int i) const {
    if(i < 0 || i >= nelem){
      throw IdxRngErr(this, i);
    }
    return (vec[i / CHAR_BITS] >> (i & (CHAR_BITS - 1)) & 1U) == 1;
  }
};

#endif
