#include <iostream>
#include "ResigningMember.h"

using namespace std;

int main(){
  ResigningMember oda("おだのぶこ", 31, 48.7);

  cout << "番号=" << oda.no() << '\n';
//cout << "氏名=" << oda.name() << '\n';
  cout << "体重=" << oda.get_weight();
//oda.set_weight(45.3);
}
