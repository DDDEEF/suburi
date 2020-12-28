#include <sstream>
#include <iostream>

using namespace std;

int main(){
  string s = "2125/12/18";
  istringstream is(s);
  int y, m, d;
  char ch;
  is >> y >> ch >> m >> ch >> d;
  cout << y << "年" << m << "月" << d << "日\n";
}
