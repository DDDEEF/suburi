#ifndef ___Class_ResigningMember
#define ___Class_ResigningMember

#include <string>
#include <iostream>
#include "Member.h"

class ResigningMember : private Member{
public:
  ResigningMember(const std::string& name, int number, double w) : Member(name, number, w){}
  double get_weight(){
    std::cout << "退会した会員の体重の取得はできません。\n";
    return 0;
  }

  using Member::no;
};

#endif
