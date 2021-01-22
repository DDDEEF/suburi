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

int main(){
  cout << "プログラムが起動しました。\n";
  func();
  func();
  cout << "プログラムが終了しました。\n";

  return 0;
}

void func(){
  cout << "func()が呼び出されました。\n";
  static int a = 123;
  cout << "静的変数の値:" << a << "\n";
  a++;
  static MyClass obj(456);
  cout << "メンバ変数の値:" << obj.myVal << "\n";
  obj.myVal++;
  cout << "func()を抜けます。\n";
}
