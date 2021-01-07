#include <string>
#include <iostream>
#include "SeniorMember.h"

using namespace std;

SeniorMember::SeniorMember(const string& name, int no, double w, int level) : Member(name, no, w)
{
  set_care_level(level); 
}

void SeniorMember::print() const{
  cout << "No." << no() << ":" << name() << "(" << get_weight() << "kg)"
       << "要介護度=" << care_level << '\n';
}
