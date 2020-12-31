#include <iostream>
#include "Counter.h"

using namespace std;

int main(){
  int no;
  Counter x;
  Counter y;

  cout << "カウントアップの回数:";
  cin >> no;
  for(int i = 0; i < no; i++){
    cout << x++ << ' ' << ++y << '\n';
  }


  cout << "カウントダウンの回数:";
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
