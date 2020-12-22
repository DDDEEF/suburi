#include <iostream>
#include "Member.h"

using namespace std;

Member::Member(string name, int number, int grade){
  full_name = name;
  no = number;
  rank = grade;
}

void Member::print(){
  cout << "No." << no << ":" << full_name << "[ランク:" << rank << "]\n"; 
}
