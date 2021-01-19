#include <iostream>
#include <cmath>
using namespace std;

class SimpleMath{
private:
  double tempCalc(double a, double b, double c);
public:
  bool quadratic(double a, double b, double c, double *x1, double *x2);
};

bool SimpleMath::quadratic(double a, double b, double c, double *x1, double *x2){
  double temp;
  temp = tempCalc(a, b, c);
  cout << "temp[" << temp << "]\n";
  cout << "sqrt(temp)[" << sqrt(temp) << "]\n";
  if(temp < 0){
    return false;
  }else{
    *x1 = (-b + sqrt(temp)) / (2*a);
    *x2 = (-b - sqrt(temp)) / (2*a);
    return true;
  }
}

double SimpleMath::tempCalc(double a, double b, double c){
  return b * b - 4 * a * c;
}

int main(){
  SimpleMath sm;
  double x1, x2;

  if(sm.quadratic(3, 10, 7, &x1, &x2) == true){
    cout << "x1 = " << x1 << "\n";
    cout << "x2 = " << x2 << "\n";
  }else{
    cout << "解なし\n";
  }
  return 0;
}

