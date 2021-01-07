#include <iostream>
#include <typeinfo>
#include "Member.h"
#include "VipMember.h"
#include "SeniorMember.h"

using namespace std;

void senior_print(Member* p){
  SeniorMember* d = dynamic_cast<SeniorMember*>(p);
  if(d){
    d->print();
  }
}

int main(){
  Member kaneko("かねこけんた", 15, 75.2);
  VipMember mineya("みねやりゅうじ", 17, 89.2, "会費全額免除");
  SeniorMember susaki("すさきけんいち", 43, 63.7, 3);

  senior_print(&kaneko);
  senior_print(&mineya);
  senior_print(&susaki);
}
