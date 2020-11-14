#include <iostream>

using namespace std;

int main(){
  const double PI = 3.1416;
  double r;

  cout << "半径:";
  cin >> r;

  cout << "円周の長さは" << 2 * r * PI << "です。\n";
  cout << "面積は" << r * r * PI << "です。\n";
}
