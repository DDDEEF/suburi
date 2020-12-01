#include <iostream>

using namespace std;

int factorial(int n){
  if(n > 0){
    return n * factorial(n - 1);
  }else{
    return 1;
  }
}

int main(){
  int x;
  cout << "整数値:";
  cin >> x;
  cout << x << "の階乗は" << factorial(x) << "です。\n";
}
