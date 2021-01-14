#include <vector>
#include <iostream>

using namespace std;

int main(){
  vector<int> v(5);
  int value = 5;

  for(vector<int>::reverse_iterator p = v.rbegin(); p != v.rend(); p++){
    *p = value--;
  }

  for(vector<int>::const_iterator p = v.begin(); p != v.end(); p++){
    cout << *p << ' ';
  }
  cout << '\n';

  vector<int>::difference_type d1 = v.end() - v.begin();
  vector<int>::difference_type d2 = v.rend() - v.rbegin();
  cout << "v.end() - v.begin() = " << d1 << '\n';
  cout << "v.rend() - v.rbegin() = " << d2 << '\n';
}
