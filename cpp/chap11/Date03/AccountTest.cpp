#include <iostream>
#include "Date.h"
#include "Account.h"

using namespace std;

int main(){
  Account suzuki("鈴木龍一", "12345678", 1000, Date(2125, 1, 24));
  string dw[] = {"日", "月", "火", "水", "木", "金", "土"};

  cout << "鈴木くんの口座\n";
  cout << "口座名義=" << suzuki.name() << '\n';
  cout << "口座番号=" << suzuki.no() << '\n';
  cout << "預金額=" << suzuki.balance() << "円\n";
  cout << "開設日=" << suzuki.opening_date();
  cout << "(" << dw[suzuki.opening_date().day_of_week()] << ")\n";
}
