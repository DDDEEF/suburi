#ifndef ___Class_IntArray
#define ___Class_IntArray

class IntArray{
  int nelem;
  int* vec;
public:
  explicit IntArray(int size) : nelem(size) { vec = new int[nelem]; }
  IntArray(const IntArray& x);
  ~IntArray(){ delete[] vec; }
  int size() const { return nelem; }
  IntArray& operator=(const IntArray& x);
  int& operator[](int i){ return vec[i]; }
  const int& operator[](int i) const { return vec[i]; }
};

#endif
