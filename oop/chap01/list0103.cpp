#include <string>
#include <iostream>

using namespace std;

class Accounting{
private:
  string full_name;
  long crnt_asset;
public:
  Accounting(string name, long asset){
    full_name = name;
    crnt_asset = asset;
  }

  string name(){
    return full_name;
  }

  long asset(){
    return crnt_asset;
  }

  void earn(long yen){
    crnt_asset += yen;
  }

  void spend(long yen){
    crnt_asset -= yen;
  }
};

int main(){
  Accounting nakano("なかのたろう", 1000);
  Accounting yamada("やまだけんた", 200);

  nakano.spend(200);
  yamada.earn(100);

  cout << "・なかの:\"" << nakano.name() << "\"" << nakano.asset() << "円\n";
  cout << "・やまだ:\"" << yamada.name() << "\"" << yamada.asset() << "円\n";
}
