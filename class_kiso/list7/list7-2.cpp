#include <iostream>
using namespace std;

class MyClass{
public:
  int myVal;
  MyClass();
  MyClass(int m);
  ~MyClass();
};

MyClass::MyClass(){
  myVal = 0;
  cout << "コンストラクタが呼び出されました。\n";
}

MyClass::MyClass(int m){
  myVal = m;
  cout << "コンストラクタが呼び出されました。\n";
}

MyClass::~MyClass(){
  cout << "デストラクタが呼び出されました。\n";
}

void func();

MyClass g(123);

int main(){
  cout << "プログラムを起動しました。\n";
  cout << "g.myValの値:" << g.myVal << "\n";

  func();
  func();

  cout << "プログラムが終了します。\n";
  return 0;
}

void func(){
  cout << "func()が呼び出されました。\n";
  MyClass a;
  cout << "a.myValの値:" << a.myVal << "\n";
  a.myVal = 456;
  cout << "func()を抜けます。\n";
}
