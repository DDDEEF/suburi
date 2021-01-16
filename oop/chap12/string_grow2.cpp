#include <string>
#include <iostream>

using namespace std;

template <class type>
void pad_char(basic_string<type>&s, type ch, typename basic_string<type>::size_type width){
  if(width > s.length()){
    s.append(width - s.length(), ch);
  }
}

int main(){
  string s1 = "ABC";
  wstring s2 = L"柴田";
  wcout.imbue(std::locale("JAPANESE"));

  pad_char(s1, '+', 10);
  pad_char(s2, L'+', 10);

  cout << "s1 = " << s1 << '\n';
  wcout << "s2 = " << s2 << '\n';
}
