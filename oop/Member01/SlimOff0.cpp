#include <iostream>
#include "Member.h"
#include "VipMember0.h"

using namespace std;

void slim_off(Member& m, double dw){
  double weight = m.get_weight();
  if(weight > dw){
    m.set_weight(weight - dw);
  }
}

void slim_off(VipMember0& m, double dw){
  double weight = m.get_weight();
  if(weight > dw){
    m.set_weight(weight - dw);
  }
}

int main(){
  Member kaneko("かねこけん", 15, 75.2);
  VipMember0 mineya("みねやたろう", 17, 89.2, "会費全額免除");

  slim_off(kaneko, 3.7);
  cout << "No." << kaneko.no() << ":" << kaneko.name()
       << "(" << kaneko.get_weight() << "kg)\n";

  slim_off(mineya, 15.3);
  cout << "No." << mineya.no() << ":" << mineya.name()
       << "(" << mineya.get_weight() << "kg)"
       << "特典=" << mineya.get_privilege() << '\n';

}
