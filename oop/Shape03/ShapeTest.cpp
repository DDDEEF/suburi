#include <iostream>
#include "Shape.h"
#include "TwoDimensional.h"
#include "Point.h"
#include "Line.h"
#include "Rectangle.h"
#include "RectEquilTriangle.h"

using namespace std;

int main(){
  Shape* s[] = {
    new Point(),
    new HorzLine(6),
    new VertLine(3),
    new Rectangle(3, 7),
    new RectEquilTriangleLB(5),
    new RectEquilTriangleRU(4),
  };

  for(int i = 0; i < sizeof(s) / sizeof(a[0]); i++){
    cout << "s[" << i << "]\n";
    s[i]->print();
    cout << '\n';
  }

  for(int i = 0; i < sizeof(s) / sizeof(s[0]); i++){
    delete s[i]l
  }
}
