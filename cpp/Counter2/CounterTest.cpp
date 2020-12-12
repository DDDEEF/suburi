#include <iostream>
#include "Counter.h"

using namespace std;

int main(){
  int no;
  Counter x;
  Counter y;

  cout << "カウントアップ回数:";
  cin >> no;
  for(int i = 0; i < no; i++){
    cout << x++ << ' ' << ++y << '\n';
  }
  cout << "カウントダウン回数:";
  cin >> no;
  for(int i = 0; i < no; i++){
    cout << x-- << ' ' << --y << '\n';
  }

  if(!x){
    cout << "xは0です。\n";
  }else{
    cout << "xは0ではありません。\n";
  }
}
