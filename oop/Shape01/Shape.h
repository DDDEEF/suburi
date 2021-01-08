#ifndef ___Class_Shape
#define ___Class_Shape

#include <iostream>

class Shape{
public:
  virtual void draw() const = 0;
};

class Point : public Shape{
public:
  void draw() const{
    std::cout << "+\n";
  }
};

class Rectangle : public Shape{
  int width;
  int height;

public:
  Rectangle(int w, int h) : width(w), height(h) {}

  void draw() const{
    for(int i = 1; i <= height; i++){
      for(int j = 1; j <= width; j++){
        std::cout << '*';
      }
      std::cout << '\n';
    }
  }
};

#endif
