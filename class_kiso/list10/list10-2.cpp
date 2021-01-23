#include <iostream>
using namespace std;

class Point{
public:
  int x;
  int y;
  Point operator+(Point obj);
  Point operator-(Point obj);
};

Point Point::operator+(Point obj){
  Point ans;
  ans.x = this->x + obj.x;
  ans.y = this->y + obj.y;
  return ans;
}

Point Point::operator-(Point obj){
  Point ans;
  ans.x = this->x - obj.x;
  ans.y = this->y - obj.y;
  return ans;
}

int main(){
  Point a, b, c;
  a.x = 1;
  a.y = 2;
  b.x = 3;
  b.y = 4;

  c = a + b;
  cout << "x座標:" << c.x << "\n";
  cout << "y座標:" << c.y << "\n";

  c = a - b;
  cout << "x座標:" << c.x << "\n";
  cout << "y座標:" << c.y << "\n";

  return 0;
}


