#include <string>
#include <iostream>
#include "Accounting.h"

using namespace std;

Accounting::Accounting(const string& name, long amnt, int y, int m, int d) : birth(y, m, d){
  full_name = name;
  crnt_asset = amnt;
}

void Accounting::earn(long amnt){
  crnt_asset += amnt;
}

void Accounting::spend(long amnt){
  crnt_asset -= amnt;
}
