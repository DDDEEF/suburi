#include <string>
#include <iostream>

using namespace std;

class Accounting{
public:
  string name;
  long asset;
};

int main(){
  Accounting nakano;
  Accounting yamada;

  nakano.name = "なかのたろう";
  nakano.asset = 1000;
  yamada.name = "やまだけん";
  yamada.asset = 200;

  nakano.asset -= 200;
  yamada.asset += 100;

  cout << "・なかの:\"" << nakano.name << "\"" << nakano.asset << "円\n";
  cout << "・やまだ:\"" << yamada.name << "\"" << yamada.asset << "円\n";
}
