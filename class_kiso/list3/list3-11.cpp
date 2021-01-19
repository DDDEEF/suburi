#include <iostream>
#include <cstring>
using namespace std;

class Employee{
public:
  int number;
  char name[80];
  int salary;
  void showData();
};

void Employee::showData(){
  cout << number << "\n";
  cout << name << "\n";
  cout << salary << "\n";
}

class MySample{
public:
  void useObject(Employee *obj);
  Employee* retObject();
};

void MySample::useObject(Employee *obj){
  obj->showData();
}

Employee* MySample::retObject(){
  static Employee obj;
  obj.number = 1234;
  strcpy(obj.name, "田中一郎");
  obj.salary = 200000;

  return &obj;
}

int main(){
  Employee *someone;
  MySample ms;

  someone = ms.retObject();
  ms.useObject(someone);

  return 0;
}
