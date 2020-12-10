#include <string>
#include "Date.h"

class Account{
  std::string full_name;
  std::string number;
  long crnt_balance;
  Date open;
public:
  Account(std::string name, std::string num, long amnt, int y, int m, int d);

  void deposit(long amnt);
  void withdraw(long amnt);

  std::string name() const { return full_name; }
  std::string no() const { return number; }
  long balance() const { return crnt_balance; }
  Date opening_date() const { return open; }
};

