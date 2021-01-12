#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

class MyException : public logic_error{
public:
  MyException() : logic_error("マイ例外") {}
  virtual const char* what() const { return "マイ例外"; }
};

void work(int sw){
  switch(sw){
    case 1: throw exception("exception例外");
    case 2: throw logic_error("logic_error例外");
    case 3: throw MyException();
  }
}

void test(int sw){
  try{
    work(sw);
  }catch(const MyException& e){
    cout << e.what() << "を捕捉。対処完了\n";
  }catch(const logic_error& e){
    cout << e.what() << "を捕捉。対処断念\n";
  }catch(const exception& e){
    cout << e.what() << "を捕捉。対処断念\n";
    throw "ABC";
  }
}

int main(){
  int sw;
  cout << "sw:";
  cin >> sw;
  try{
    test(sw);
  }catch(const logic_error& e){
    cout << e.what() << "を捕捉。\n";
  }catch(const char* e){
    cout << e << "を捕捉\n";
  }
}
