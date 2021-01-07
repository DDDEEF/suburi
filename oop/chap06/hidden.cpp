#include <iostream>

using namespace std;

class A{
public:
  int a;
  A(int aa = 55) : a(aa){}
};

class B : public A{
public:
  double a;
  B(double aa = 3.14) : a(aa){}
};

int main(){
  B b(3.14);
  cout << "b.a = "    << b.a    << '\n';
  cout << "b.A::a = " << b.A::a << '\n'; 
}
