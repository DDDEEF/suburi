#include <iostream>
#include <cstring>
using namespace std;

class Employee{
public:
  int number;
  char* name;
  int salary;
  Employee();
  ~Employee();
};

Employee::Employee(){
  name = new char[80];
  number = 0;
  strcpy(name, "未設定");
  salary = 150000;
  cout << "コンストラクが呼び出されました。\n";
}

Employee::~Employee(){
  delete [] name;
  cout << "デストラクタが呼び出されました。\n";
}

void show(Employee* ptr);

int main(){
  Employee tanaka;
  tanaka.number = 1234;
  strcpy(tanaka.name, "田中一郎");
  tanaka.salary = 20000;

  cout << "show()を呼び出しました。\n";
  show(&tanaka);
  cout << "show()を抜けました。\n";
  cout << "氏名:" << tanaka.name << "\n";
  return 0;
}

void show(Employee* ptr){
  cout << "社員番号:" << ptr->number << "\n";
  cout << "氏名:" << ptr->name << "\n";
  cout << "給与:" << ptr->salary << "\n";
}
