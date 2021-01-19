#include <iostream>
#include <cstring>
using namespace std;

class Employee{
public:
  int number;
  char name[80];
  int salary;
  void showData();
  Employee();
  Employee(int nu, const char* na, int sa);
};

void Employee::showData(){
  cout << number << "\n";
  cout << name << "\n";
  cout << salary << "\n";
}

Employee::Employee(){
  number = 0;
  strcpy(name, "未設定");
  salary = 150000;
}

Employee::Employee(int nu, const char* na, int sa){
  number = nu;
  strcpy(name, na);
  salary = sa;
}

int main(){
  Employee someone;
  someone.showData();
  Employee tanaka(1234, "田中一郎", 200000);
  tanaka.showData();
  
  return 0;
}
