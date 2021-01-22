#include <iostream>
#include <cstring>
using namespace std;

class CellPhone{
public:
  char number[20];
  bool smart;
};

class Employee{
public:
  int number;
  char name[80];
  int salary;
  CellPhone phone;
  void showData();
};

void Employee::showData(){
  cout << "社員番号:" << number << "\n";
  cout << "氏名:" << name << "\n";
  cout << "給与:" << salary << "\n";
  cout << "携帯電話番号:" << phone.number << "\n";
  cout << "スマホかどうか:" << phone.smart << "\n";
}

Employee tanaka;

int main(){
  tanaka.number = 1234;
  strcpy(tanaka.name, "田中一郎");
  tanaka.salary = 200000;
  strcpy(tanaka.phone.number, "1111-1111-1111");
  tanaka.phone.smart = true;
  tanaka.showData();

  Employee sato;
  sato.number = 1235;
  strcpy(sato.name, "佐藤二朗");
  sato.salary = 2500000;
  strcpy(sato.phone.number, "2222-2222-2222");
  sato.phone.smart = true;
  sato.showData();

  Employee* suzuki = new Employee;
  suzuki->number = 1236;
  strcpy(suzuki->name, "鈴木三郎");
  suzuki->salary = 300000;
  strcpy(suzuki->phone.number, "3333-3333-3333");
  suzuki->phone.smart = false;
  suzuki->showData();
  delete suzuki;

  return 0;
}
