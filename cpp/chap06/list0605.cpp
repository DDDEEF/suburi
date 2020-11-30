#include <iostream>

using namespace std;

int max(int a, int b, int c);

int main(){
  int a, b, c;

  cout << "整数a:"; cin >> a;
  cout << "整数b:"; cin >> b;
  cout << "整数c:"; cin >> c;

  cout << "最大値は" << max(a, b, c) << "です。\n";
}

int max(int a, int b, int c){
  int max = a;
  if(b > max) max = b;
  if(c > max) max = c;
  return max;
}
