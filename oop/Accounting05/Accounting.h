#ifndef ___Class_Accounting
#define ___Class_Accounting

#include <string>
#include "Date.h"

class Accounting{
  std::string full_name;
  long crnt_asset;
  Date birth;
public:
  Accounting(const std::string& name, long amnt, int y, int m, int d);
  void earn(long amnt);
  void spend(long amnt);
  std::string name() const { return full_name; }
  long asset() const { return crnt_asset; }
  Date birthday() const { return birth; }
};

#endif
