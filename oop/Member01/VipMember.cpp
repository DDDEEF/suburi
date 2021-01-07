#include <iostream>
#include "VipMember.h"

using namespace std;

VipMember::VipMember(const string& name, int no, double w, const string& prv) : Member(name, no, w)
{
  set_privilege(prv); 
}

void VipMember::print() const{
  cout << "No." << no() << ":" << name() << "(" << get_weight() << "kg)"
       << "特典=" << privilege << '\n';
}
