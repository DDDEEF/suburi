#include <cctype>
#include <iostream>

using namespace std;

void put_upper(const char s[]){
  for(int i = 0; s[i]; i++){
    cout << static_cast<char>(toupper(s[i]));
  }
}

int main(){
  char str[36];
  cout << "文字列:";
  cin >> str;
  put_upper(str);
  cout << '\n';
}
