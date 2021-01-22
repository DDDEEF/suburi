#include <iostream>
#include "Employee.h"
using namespace std;

int main(){
  cout << Employee::companyName << "\n";
  Employee tanaka;
  cout << tanaka.companyName << "\n";

  return 0;
}
