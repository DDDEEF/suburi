#include <iostream>
#include "VipMember.h"
#include "SeniorMember.h"

using namespace std;

int main(){
  VipMember mineya("みねやりゅうじ", 17, 89.2, "会費全額免除");
  SeniorMember susaki("すざきけんじ", 43, 63.7, 3);

  mineya.print();
  susaki.print();
}
