#include <iostream>

using namespace std;

class Test{
public:
  Test(){
    cout << "初期化:Test()\n";
  }

  Test(const Test& t){
    cout << "初期化:Test(const Test&)\n";
  }

  Test& operator=(const Test& t){
    cout << "代入:Test = Test\n";
    return *this;
  }
};

void value(Test a){ 
}

void reference(Test& a){
}

int main(){
  Test x;
  Test y = x;
  Test z(x);
  y = x;
  value(x);
  reference(x);
}
