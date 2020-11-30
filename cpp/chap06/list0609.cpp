#include <iostream>

using namespace std;

void put_nchar(char c, int n){
  while(n-- > 0){
    cout << c;
  }
}

int main(){
  int n;

  cout << "右下直角の二等辺三角形を表示します。\n";
  cout << "段数は:";
  cin >> n;

  for(int i = 1; i <= n; i++){
    put_nchar(' ', n - i);
    put_nchar('*', i);
    cout << '\n';
  }
}
