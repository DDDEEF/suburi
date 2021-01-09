#ifndef ___Class_Line
#define ___Class_Line

#include <string>
#include <sstream>
#include <iostream>
#include "Shape.h"

class Line : public Shape{
protected:
  int length;
public:
  Line(int len) : length(len){}
  int get_length() const { return length; }
  void set_length(int len) { length = len; }
  void debug() const {
    Shape::debug();
    std::cout << "length:" << length << '\n';
  }
};

class HorzLine : public Line{
public:
  HorzLine(int len) : Line(len) {}
  HorzLine* clone() const {
    return new HorzLine(length);
  }
  void draw() const {
    for(int i = 1; i <= length; i++){
      std::cout << '-';
    }
    std::cout << '\n';
  }
  std::string to_string() const {
    std::ostringstream os;
    os << "HorzLine(length:" << length << ")";
    return os.str();
  }
};

class VertLine : public Line {
public:
  VertLine(int len) : Line(len){}
  VertLine* clone() const {
    return new VertLine(length);
  }
  void draw() const{
    for(int i = 1; i <= length; i++){
      std::cout << "|\n";
    }
  }
  std::string to_string() const {
    std::ostringstream os;
    os << "VertLine(length:" << length << ")";
    return os.str();
  }
};

#endif
