#include <iostream>
using namespace std;

class MyClass{
public:
  int number;
  MyClass();
  ~MyClass();
};

MyClass::MyClass(){
  cout << "コンストラクタが呼び出されました。\n";
}

MyClass::~MyClass(){
  cout << "オブジェクト" << number;
  cout << "のデストラクタが呼び出されました。\n";
}

void myFunc(){
  MyClass obj1;
  obj1.number = 1;
}

int main(){
  myFunc();
  MyClass obj2;
  obj2.number = 2;

  return 0;
}
