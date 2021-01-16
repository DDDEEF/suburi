#include <string>
#include <iostream>

using namespace std;

void print_string_idx(const string& s){
  for(string::size_type i = 0; i < s.length(); i++){
    cout << s[i];
  }
}

void print_string_it1(const string& s){
  for(string::const_iterator i = s.begin(); i != s.end(); i++){
    cout << *i;
  }
}

template<class InputIterator>
void print_string_it2(InputIterator first, InputIterator last){
  for(InputIterator i = first; i != last; i++){
    cout << *i;
  }
}

int main(){
  string s1;
  cout << "文字列:";
  cin >> s1;

  print_string_idx(s1);                    cout << '\n';
  print_string_it1(s1);                    cout << '\n';
  print_string_it2(s1.begin(), s1.end());  cout << '\n';
}
