#include <iostream>

using namespace std;

template <class Type>
Type maxof(Type a, Type b){
  return a > b ? a : b;
}

int main(){
  int a, b;
  double x;

  cout << "整数a:"; cin >> a;
  cout << "整数b:"; cin >> b;
  cout << "整数c:"; cin >> x;
  
  cout << "aとbで大きいのは" << maxof(a, b) << "です。\n";
  cout << "aとxで大きいのは" << maxof<double>(a, x) << "です。\n";

  cout << "aとbで大きいのは" << maxof(a, b) << "です。\n";
  cout << "aとxで大きいのは" << maxof<double>(a, x) << "です。\n";
}
