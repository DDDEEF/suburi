#include <iostream>
#include "Company.h"
using namespace std;

int main(){
  Director d(1111, "役員一郎", 50000, 1000);
  Manager m1(2222, "課長一郎", 350000, 10000);
  Manager m2(3333, "課長次郎", 300000, 5000);
  Salesman s1(4444, "営業一郎", 230000, 1235);
  Salesman s2(5555, "営業二郎", 250000, 4567);
  Salesman s3(6666, "営業三郎", 270000, 6789);

  d.showData();
  cout << "*************************\n";
  m1.showData();
  cout << "*************************\n";
  m2.showData();
  cout << "*************************\n";
  s1.showData();
  cout << "*************************\n";
  s2.showData();
  cout << "*************************\n";
  s3.showData();
  cout << "*************************\n";
  
  return 0;
}
