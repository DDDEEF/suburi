#include <iostream>
#include <cstring>
using namespace std;

class CellPhone{
public:
  char number[20];
  bool smart;
  CellPhone();
  ~CellPhone();
};

CellPhone::CellPhone(){
  cout << "CellPhoneクラスのコンストラクが呼び出されました。\n"; 
}

CellPhone::~CellPhone(){
  cout << "CellPhoneクラスのデストラクタが呼び出されました。\n";
}

class Employee{
public:
  int number;
  char name[80];
  int salary;
  CellPhone phone;
  void showData();
  Employee();
  ~Employee();
};

void Employee::showData(){
  cout << "社員番号:" << number << "\n";
  cout << "氏名:" << name << "\n";
  cout << "給与:" << salary << "\n";
  cout << "携帯電話番号:" << phone.number << "\n";
  cout << "スマホかどうか:" << phone.smart << "\n";
}

Employee::Employee(){
  cout << "Employeeクラスのコンストラクタが呼び出されました\n";
}

Employee::~Employee(){
  cout << "Employeeクラスのデストラクタが呼び出されました。\n";
}

int main(){
  Employee tanaka;
  
  tanaka.number = 1234;
  strcpy(tanaka.name, "田中一郎");
  tanaka.salary = 2000000;
  strcpy(tanaka.phone.number, "1111-1111-1111");
  tanaka.phone.smart = true;
  tanaka.showData();

  return 0;
}
