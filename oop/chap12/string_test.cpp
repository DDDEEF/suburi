#include <string>
#include <iostream>

using namespace std;

int main(){
  string s1 = "ABC";
  string s2 = s1 + "DEF";
  string s3;

  cout << "文字列を入力せよ";
  cin >> s3;

  cout << "その文字列は\"" + s1 + "\"と等し" +
          ((s3 == s1) ? "いです。\n" : "くありません。\n");

  cout << "その文字列は\"" + s2 + "\"より小さ" +
          ((s3 < s2) ? "いです。\n" : "くありません。\n");
}
