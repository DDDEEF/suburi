#include <iostream>
using namespace std;

template<class datatype> class TPoint{
public:
  datatype x;
  datatype y;
  void showData();
  TPoint();
  TPoint(datatype x, datatype y);
};

template<class datatype> void TPoint<datatype>::showData(){
  cout << "x座標:" << x << "\n";
  cout << "y座標:" << y << "\n";
}

template<class datatype> TPoint<datatype>::TPoint(){
  x = 0;
  y = 0;
}

template<class datatype> TPoint<datatype>::TPoint(datatype x, datatype y){
  this->x = x;
  this->y = y;
}

int main(){
  TPoint<int> obj1;
  obj1.x = 123;
  obj1.y = 456;
  obj1.showData();

  TPoint<double> obj2(1.23, 3.45);
  obj2.showData();

  return 0;
}
