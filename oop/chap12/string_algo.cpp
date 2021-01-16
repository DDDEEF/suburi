#include <cctype>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

struct to_upper{
  char operator()(char c){ return toupper(c); }
};

struct to_lower{
  char operator()(char c){ return tolower(c); }
};

struct invert_case{
  char operator()(char c){
    return islower(c) ? toupper(c) : isupper(c) ? tolower(c) : c;
  }
};

int main(){
  string s1;
  cout << "文字列を入力せよ\n";
  cin >> s1;
  string s2(s1);

  transform(s1.begin(), s1.end(), s2.begin(), invert_case());
  cout << "大小の反転:" << s2 << '\n';

  transform(s1.begin(), s1.end(), s2.begin(), to_upper());
  cout << "全大文字化:" << s2 << '\n';

  transform(s1.begin(), s1.end(), s2.begin(), to_lower());
  cout << "全小文字化:" << s2 << '\n';

  random_shuffle(s1.begin(), s1.end());
  cout << "シャッフル:" << s1 << '\n';

  sort(s1.begin(), s1.end());
  cout << "昇順ソート:" << s1 << '\n';

  sort(s1.begin(), s1.end(), greater<char>());
  cout << "降順ソート:" << s1 << '\n';
}
