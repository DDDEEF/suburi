#ifndef ___ClassTemplate_Array
#define ___ClassTemplate_Array

template <class Type> class Array{
  int nelem;
  Type *vec;
  bool is_valid_index(int idx){ return idx >= 0 && idx < nelem; }
public:
  class IdxRngErr{
    const Array* ident;
    int idx;
  public:
    IdxRngErr(const Array* p, int i) : ident(p), idx(i) {}
    int Index() const { return idx; }
  };
  explicit Array(int size, const Type& v = Type()) : nelem(size){
    vec = new Type[nelem];
    for(int i = 0; i < nelem; i++){
      vec[i] = v;
    }
  }
  Array(const Array<Type>& x){
    if(&x == this){
      nelem = 0;
      vec = NULL;
    }else{
      nelem = x.nelem;
      vec = new Type[nelem];
      for(int i = 0; i < nelem; i++){
        vec[i] = x.vec[i];
      }
    }
  }
  ~Array() { delete[] vec; }
  int size() const { return nelem; }
  Array& operator=(const Array<Type>& x){
    if(&x != this){
      if(nelem != x.nelem){
        delete[] vec;
        nelem = x.nelem;
        vec = new Type[nelem];
      }
      for(int i = 0; i < nelem; i++){
        vec[i] = x.vec[i];
      }
    }
    return *this;
  }
  Type& operator[](int i){
    if(!is_valid_index(i)){
      throw IdxRngErr(this, i);
    }
    return vec[i];
  }
  const Type& operator[](int i) const{
    if(!is_valid_index(i)){
      throw IdxRngErr(this, i);
    }
    return vec[i];
  }
};

#endif
