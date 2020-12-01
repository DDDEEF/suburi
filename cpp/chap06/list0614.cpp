#include <iostream>

using namespace std;

int count_bits(unsigned x){
  int bits = 0;
  while(x){
    if(x & 1U){
      bits++;
    }
    x >>= 1;
  }
  return bits;
}

int int_bits(){
  return count_bits(~0U);
}

void print_bits(unsigned x){
  cout << "int_bits()-1:" << int_bits() - 1 << '\n';
  for(int i = int_bits() - 1; i >= 0; i--){
    cout << ((x >> i) & 1U ? '1' : '0');
  }
}


int main(){
  unsigned x, n;
  cout << "非負の整数:";  cin >> x;
  cout << "シフトするビット数:"; cin >> n;
  cout << "整数     = "; print_bits(x); cout << '\n';
  cout << "左シフト = "; print_bits(x << n); cout << '\n';
  cout << "右シフト = "; print_bits(x >> n); cout << '\n';
}

