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

int main(){
  Employee obj[3];

  obj[0].number = 1234;
  strcpy(obj[0].name, "田中一郎");
  obj[0].salary = 200000;

  obj[1].number = 1235;
  strcpy(obj[1].name, "佐藤二朗");
  obj[1].salary = 250000;

  obj[2].number = 1236;
  strcpy(obj[2].name, "鈴木三郎");
  obj[2].salary = 300000;

  for(int i = 0; i < 3; i++){
    obj[i].showData();
  }

  return 0;
}
