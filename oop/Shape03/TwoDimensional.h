#ifndef ___Class_TwoDimensional
#define ___Class_TwoDimensional

class TwoDimensional{
public:
  virtual ~TwoDimensional() = 0;
  virtual double get_area() const = 0;
};

inline TwoDimensional::~TwoDimensional(){}

#endif
