#ifndef ___Class_Point
#define ___Class_Point

#include <string>
#include <iostream>
#include "Shape.h"

class Point : public Shape{
public:
  void draw() const {
    std::cout << "*\n";
  }

  Point* clone() const {
    return new Point;
  }

  std::string to_string() const {
    return "Point";
  }

  void debug() const {
    Shape::debug();
  }
};

#endif
