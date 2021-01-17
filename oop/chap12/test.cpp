#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> strptary_to_vec(char** p, int n){
  vector<string> temp;
  for(int i = 0; i < n; i++){
    temp.push_back(p[i]);
  }
  return temp;
}

int main(int argc, char** argv){
  vector<string> arg = strptary_to_vec(argv, argc);
  for(vector<string>::size_type i = 0; i < arg.size(); i++){
    cout << "arg[" << i << "] = " << argv[i] << '\n';
  }

  string s1, s2;

  cout << "文字列s1:"; getline(cin, s1);
  cout << "文字列s2:"; getline(cin, s2);

  cout << "s1 = ";
  for(string::size_type i = 0; i < s1.length(); i++){
    cout << s1[i];
  }
  cout << '\n';

  cout << "s2 = ";
  for(string::const_iterator i = s2.begin(); i != s2.end(); i++){
    cout << *i;
  }
  cout << '\n';

  string::size_type idx = s1.find(s2);
  if(idx == string::npos){
    cout << "s2はs1に含まれません。\n";
  }else{
    cout << "s2はs1の" << (idx + 1) << "文字目に含まれます。\n";
  }
}
