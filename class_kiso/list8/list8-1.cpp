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

MyClass* gPtr;

int main(){
  cout << "プログラムが起動しました。\n";
  gPtr = new MyClass(123);
  cout << gPtr->myVal << "\n";

  func();
  
  delete gPtr;
  
  cout << "プログラムが終了します。\n";

  return 0;
}

void func(){
  MyClass* ptr;

  cout << "func()が呼び出されました。\n";

  for(int i = 1; i <= 3; i++){
    ptr = new MyClass(i);
    cout << ptr->myVal << "\n";
    delete ptr;
  }

  cout << "func()を抜けます。\n";
}
