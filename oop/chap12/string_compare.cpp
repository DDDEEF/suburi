#include <string>
#include <iostream>

using namespace std;

void put_comp_result(int cmp){
  if(cmp < 0){
    cout << "より小さいです。\n";
  }else if(cmp > 0){
    cout << "より大きいです。\n";
  }else{
    cout << "と一致します。\n";
  }
}

int main(){
  int n;
  string s1, s2;
  cout << "文字列s1:";       cin >> s1;
  cout << "文字列s2:";       cin >> s2;
  cout << "部分比較文字数:"; cin >> n;

  cout << boolalpha;
  cout << "s1 == s2 " << (s1 == s2) << '\n';
  cout << "s1 != s2 " << (s1 != s2) << '\n';
  cout << "s1 <  s2"  << (s1 <  s2) << '\n';
  cout << "s1 <= s2 " << (s1 <= s2) << '\n';
  cout << "s1 >  s2 " << (s1 >  s2) << '\n';
  cout << "s1 >= s2 " << (s1 >= s2) << '\n';
  
  cout << "s1はs2";
  put_comp_result(s1.compare(s2));
  
  cout << "s1の先頭" << n << "文字はs2の先頭" << n << "文字";
  put_comp_result(s1.compare(0, n, s2, 0, n));

  cout << "s1は\"ABC\"";
  put_comp_result(s1.compare("ABC"));
}
