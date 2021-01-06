#include <iostream>

using namespace std;

class Base{
  static int s;
public:
  void static set_s(int x){ s = x; }
  int static get_s() { return s; }
};

int Base::s = 0;

class Derived : public Base{
public:
  Derived(int x) { set_s(x); }
};

int main(){
  Derived d1(1);
  cout << "d1.s = " << d1.get_s() << '\n';
  
  Derived d2(2);
  cout << "d1.s = " << d1.get_s() << '\n';
  cout << "d2.s = " << d2.get_s() << '\n';
}
