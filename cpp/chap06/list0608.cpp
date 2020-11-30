#include <iostream>

using namespace std;

void put_stars(int n){
  while(n-- > 0){
    cout << '*';
  }
}

int main(){
  int n;

  cout << "左下直角の二等辺三角形を表示します。\n";
  cout << "段数は:";
  cin >> n;

  for(int i = 1; i <= n; i++){
    put_stars(i);
    cout << '\n';
  }
}
