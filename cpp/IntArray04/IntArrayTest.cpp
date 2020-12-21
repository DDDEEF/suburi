#include <new>
#include <iostream>
#include "IntArray.h"

using namespace std;

void f(int size, int num){
  try{
    IntArray x(size);
    for(int i = 0; i < num; i++){
      x[i] = i;
      cout << "x[" << i << "] = " << x[i] << '\n';
    }
  }catch(IntArray::IdxRngErr& x){
    cout << "添字オーバフロー:" << x.index() << '\n';
    return;
  }catch(bad_alloc){
    cout << "メモリの確保に失敗しました。\n";
    exit(1);
  }
}

int main(){
  int size, num;
  cout << "要素数:";
  cin >> size;

  cout << "データ数";
  cin >> num;

  f(size, num);

  cout << "main関数終了\n";
}
