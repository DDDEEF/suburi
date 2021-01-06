#include <iostream>
#include "Member.h"
#include "VipMember.h"

using namespace std;

int main(){
  Member kaneko("かねこけんた", 15, 75.2);
  VipMember mineya("みねやりゅうじ", 17, 89.2, "全額免除");

  Member* pm1 = &kaneko;
  cout << "pm1の氏名:" << pm1->name() << '\n';

  Member* pm2 = &mineya;
  cout << "pm2の氏名:" << pm2->name() << '\n';
//cout << "pm2の氏名:" << pm2->get_privilege() << '\n';

//VipMember* pv1 = &kaneko1;
//cout << "pv1の特典:" << pv1->get_privilege() << '\n';

  VipMember* pv2 = &mineya;
  cout << "pv2の特典:" << pv2->get_privilege() << '\n';
}
