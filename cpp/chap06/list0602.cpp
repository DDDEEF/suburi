#include <iostream>

using namespace std;

int max(int a, int b, int c){
  int max = a;
  if(b > max){
    max = b;  
  }

  if(c > max){
    max = c;
  }

  return max;
}

int main(){
  int math[3];
  int eng[3];

  for(int i = 0; i < 3; i++){
    cout << "[" << i + 1 << "]";
    cout << "数学:"; cin >> math[i];
    cout << "   英語:"; cin >> eng[i];
  }

  int max_math = max(math[0], math[1], math[2]);
  int max_eng = max(eng[0], eng[1], eng[2]);

  cout << "数学の最高点は" << max_math << "です。\n";
  cout << "英語の最高点は" << max_eng << "です。\n";
}
