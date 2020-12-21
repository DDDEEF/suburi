#include <iostream>
#include "IntStack.h"

using namespace std;

int main(){
  IntStack s1(5);
  s1.push(15);
  s1.push(31);

  IntStack s2(1);
  s2 = s1;
  s2.push(88);

  IntStack s3 = s2;
  s3.push(99);

  cout << "スタックs3に積まれているデータをすべてポップします。\n";
  while(!s3.empty())
    cout << s3.pop() << '\n';
}
