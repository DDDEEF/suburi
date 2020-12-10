#include <iostream>

using namespace std;

#define DEBUG 1

int main(){
  int a = 5;
  int x = 7;

#if DEBUG == 1
  a = x;
#endif

  cout << "aの値は" << a << "です。\n";
}
