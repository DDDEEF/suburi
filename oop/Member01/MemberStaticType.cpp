#include <iostream>
#include <typeinfo>
#include "Member.h"
#include "VipMember.h"
#include "SeniorMember.h"

using namespace std;

int main(){
  VipMember mineya("みねやりゅうじ", 17, 89.2, "会費全額免除");

  Member* ptr = &mineya;
  Member& ref =  mineya;

  cout << "ptrが指す先は" << typeid(*ptr).name() << "型オブジェクトです。\n";
  cout << "refが指す先は" << typeid(ref).name()  << "型オブジェクトです。\n";
}
