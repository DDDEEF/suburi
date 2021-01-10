#include <string>
#include <iostream>

using namespace std;

class C{
  string name;
public:
  C(const string& n) : name(n){
    cout << name << "を構築\n";
  }
  C(const C& c){
    name = c.name + "'";
    cout << name << "コピーを構築\n";
  }
  ~C(){
    cout << name << "を解体\n";
  }
};

void func(){
  C c1(string("c1"));
  try{
    C c2(string("c2"));
    throw c2;
  }catch(int){
    cout << "int型例外を捕捉\n";
  }
  cout << "tryブロックを終了\n";
}

int main(){
  try{
    func();
  }catch(const C& c){
    cout << "C型例外を捕捉\n";
  }
}
