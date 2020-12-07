#include <string>
#include <iostream>

using namespace std;

class Account{
private:
  string full_name;
  string number;
  long crnt_balance;
public:
  Account(string name, string num, long amnt){
    full_name = name;
    number = num;
    crnt_balance = amnt;
  }

  string name(){
    return full_name;
  }

  string no(){
    return number;
  }

  long balance(){
    return crnt_balance;
  }

  void deposit(long amnt){
    crnt_balance += amnt;
  }

  void withdraw(long amnt){
    crnt_balance -= amnt;
  }
};

int main(){
  Account suzuki("鈴木龍一", "12345678", 1000);
  Account takeda("武田浩文", "87654321", 200);
  suzuki.withdraw(200);
  takeda.deposit(100);

  cout << "鈴木くんの口座:\"" << suzuki.name() << "\"(" << suzuki.no() << ")" << suzuki.balance() << "円\n";
  cout << "武田くんの口座:\"" << takeda.name() << "\"(" << takeda.no() << ")" << takeda.balance() << "円\n"; 
}
