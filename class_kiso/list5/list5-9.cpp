#include <iostream>
using namespace std;

class MyClass{
public:
  int my_data;
  MyClass();
  MyClass(int m);
  ~MyClass();
};

MyClass::MyClass(){
  my_data = -1;
  cout << "基本クラスの引数のないコンストラクタが呼び出されました。\n";
}

MyClass::MyClass(int m){
  my_data = m;
  cout << "基本クラスの引数を持つコンストラクタが呼び出されました。\n";
}

MyClass::~MyClass(){
  cout << "基本クラスのデストラクタが呼び出されました。\n";
}

class NewClass : public MyClass{
public:
  int new_data;
  NewClass();
  NewClass(int n, int m);
  ~NewClass();
};

NewClass::NewClass(){
  new_data = -1;
  cout << "派生クラスの引数のないコンストラクが呼び出されました。\n";
}

NewClass::NewClass(int n, int m) : MyClass(m){
  new_data = n;
  cout << "派生クラスの引数を持つコンストラクタが呼び出されました。\n";
}

NewClass::~NewClass(){
  cout << "派生クラスのデストラクタが呼び出されました。\n";
}

int main(){
  NewClass obj1;

  cout << obj1.my_data << "\n";
  cout << obj1.new_data << "\n";
  cout << "**********************\n";

  NewClass obj2(123, 456);

  cout << obj2.my_data << "\n";
  cout << obj2.new_data << "\n";

  return 0;
}

