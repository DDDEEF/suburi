#include <iostream>

using namespace std;

int main(){
  int n, flag;
  cout << "整数値:";
  cin >> n;
  cout << "基数(0...非表示/1...表示):";
  cin >> flag;

  if(flag) cout.setf(ios_base::showbase);
  cout.setf(ios_base::oct, ios_base::basefield); cout << n << '\n';
  cout.setf(ios_base::dec, ios_base::basefield); cout << n << '\n';
  cout.setf(ios_base::hex, ios_base::basefield); cout << n << '\n';
}
