#include <iostream>

using namespace std;

class A{
public:
  virtual void f1() { cout << "A::f1()です。\n"; }
  virtual void f2() { cout << "A::f2()です。\n"; }
};

class B : public A{
public:
  void f2() { cout << "B::f2()です。\n"; }
};

class C : public B{
public:
  void f1() { cout << "C::f1()です。\n"; }
};

class D : public C{
public:
  void f1() { cout << "D::f1()です。\n"; }
  void f2() { cout << "D::f2()です。\n"; }
};

int main(){
  A *p;   
  A a;  p = &a;   cout << "p->a\n";   p->f1(); p->f2(); cout << '\n';
  B b;  p = &b;   cout << "p->b\n";   p->f1(); p->f2(); cout << '\n';
  C c1; p = &c1;  cout << "p->c1\n";  p->f1(); p->f2(); cout << '\n';
  C c2; p = &c2;  cout << "p->c2\n";  p->f1(); p->f2(); cout << '\n';
  D d;  p = &d;   cout << "p->d\n";   p->f1(); p->f2(); cout << '\n';
}
