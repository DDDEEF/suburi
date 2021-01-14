#include <vector>
#include <iostream>

using namespace std;

int main(){
  vector<int> x;
  vector<int> y;

  cout << "xの要素を入力せよ\n・9999\n";
  for(int i = 0; ; i++){
    cout << "x[" << i << "] = ";
    int temp;
    cin >> temp;
    if(temp == 9999) break;
    x.push_back(temp);
  }

  cout << "yの要素を入力せよ\n・9999\n";
  for(int i = 0; ; i++){
    cout << "y[" << i << "] = ";
    int temp;
    cin >> temp;
    if(temp == 9999) break;
    y.push_back(temp);
  }

  cout << boolalpha;
  cout << "x == y " << (x == y) << '\n';
  cout << "x != y " << (x != y) << '\n';
  cout << "x <  y " << (x <  y) << '\n';
  cout << "x <= y " << (x <= y) << '\n';
  cout << "x >  y " << (x >  y) << '\n';
  cout << "x >= y " << (x >= y) << '\n'; 
}
