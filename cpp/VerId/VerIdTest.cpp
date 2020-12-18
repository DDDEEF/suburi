#include <iostream>
#include "VerId.h"

using namespace std;

int main(){
  VerId a;
  VerId b;

  cout << "aの識別番号:" << a.id() << '\n';
  cout << "bの識別番号:" << b.id() << '\n';
  cout << "生成されたオブジェクトの数:" << VerId::counter << '\n';
  cout << "生成されたオブジェクトの数:" << a.counter << '\n';
  cout << "生成されたオブジェクトの数:" << b.counter << '\n';
}

