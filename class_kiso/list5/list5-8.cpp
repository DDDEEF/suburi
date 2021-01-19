#include <iostream>
using namespace std;

class MyClass{
public:
  MyClass();
  ~MyClass();
};

MyClass::MyClass(){
  cout << "基本クラスのコンストラクタが呼び出されました。\n";
}

MyClass::~MyClass(){
  cout << "基本クラスのデストラクタが呼び出されました。\n";
}

class NewClass : public MyClass{
public:
  NewClass();
  ~NewClass();
};

NewClass::NewClass(){
  cout << "派生クラスのコンストラクタが呼び出されました。\n";
}

NewClass::~NewClass(){
  cout << "派生クラスのデストラクタが呼び出されました。\n";
}

int main(){
  NewClass obj;
  cout << "*******************************\n";
  return 0;
}


