#ifndef ___Math_Exception
#define ___Math_Exception

#include <string>

class MathException{
public:
  virtual void display() const { std::cout << "数値演算例外\n"; }
};

class DividedByZero : public MathException {
public:
  void display() const { std::cout << "0による除算\n"; }
};

class Overflow : public MathException {
  int v;
public:
  Overflow(int val) : v(val) {}
  int value() const { return v; }
  void display() const { std::cout << "オーバーフロー(値は" << v << ")\n"; }
};

class Underflow : public MathException {
  int v;
public:
  Underflow(int val) : v(val) {}
  int value() const { return v; }
  void display() const { std::cout << "アンダーフロー(値は" << v << ")\n"; }
};

#endif
