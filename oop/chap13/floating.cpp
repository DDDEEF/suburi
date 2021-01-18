#include <iostream>

using namespace std;

int main(){
  int precision;
  double x;

  cout << "実数値:";
  cin >> x;

  cout << "精度:";
  cin >> precision;

  cout.precision(precision);

  cout.setf(ios_base::scientific, ios_base::floatfield);
  cout << "科学形式:" << x << '\n';

  cout.setf(ios_base::fixed, ios_base::floatfield);
  cout << "固定形式:" << x << '\n';

  cout.setf(ios_base::floatfield);
  cout << "通常形式:" << x << '\n';
}
