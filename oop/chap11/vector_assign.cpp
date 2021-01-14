#include <vector>
#include <iostream>

using namespace std;

int main(){
  vector<double> x, y;

  y.push_back(5.2);
  x.assign(5, 3.14);

  y = x;

  for(vector<int>::size_type i = 0; i < y.size(); i++){
    cout << "y[" << i << "] = " << y[i] << '\n';
  }
}
