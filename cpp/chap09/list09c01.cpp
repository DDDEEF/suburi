#include <iostream>

using namespace std;

//通常の関数
int maxof(int a, int b){
  return a < b ? a : b;
}

//関数テンプレート
template <class Type>
Type maxof(Type a, Type b){
  return a > b ? a : b;
}

int main(){
  int a, b;

  cout << "整数a:"; cin >> a;
  cout << "整数b:"; cin >> b;

  //通常の関数
  cout << "大きいのは" << maxof(a, b) << "です。\n";

  //関数テンプレート
  cout << "大きいのは" << maxof<int>(a, b) << "です。\n";
  cout << "大きいのは" << maxof<>(a, b) << "です。\n";
}
