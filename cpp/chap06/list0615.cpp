#include <limits>
#include <iostream>

using namespace std;

int main(){
  cout << "char型のビット数:" << numeric_limits<unsigned char>::digits << '\n';
  cout << "short型のビット数" << numeric_limits<unsigned short>::digits << '\n';
  cout << "int型のビット数" << numeric_limits<unsigned int>::digits << '\n';
  cout << "long型のビット数" << numeric_limits<unsigned long>::digits << '\n';
}
