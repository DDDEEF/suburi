#include <iostream>

using namespace std;

class Base{
  int x;
public:
  Base(int a = 0) : x(a) { cout << "Base::xを" << x << "で初期化。\n"; }
};

class Memb{
  int x;
public:
  Memb(int a = 0) : x(a) { cout << "Memb::xを" << x << "で初期化。\n"; }
};

class Derived : public Base{
  int y;
  Memb m1;
  Memb m2;
  void say() { y = 0; cout << "Derived::yを" << y << "で初期化。\n"; }
public:
  Derived() { say(); }
  Derived(int a, int b, int c) : m2(a), m1(b), Base(c) { say(); }
};

int main(){
  Derived d1;
  cout << '\n';
  Derived d2(1, 2, 3);
}
