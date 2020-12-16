#ifndef ___Class_Complex
#define ___Class_Complex

#include <iostream>

class Complex{
  double re;  //実部
  double im;  //虚部
public:
  Complex(double r = 0, double i = 0) : re(r), im(i){}
  double real() const { return re; }
  double imag() const { return im; }

  Complex operator+() const { return *this; }
  Complex operator-() const { return Complex(-re, -im); }

  Complex& operator+=(const Complex& x){
    re += x.re;
    im += x.im;
    return *this;
  }

  Complex& operator-=(const Complex& x){
    re -= x.re;
    im -= x.im;
    return *this;
  }

  friend bool operator==(const Complex& x, const Complex& y){
    return x.re == y.re && x.im == y.im;
  }

  friend bool operator!=(const Complex& x, const Complex& y){
    return !(x == y);
  }

  friend Complex operator+(const Complex& x, const Complex& y){
    return Complex(x.re + y.re, x.im + y.im);
  }

  friend Complex operator+(double x, const Complex& y){
    return Complex(x + y.re, y.im);
  }

  friend Complex operator+(const Complex& x, double y){
    return Complex(x.re + y, x.im);
  }
};

inline std::ostream& operator<<(std::ostream& s, const Complex& x){
  return s << '(' << x.real() << ", " << x.imag() << ')';
}

#endif
