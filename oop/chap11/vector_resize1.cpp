#include <vector>
#include <iostream>

using namespace std;

int main(){
  vector<int> x(2, 0);
  x.resize(6, 99);
  for(vector<int>::size_type i = 0; i < x.size(); i++){
    cout << "x["  << i << "] = " << x[i] << '\n';
  }
}
