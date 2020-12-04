#include <cstring>
#include <iostream>

using namespace std;

int main(){
  char str[100];

  cout << "文字列を入力してください:";
  cin >> str;
  cout << "文字列\"" << str << "\"の長さは" << strlen(str) << "です。\n";
}
