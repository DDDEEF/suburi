#include <iostream>

using namespace std;

int main(){
  int n;

  cout << "整数値:";
  cin >> n;

  if(int mod = n %10){
    cout << "その値は10で割り切れません。\n";
    cout << "最下位桁は" << mod << "です。\n";
  }else{
    cout << "その値は10で割り切れます。\n";
  }
}
