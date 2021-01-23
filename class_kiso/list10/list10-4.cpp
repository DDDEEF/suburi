#include <iostream>
using namespace std;

class Point{
public:
  int x;
  int y;

  Point operator+(Point obj);
  Point operator+(int a);
  friend Point operator+(int a, Point obj);
};

Point Point::operator+(Point obj){
  Point ans;
  ans.x = this->x + obj.x;
  ans.y = this->y + obj.y;
  
  return ans;
}

Point Point::operator+(int a){
  Point ans;
  ans.x = this->x + a;
  ans.y = this->y + a;

  return ans;
}

Point operator+(int a, Point obj2){
  Point ans;
  ans.x = a + obj2.x;
  ans.y = a + obj2.y;
  
  return ans;
}

int main(){
  Point a, b, c;

  a.x = 1;
  a.y = 2;
  b.x = 3;
  b.y = 4;
  c = a + b;
  cout << "Point+Point\n";
  cout << "x座標:" << c.x << "\n";
  cout << "y座標:" << c.y << "\n";

  c = a + 10;
  cout << "Point+int\n";
  cout << "x座標:" << c.x << "\n";
  cout << "y座標:" << c.y << "\n";

  c = 20 + a;
  cout << "int+Point\n";
  cout << "x座標:" << c.x << "\n";
  cout << "y座標:" << c.y << "\n";

  return 0;
}


