#include <vector>
#include <iostream>

using namespace std;

int main(){
  int m, n;
  cout << "行数:"; cin >> m;
  cout << "列数:"; cin >> n;

  vector<vector<int> > x(m, vector<int>(n));

  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      cout << "x[" << i << "][" << j << "] = " << x[i][j] << '\n';
    }
  }
}
