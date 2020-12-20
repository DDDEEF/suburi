#ifndef ___Point2D
#define ___Point2D
#include <iostream>

class Point2D{
  int xp, yp;
  int id_no;
  static int counter;
public:
  Point2D(int x = 0, int y = 0);
  int id() const { return id_no; }
  void print() const{ std::cout << "(" << xp << "," << yp << ")"; }
  static int get_max_id();
};

#endif
