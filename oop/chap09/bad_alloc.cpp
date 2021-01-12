#include <new>
#include <cstdlib>
#include <iostream>

using namespace std;

void new_error(){
  cout << "new演算子による記憶域の確保に失敗しました。\n";
  abort();
}

int main(){
  set_new_handler(new_error);
  while(true){
    new char[10000];
  }
}
