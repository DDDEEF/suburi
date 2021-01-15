#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

template<class InputIterator>
void print(InputIterator first, InputIterator last){
  cout << "{";
  for(InputIterator i = first;i != last; i++){
    cout << *i << ' ';
  }
  cout << "}";
}

int main(){
  vector<int> x;
  for(vector<int>::size_type i = 0; i < 10; i++){
    x.push_back(i);
  }

  random_shuffle(x.begin(), x.end());
  cout << "シャッフル:"; print(x.begin(), x.end()); cout << '\n';

  sort(x.begin(), x.end());
  cout << "昇順ソート:"; print(x.begin(), x.end()); cout << '\n';

  sort(x.begin(), x.end(), greater<int>());
  cout << "降順ソート:"; print(x.begin(), x.end()); cout << '\n';
}
