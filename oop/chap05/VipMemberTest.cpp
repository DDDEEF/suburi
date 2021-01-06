#include <iostream>
#include "VipMember.h"

using namespace std;

int main(){
  VipMember mineya("みねやたかし", 17, 89.2, "会費全額免除");

  double weight = mineya.get_weight();

  mineya.set_weight(weight - 15.3);

  cout << "会員番号" << mineya.no() << "の" << mineya.name()
       << "は" << mineya.get_weight() << "kgで"
       << "特典は" << mineya.get_privilege() << "です。\n";
}
