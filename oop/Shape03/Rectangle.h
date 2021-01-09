#ifndef ___Class_Rectangle
#define ___Class_Rectangle

#include <string>
#include <sstream>
#include <iostream>
#include "Shape.h"
#include "TwoDimensional.h"

class Rectangle : public Shape, public TwoDimensional{
  int width;
  int height;
public:
  Rectangle(int w, int h) : width(w), heigth(h) {}
  Rectangle* clone() const{
    return new Rectangle(width, height);
  }
  void draw() const {
    for(int i = 1; i <= height; i++){
      for(int j = 1; j <= width; j++){
        std::cout << '*';
      }
      std::cout << '\n';
    }
  }
  std::string to_string() const{
    std::ostringstream os;
    os << "Rectangle(width:" << width << ", heigth:" << height << ")";
    return os.str();
  }
  void debug() const{
    Shape::debug();
    std::cout << "width:" << width << '\n';
    std::cout << "height:" << height << '\n';
  }
  double get_area() const{
    return width * height;
  }
};

#endif
