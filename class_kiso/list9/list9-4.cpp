#include <iostream>
#include <cstring>
using namespace std;

class Employee{
public:
  int number;
  char* name;
  int salary;
  Employee();
  Employee(const Employee &obj);
  ~Employee();
};

Employee::Employee(){
  name = new char[80];
  number = 0;
  strcpy(name, "未設定");
  salary = 150000;
  cout << "コンストラクタが呼び出されました。\n";
}

Employee::Employee(const Employee &obj){
  name = new char[80];
  number = obj.number;
  strcpy(name, obj.name);
  salary = obj.salary;
  cout << "コピーコンストラクタが呼び出されました。\n";
}

Employee::~Employee(){
  delete [] name;
  cout << "デストラクタが呼び出されました。\n";
}

void show(Employee obj);

int main(){
  Employee tanaka;
  tanaka.number = 1234;
  strcpy(tanaka.name, "田中一郎");
  tanaka.salary = 2000000;

  cout << "show()を呼び出します。\n";
  show(tanaka);
  cout << "show()を抜けました。\n";
  cout << "氏名:" << tanaka.name << "\n";

  return 0;
}

void show(Employee obj){
  cout << "社員番号:" << obj.number << "\n";
  cout << "氏名:" << obj.name << "\n";
  cout << "給与:" << obj.salary << "\n";
}
