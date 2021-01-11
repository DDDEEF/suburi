#ifndef ___Math_Exception
#define ___Math_Exception

class DividedByZero{};

class Overflow{
  int v;
public:
  Overflow(int val) : v(val){}
  int value() const { return v; }
};

class Underflow{
  int v;
public:
  Underflow(int val) : v(val){}
  int value() const { return v; }
};

#endif
