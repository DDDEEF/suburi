#ifndef ___Math_Exception
#define ___Math_Exception

class MathException{};
class DividedByZero : public MathException {};

class Overflow : public MathException{
  int v;
public:
  Overflow(int val) : v(val) {}
  int value() const { return v; }
};

class Underflow : public MathException{
  int v;
public:
  Underflow(int val) : v(val){}
  int value() const { return v; }
};

#endif
