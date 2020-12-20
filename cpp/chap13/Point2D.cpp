#include "Point2D.h"
int Point2D::counter = 0;
Point2D::Point2D(int x, int y) : xp(x), yp(y){
  id_no = ++counter;
}

int Point2D::get_max_id(){
  return counter;
}
