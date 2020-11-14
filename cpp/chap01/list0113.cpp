#include <iostream>

using namespace std;

int main(){
  double x;
  double y;

  cout << "xとyを加減乗除します。\n";

  cout << "xの値:";
  cin >> x;

  cout << "yの値:";
  cin >> y;

  cout << "x + yは" << x + y << "です。\n";
  cout << "x - yは" << x - y << "です。\n";
  cout << "x * yは" << x * y << "です。\n";
  cout << "x / yは" << x / y << "です。\n";
//cout << "x % yは" << x % y << "です。\n"; 実数型に%演算子は適用できない。
}
