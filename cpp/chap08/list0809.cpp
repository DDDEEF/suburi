#include <iostream>

using namespace std;

int main(){
  char s[] = "ABC";
  cout << "s = \"" << s << "\"\n";
  s = "XYZ"; //エラー
  cout << "s = \"" << s << "\"\n";
}
