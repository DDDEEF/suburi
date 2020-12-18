#include <iostream>
#include "IdNo.h"

using namespace std;

int main(){
  IdNo a;
  IdNo b;
  IdNo c[4];

  cout << "aの識別番号:" << a.id() << '\n';
  cout << "bの識別番号:" << b.id() << '\n';
  for(int i = 0; i < 4; i++){
    cout << "c[" << i << "]の識別番号:" << c[i].id() << '\n';
  }
}
