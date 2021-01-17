#include <string>
#include <iostream>

using namespace std;

void put_string_ary(const string* s, size_t n){
  cout << "{";
  for(size_t i = 0; i < n; i++){
    cout << '"';
    for(string::size_type j = 0; j < s[i].length(); j++){
      cout << s[i][j];
    }
    cout << "\" ";
  }
  cout << "}";
}

int main(){
  string s1[3];
  string s2[3] = {"ABC", "123", "XYZ"};

  cout << "s1 = ";
  put_string_ary(s1, sizeof(s1) / sizeof(s1[0]));
  cout << '\n';

  cout << "s2 = ";
  put_string_ary(s2, sizeof(s2) / sizeof(s2[0]));
  cout << '\n';
}
