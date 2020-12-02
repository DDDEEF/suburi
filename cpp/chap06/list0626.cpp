#include <iostream>

using namespace std;

#define sqr(x) ((x) * (x))

int main(){
  int n;
  double x;

  cout << "整数を入力してください。:"; cin >> n;
  cout << "その数の2乗は" << sqr(n) << "です。\n";

  cout << "実数を入力してください。:"; cin >> x;
  cout << "その数の2乗は" << sqr(x) << "です。\n"; 
}
