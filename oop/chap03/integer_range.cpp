#include <limits>
#include <iostream>

using namespace std;

int main(){
  cout << "この処理系の整数型で表現できる値\n";

  cout << "unsigned char:" << int(numeric_limits<unsigned char>::min()) << "~"
                           << int(numeric_limits<unsigned char>::max()) << '\n';

  cout << "unsinged int:" << numeric_limits<unsigned int>::min() << "~"
                          << numeric_limits<unsigned int>::max() << '\n';

  cout << "usigned long:" << numeric_limits<unsigned long>::min() << "~"
                          << numeric_limits<unsigned long>::max() << '\n';
}
