#include <string>
#include <iostream>

using namespace std;

int main(){
  string suzuki_name = "鈴木龍一";
  string suzuki_number = "12345678";
  long suzuki_balance = 1000;

  string takeda_name = "武田浩文";
  string takeda_number = "87654321";
  long takeda_balance = 300;

  suzuki_balance -= 200;
  takeda_balance += 100;

  cout << "鈴木くんの口座:\"" << suzuki_name << "\" (" << suzuki_number << ")" << suzuki_balance << "円\n";

  cout << "武田くんの口座:\"" << takeda_name << "\" (" << takeda_number << ")" << takeda_balance << "円\n";
}
