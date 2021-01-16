#include <string>
#include <cstring>
#include <iostream>

using namespace std;

int main(){
  char cst[100];
  string str;
  cout << "文字列を入力せよ\n";
  cin >> str;

  strcpy(cst, str.c_str());
  cout << "cst = " << cst << '\n';
  cout << "str = " << str << '\n';
}
