#include <iostream>
#include "Member.h"
#include "VipMember.h"

using namespace std;

void slim_off(Member& m, double dw){
  double weight = m.get_weight();
  if(weight > dw){
    m.set_weight(weight - dw);
  }
}

int main(){
  Member kaneko("かねこけんた", 15, 72.2);
  slim_off(kaneko, 3.7);

  VipMember mineya("みねやりゅうじ", 17, 89.2, "会費全額免除");
  slim_off(mineya, 15.3);

  cout << "No." << kaneko.no() << ":" << kaneko.name()
       << "(" << kaneko.get_weight() << "kg)\n";

  cout << "No." << mineya.no() << ":" << mineya.name()
       << "(" << mineya.get_privileget() << '\n';
}
