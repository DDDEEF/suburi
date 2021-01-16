#include <string>
#include <iostream>

using namespace std;

template <class CharT, class Traits, class Allocator>
basic_string<CharT, Traits, Allocator>& replace_substr(
  basic_string<CharT, Traits, Allocator>& s1,
  const basic_string(CharT, Traits, Allocator)& s2,
  const basic_string(CharT, Traits, Allocator)& s3
)
{
  typename basic_string<CharT, Traits, Allocator>::size_type pos = s1.find(d2);
  if(pos != basic_string<CharT, Traits, Allocator>::npos){
    s1.replace(pos, s2.length(), s3);
  }
  return s1;
}

int main(){
  string s1, s2, s3;

  cout << "s1中の最も先頭に位置するs2をs3に置換します。\n";
  cout << "文字列s1:"; getline(cin, s1);
  cout << "文字列s2:"; getline(cin, s2);
  cout << "文字列s3:"; getline(cin, s3);

  cout << "置換後s1:" << replace_substr(s1, s2, s3) << '\n';
}
