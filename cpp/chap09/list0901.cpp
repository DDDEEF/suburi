#include <iostream>

using namespace std;

int maxof(const int x[], int n){
  int max = x[0];
  for(int i = 1; i < n; i++){
    if(x[i] > max){
      max = x[i];
    }
  }
  return max;
}

double maxof(const double x[], int n){
  double max = x[0];
  for(int i = 1; i < n; i++){
    if(x[i] > max){
      max = x[i];
    }
  }
  return max;
}

int main(){
  const int isize = 8;
  int ix[isize];

  cout << isize << "個の整数を入力せよ。\n";
  for(int i = 0; i < isize; i++){
    cout << i  + 1 << ":";
    cin >> ix[i];
  }

  cout << "最大値は" << maxof(ix, isize) << "です。\n\n";

  const int dsize = 5;
  double dx[dsize];

  cout << dsize << "個の実数を入力せよ\n";
  for(int i = 0; i < dsize; i++){
    cout << i + 1 << ":";
    cin >> dx[i];
  }

  cout << "最大値は" << maxof(dx, dsize) << "です。\n";
}
