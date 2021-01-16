#include <string>
#include <iostream>

using namespace std;

int main(){
  string txt, pat;

  cout << "文字列txt:"; getline(cin, txt);
  cout << "文字列pat:"; getline(cin, pat);

  string::size_type pos = txt.find(pat);
  if(pos == string::npos){
    cout << "patはtxtに含まれません。\n";
  }else{
    cout << "patはtxtの" << (pos + 1) << "文字目に含まれます。\n";
  }
}
