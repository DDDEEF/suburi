#include <iostream>

using namespace std;

void swap(int& x, int& y){
  int t = x;
  x = y;
  y = t;
}

void sort(int& a, int& b, int& c){
  if(a > b) swap(a, b);
  if(b > c) swap(b, c);
  if(a > b) swap(a, b);
}

int main(){
  int a, b, c;
  cout << "変数a:"; cin >> a;
  cout << "変数b:"; cin >> b;
  cout << "変数c:"; cin >> c;
  sort(a, b, c);
  cout << "変数a, b, cを昇順に並べ替えました。\n";
  cout << "変数aの値は" << a << "です。\n";
  cout << "変数bの値は" << b << "です。\n";
  cout << "変数cの値は" << c << "です。\n";
}
