#ifndef ___Class_Shape
#define ___Class_Shape

class Shape{
public:
  virtual ~Shape() = 0;
  virtual Shape* clone() const = 0;
  virtual void draw() const = 0;
  virtual std::string to_string() const = 0;
  void print() const {
    std::cout << to_string() << '\n';
    draw();
  }
  virtual void debug() const = 0;
};

inline Shape::~Shape() {}

inline void Shape::debug() const {
  std::cout << "---デバッグ情報---\n";
  std::cout << "型:" << typeid(*this).name() << '\n';
  std::cout << "アドレス:" << this << '\n';
}

inline std::ostream& operatro<<(std::ostream& os, const Shape& s){
  return os << s.to_string();
}

#endif

