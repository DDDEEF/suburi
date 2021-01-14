#include <iostream>

using namespace std;

int main(){
  int a[5];
  int value = 0;

  for(int* p = &a[0]; p != &a[5]; p++){
    *p = ++value;
  }

  for(const int* p = &a[0]; p != &a[5]; p++){
    cout << *p << ' ';
  }
  cout << '\n';
}
