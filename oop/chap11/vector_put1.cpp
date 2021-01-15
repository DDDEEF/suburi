#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

template <class Type>
struct put1 : public unary_function<const Type&, void>{
  void operator()(const Type& n){
    cout << n << ' ';
  }
};

template <class Type>
struct put2 : public unary_function<const Type&, void>{
  void operator()(const Type& n){
    cout << n << " ";
  }
};

int main(){
  vector<int> x;
  for(vector<int>::size_type i = 0; i < 10; i++){
    x.push_back(i);
  }

  for_each(x.begin(), x.end(), put1<int>());
  cout << '\n';

  for_each(x.begin(), x.end(), put2<int>());
  cout << '\n';
}
