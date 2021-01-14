#include <vector>
#include <iomanip>
#include <iostream>

using namespace std;

int main(){
  vector<int> v;

  cout << "要素数 容量\n";
  for(vector<int>::size_type i = 0; i < 10000; i++){
    v.push_back(i);
    cout << setw(6) << v.size()
         << setw(6) << v.capacity() << '\n';
  }
}
