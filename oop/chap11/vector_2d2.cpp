#include <vector>
#include <iostream>

using namespace std;

int main(){
  int m;
  cout << "行数:";
  cin >> m;

  vector<vector<int> > x;
  for(int i = 0; i < m; i++){
    int width;
    cout << i << "行目の列数:";
    cin >> width;
    x.push_back(vector<int>(width));
  }

  for(int i = 0; i < m; i++){
    for(int j = 0; j < x[i].size(); j++){
      cout << "x[" << i << "][" << j << "] = " << x[i][j] << '\n'; 
    }
  }
}
