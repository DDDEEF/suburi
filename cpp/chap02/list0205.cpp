#include <iostream>

using namespace std;

int main(){
  int n;

  cout << "整数値";
  cin >> n;

  if(n > 0)
    cout << "その値は正です。\n";
  else if(n < 0)
    cout << "その値は負です。\n";
  else
    cout << "その値は0です。\n";
}
