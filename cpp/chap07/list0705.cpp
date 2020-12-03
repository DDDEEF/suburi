#include <iostream>

using namespace std;

void sum_mul(int x, int y, int *sum, int *mul){
  *sum = x + y;
  *mul = x * y;
}

int main(){
  int a, b;
  int wa = 0, seki = 0;

  cout << "整数a:"; cin >> a;
  cout << "整数b:"; cin >> b;

  sum_mul(a, b, &wa, &seki);

  cout << "和は" << wa << "です。\n";
  cout << "積は" << seki << "です。\n";
}
