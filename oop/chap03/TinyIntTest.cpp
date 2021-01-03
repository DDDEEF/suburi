#include <iostream>
#include "TinyInt.h"

using namespace std;

int main(){
  TinyInt a, b(3), c(6);
  TinyInt d = (++a) + (b++) + (c += 3);
  cout << "a = " << a << '\n';
  cout << "b = " << b << '\n';
  cout << "c = " << c << '\n';
  cout << "d = " << d << '\n';
}
