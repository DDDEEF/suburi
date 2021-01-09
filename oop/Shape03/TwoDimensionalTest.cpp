#include <iostream>
#include "Shape.h"
#include "TwoDimensional.h"
#include "Rectangle.h"
#include "RectEquilTriangle.h"

using namespace std;

int main(){
  TwoDimensional* t[] = {
    new Rectagnle(3, 7),
    new RectEquilTriangleLB(5),
    new RectEquilTrinagleRU(4),
  };
  for(int i = 0; i < sizeof(t) / sizeof(t[0]); i++){
    cout << "t[" << i << "]の面積は" << t[i]->get_area() << "です。\n";
  }
  for(int i = 0; i < sizeof(t) / sizeof(t[0]); i++){
    delete t[i];
  }
}
