#ifndef ___Class_RectEquilTriangle
#define ___Class_RectEquilTriangle

#include <string>
#include <sstream>
#include <iostream>
#include "Shape.h"
#include "TwoDimensional.h"

class RectEquilTriangle : public Shape, public TwoDimensional{
protected:
  int length;
public:
  RectEquilTriangle(int len) : length(len) {}
  double get_area() const {
    return length * length / 2.0;
  }
};

class RectEquilTriangleLB : public RectEquilTriangle{
public:
  RectEquilTriangleLB(int len) : RectEquilTriangle(len) {}
  RectEquilTriangleLB* clone() const {
    return new RectEquilTriangleLB(length);
  }
  void draw() const {
    for(int i = 1; i <= length; i++){
      for(int j = 1; j <= i; j++){
        std::cout << '*';
      }
      std::cout << '\n';
    }
  }
  std::string to_string() const {
    std::ostringstream os;
    os << "RectEquilTriangleLB(length:" << length << ")";
    return os.str();
  }
  void debug() const {
    Shape::debug();
    std::cout << "クラス:RectEquilTriangleLB\n";
    std::cout << "アドレス" << this << '\n';
    std::cout << "length:" << length << '\n';
  }
};

class RectEquilTriangleRU : public RectEquilTriangle {
public:
  RectEquilTriangleRU(int len) : RectEquilTriangle(len) {}
  RectEquilTrinagleRU* clone() const {
    return new RectEquilTriangleRU(length);
  }
  void draw() const{
    for(int i = 1; i <= length; i++){
      for(int j = 1; j <= i - 1; j++){
        std::cout << ' ';
      }
      for(int j = 1; j <= length - i + 1; j++){
        std::cout << '*';
      }
      std::cout << '\n';
    }
  }
  std::string to_string() const{
    std::ostringstream os;
    os << "RectEquilTriangleRU(length:" << length << ")";
    return os.str();
  }
  void debug() const{
    Shape::debug();
    std::cout << "クラス:RectEquilTriangleRU\n";
    std::cout << "アドレス" << this << '\n';
    std::cout << "length:" << length << '\n';
  }
};

#endif
