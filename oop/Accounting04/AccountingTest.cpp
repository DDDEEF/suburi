#include <string>
#include <iostream>
#include "Accounting.h"

using namespace std;

void print_Accounting(string title, Accounting* p){
  cout << title << "\"" << p->name() << "\"" << p->asset() << "円\n";
}

int main(){
  Accounting nakano("なかのたろう", 1000);
  Accounting yamada("やまだけんた", 200);

  nakano.spend(200);
  yamada.earn(100);

  print_Accounting("・なかの:", &nakano);
  print_Accounting("・やまだ:", &yamada);
}
