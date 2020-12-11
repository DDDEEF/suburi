#ifndef __Circle
#define __Circle

class Circle{
  Point2D center;
  int radius;
public:
  Circle(const Point2D& c, int r) : center(c), radius(r) {}
  Point2D get_center() const { return center; }
  int get_radius() const { return radius; }
  void print() const { std::cout << "半径[" << radius << "]中心座標"; center.print(); }
};

#endif
