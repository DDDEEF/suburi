#include <cstring>
#include <iostream>

using namespace std;

int main(){
  char s1[8] = "";
  char s2[8] = "ABC";
  char s3[8] = "AB\0CDEF";

  cout << "strlen(s1) = " << strlen(s1) << '\n';
  cout << "strlen(s2) = " << strlen(s2) << '\n';
  cout << "strlen(&s2[1]) = " << strlen(&s2[1]) << '\n';
  cout << "strlen(s3) = " << strlen(s3) << '\n';
  cout << "strlen(\"XYZ\") = " << strlen("XYZ") << '\n';
  cout << "strlen(&\"XYZ\"[1]) = " << strlen(&"XYZ"[1]) << '\n';
  cout << "strlen(\"ABC\\0DEF\") = " << strlen("ABC\0DEF") << '\n';
  cout << "sizeof(\"ABC\\0DEF\") = " << sizeof("ABC\0DEF") << '\n';
}
