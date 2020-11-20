#include <iomanip>
#include <iostream>

using namespace std;

int main(){
  cout << oct << 1234 << '\n';
  cout << dec << 1234 << '\n';
  cout << hex << 1234 << '\n';

  cout << showbase;
  cout << oct << 1234 << '\n';
  cout << dec << 1234 << '\n';
  cout << hex << 1234 << '\n';

  cout << setw(10) << internal << "abc\n";
  cout << setw(10) << left << "abc\n";
  cout << setw(10) << right << "abc\n";
}
