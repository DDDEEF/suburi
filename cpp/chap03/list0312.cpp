#include <iostream>

using namespace std;

int main(){
  int n;
  cout << "整数値:";
  cin >> n;
  for(int i = 1; i <= n; i += 2)
    cout << i << '\n';
}
