#include <string>
#include <iostream>

using namespace std;

int main(){
  string s0;
  string s1("ABCDEFGHIJK");
  string s2("ABCDEFGHIJK", 5);
  string s3(7, '*');
  string s4(s1);
  string s5(s1, 5, 3);

  cout << "s0 = " << s0 << '\n';
  cout << "s1 = " << s1 << '\n';
  cout << "s2 = " << s2 << '\n';
  cout << "s3 = " << s3 << '\n';
  cout << "s4 = " << s4 << '\n';
  cout << "s5 = " << s5 << '\n';
}
