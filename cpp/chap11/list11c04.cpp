#include <iostream>

using namespace std;

class Int{
  int v;
public:
  Int(int val) : v(val) { cout << v << '\n'; }
};

class Abc{
  Int a;
  Int b;
  Int c;

public:
  Abc(int aa, int bb, int cc) : c(cc), b(bb), a(aa) {}
};

int main(){
  Abc x(1, 2, 3);
}
