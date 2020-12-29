#include <iostream>
#include "Accounting.h"

using namespace std;

int main(){
  Accounting nakano("なかのたつと", 1000, 2125, 1, 24);
  Accounting yamada("やまだたろう", 200, 2123, 7, 15);

  nakano.spend(200);
  yamada.earn(100);

  cout << "なかのくん\n";
  cout << "氏名=" << nakano.name() << '\n';
  cout << "資産=" << nakano.asset() << "円\n";
  cout << "誕生日=" << nakano.birthday().year() << "年"
                    << nakano.birthday().month() << "月"
                    << nakano.birthday().day() << "日\n";

  cout << "やまだくん\n";
  cout << "氏名=" << yamada.name() << '\n';
  cout << "資産=" << yamada.asset() << "円\n";
  cout << "誕生日=" << yamada.birthday() << '\n';
}
