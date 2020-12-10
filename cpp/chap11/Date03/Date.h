#ifndef __Class_Date
#define __Class_Date

class Date{
  int y;
  int m;
  int d;
public:
  Date();
  Date(int yy, int mm = 1, int dd = 1);

  int year() const { return y; }
  int month() const { return m; }
  int day() const { return d; }

  Date preceding_day() const;
  int day_of_week() const;
  std::string to_string() const;
};

std::ostream& operator<<(std::ostream& s, const Date& x);
std::istream& operator<<(std::istream& s, Date& x);

#endif
