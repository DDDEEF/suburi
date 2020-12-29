#include <iostream>
#include "Point2D.h"

using namespace std;

int main(){
  Point2D p;
  Point2D q(1, 3);
  Point2D a[] = { Point2D(1, 1), Point2D(2, 2) };
  cout << "最後に与えた識別番号:" << Point2D::get_max_id() << '\n';
  cout << "p = "; p.print(); cout << " 識別番号:" << p.id() << '\n';
  cout << "q = "; q.print(); cout << " 識別番号:" << q.id() << '\n';
  for(int i = 0; i < sizeof(a) / sizeof(a[0]); i++){
    cout << "a[" << i << "] = "; a[i].print();
    cout << "識別番号:" << a[i].id() << '\n';
  }
}
