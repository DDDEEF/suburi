#include <iostream>
#include "MathException.h"

using namespace std;

int check(int value){
  if(value < 0) throw Underflow(value);
  if(value > 99) throw Overflow(value);
  return value;
}

int add2(int x, int y){
  return check(x + y);
}

int sub2(int x, int y){
  return check(x - y);
}

int mul2(int x, int y){
  return check(x * y);
}

int div2(int x, int y){
  if(y == 0) throw DividedByZero();
  return check(x / y);
}

int main(){
  int x, y;

  do{ cout << "xの値:"; cin >> x; } while (x < 0 || x > 99);
  do{ cout << "yの値:"; cin >> y; } while (y < 0 || y > 99);

  try{
    cout << "x + y = " << add2(x, y) << '\n';
    cout << "x - y = " << sub2(x, y) << '\n';
    cout << "x * y = " << mul2(x, y) << '\n';
    cout << "x / y = " << div2(x, y) << '\n';
  }catch(const DividedByZero&){
    cout << "DividedByZeroを捕捉: 0による除算が発生\n";
  }catch(const MathException&){
    cout << "MathExceptionを捕捉: 0による除算以外の算術例外が発生\n";
  }
  cout << "プログラム終了\n";
}
