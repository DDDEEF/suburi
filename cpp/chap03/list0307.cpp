#include <iostream>

using namespace std;

int main(){
  int n;
  cout << "何個表示しますか?:";
  cin >> n;

  if(n > 0){
    int i = 0;
    while(i < n / 2){
      cout << "+-";
      i++;
    }
    if(n % 2) cout << '+';
    cout << '\n';
  }
}
