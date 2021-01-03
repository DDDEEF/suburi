#ifndef ___TinyInt
#define ___TinyInt

#include <limits>
#include <iostream>

class TinyInt{
  int v;
public:
  TinyInt(int value = 0) : v(value){}
  operator int() const { return v; }
  bool operator!() const { return v == 0; }
  TinyInt& operator++(){
    if(v < std::numeric_limits<int>::max()) v++;
    return *this;
  }
  TinyInt operator++(int){
    TinyInt x = *this;
    ++(*this);
    return x;
  }
  friend TinyInt operator+(const TinyInt& x, const TinyInt& y){
    return TinyInt(x.v + y.v);
  }
  TinyInt& operator+=(const TinyInt& x){ v += x.v; return *this; }
  friend bool operator==(const TinyInt& x, const TinyInt& y){ return x.v == y.v; }
  friend bool operator!=(const TinyInt& x, const TinyInt& y){ return x.v != y.v; }
  friend bool operator> (const TinyInt& x, const TinyInt& y){ return x.v >  y.v; }
  friend bool operator>=(const TinyInt& x, const TinyInt& y){ return x.v >= y.v; }
  friend bool operator< (const TinyInt& x, const TinyInt& y){ return x.v <  y.v; }
  friend bool operator<=(const TinyInt& x, const TinyInt& y){ return x.v <= y.v; }
  friend std::ostream& operator<<(std::ostream& s, const TinyInt& x){
    return s << x.v;
  }
};

#endif
