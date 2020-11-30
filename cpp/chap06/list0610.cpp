#include <iostream>

using namespace std;

void put_nchar(char c, int n){
  while(n-- > 0){
    cout << c;
  }
}

void put_square(int n, char c){
  for(int i = 1; i <= n; i++){
    put_nchar(c, n);
    cout << '\n';
  }
}

void put_rectangle(int h, int w, char c){
  for(int i = 1; i <= h; i++){
    put_nchar(c, w);
    cout << '\n';
  }
}

int main(){
  int n, h, w;
  cout << "正方形を表示します。\n";
  cout << "一辺は:"; cin >> n;
  put_square(n, '*');
  cout << "長方形を表示します。\n";
  cout << "高さは:"; cin >> h;
  cout << "横幅は:"; cin >> w;
  put_rectangle(h, w, '+');
}
