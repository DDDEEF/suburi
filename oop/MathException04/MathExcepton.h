#ifndef ___Math_Exception
#define ___Math_Exception

#include <string>
#include <cstring>
#include <sstream>
#include <exception>
#include <stdexcept>

class MathException : public std::logic_error{
public:
  MathException() : logic_error("数値演算例外") {}
  virtual const char* what() const { return "数値演算例外"; }
};

class DividedByZero : public MathException{
public:
  const char* what() const { return "0による除算"; }
};

class Overflow : public MathException {
  int v;
public:
  Overflow(int val) : v(val){}
  int value() const { return v; }
  const char* what() const {
    static char buff[128];
    std::ostringstream s;
    s << "オーバーフロー(値は" << v << ")";
    return std::strcpy(buff, s.str().c_str());
  }
};

class Underflow : public MathException {
  int v;
public:
  Underflow(int val) : v(val) {}
  int value() const { return v; }
  const char* what() const {
    static char buff[128];
    std::ostringstream s;
    s << "アンダーフロー(値は" << v << ")";
    return std::strcpy(buff, s.str().c_str());
  }
};

#endif
