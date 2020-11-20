#include <iostream>

using namespace std;

int main(){
  int x = 0;
  ++x = 5;
  cout << "xの値は" << x << "です。\n";

  x++ = 10; //NG
  cout << "xの値は" << x << "です。\n";
}
