#include <vector>
#include <iostream>

using namespace std;

int main(){
  vector<int> v(5);
  int value = 0;

  for(vector<int>::iterator p = v.begin(); p != v.end(); p++){
    *p = ++value;
  }

  for(vector<int>::const_iterator p = v.begin(); p != v.end(); p++){
    cout << *p << ' ';
  }
  cout << '\n';
}
