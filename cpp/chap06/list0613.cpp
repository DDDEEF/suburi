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
  for(int i = int_bits() - 1; i >= 0; i--){
    cout << ((x >> i) & 1U ? '1' : '0');
  }
}

int main(){
  unsigned a, b;

  cout << "非負の整数を二つ入力せよ。\n";
  cout << "a:"; cin >> a;
  cout << "b:"; cin >> b;

  cout << "a = "; print_bits(a); cout << '\n';
  cout << "b = "; print_bits(b); cout << '\n';
  cout << "a & b = "; print_bits(a & b); cout << '\n';
  cout << "a | b = "; print_bits(a | b); cout << '\n';
  cout << "a ^ b = "; print_bits(a ^ b); cout << '\n';
  cout << "~a    = "; print_bits(~a); cout << '\n';
  cout << "~b    = "; print_bits(~b); cout << '\n';
}
