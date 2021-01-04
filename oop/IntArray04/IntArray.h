#ifndef ___Class_IntArray
#define ___Class_IntArray

class IntArray{
  int nelem;
  int *vec;
public:
  class IdxRngErr{
  private:
    const IntArray* ident;
    int idx;
  public:
    IdxRngErr(const IntArray* p, int i) : ident(p), idx(i) {}
    int index() const { return idx; }
  };

  explicit IntArray(int size) : nelem(size) { vec = new int[nelem]; }
  IntArray(const IntArray& x);
  ~IntArray(){ delete[] vec; }
  int size() const { return nelem; }
  IntArray& operator=(const IntArray& x);
  int& operator[](int i){
    if(i < 0 || i >= nelem){
      throw IdxRngErr(this, i);
    }
    return vec[i];
  }
  const int& operator[](int i) const {
    if(i < 0 || i >= nelem){
      throw IdxRngErr(this, i);
    }
    return vec[i];
  }
};

#endif
