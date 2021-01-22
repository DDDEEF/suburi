#include <iostream>
#include <cstring>
using namespace std;

class Employee{
public:
  static int objNum;
  static const char* companyName;
  int number;
  char name[80];
  int salary;
  void showData();
  Employee();
  Employee(const char* na, int sa);
};

int Employee::objNum = 0;
const char* Employee::companyName = "技術評論社";

Employee::Employee(){
  objNum++;
  number = objNum;
  strcpy(name, "未設定");
  salary = 150000;
}

Employee::Employee(const char* na, int sa){
  objNum++;
  number = objNum;
  strcpy(name, na);
  salary = sa;
}

void Employee::showData(){
  cout << "会社名:" << companyName << "\n";
  cout << "社員番号:" << number << "\n";
  cout << "氏名:" << name << "\n";
  cout << "給与:" << salary << "\n";
}

int main(){
  Employee tanaka("田中一郎", 200000);
  Employee sato("佐藤二郎", 250000);
  Employee someone;

  tanaka.showData();
  sato.showData();
  someone.showData();
  cout << "現在の社員数:" << Employee::objNum << "\n";

  return 0;
}
