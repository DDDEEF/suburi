#include <iomanip>
#include <iostream>

using namespace std;

int main(){
  float a = 123456789.0;
  double b = 12345678901234567890.0;
  long double c = 12345678901234567901234567890.0;

  cout << "a = " << setprecision(30) << a << '\n';
  cout << "b = " << setprecision(30) << b << '\n';
  cout << "c = " << setprecision(30) << c << '\n';
}
