#include <cmath>
#include <iostream>

using namespace std;

int main(){
  double x;

  cout << "実数値:";
  cin >> x;

  if(double m = fmod(x, 10)){
    cout << "その値は10で割り切れません。\n";
    cout << "剰余は" << m << "です。\n";
  }else{
    cout << "その値は10で割り切れます。\n";
  }
}
