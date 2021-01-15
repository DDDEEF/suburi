#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

template <class Type>
struct is_even : public unary_function<const Type&, bool>{
  bool operator() (const Type& n){
    return n % 2 == 0;
  }
};

template <class Type>
struct plus10 : public unary_function<const Type&, const Type&>{
  Type operator()(const Type& n){
    return n + 10;
  }
};

template <class Type>
struct diff : public binary_function<const Type&, const Type&, Type>{
  Type operator()(const Type& a1, const Type& a2){
    return (a1 < a2) ? a2 - a1 : a1 - a2;
  }
};

int main(){
  vector<int> a;
  for(vector<int>::size_type i = 0; i < 10; i++){
    a.push_back(i);
  }

  vector<int> b(a);
  random_shuffle(b.begin(), b.end());

  vector<bool> c(10);
  transform(a.begin(), a.end(), c.begin(), is_even<int>());

  vector<int> d(10);
  transform(a.begin(), a.end(), d.begin(), plus10<int>());

  vector<int> e(10);
  transform(a.begin(), a.end(), b.begin(), e.begin(), diff<int>());

  cout << "a = "; print(a.begin(), a.end()); cout << '\n';
  cout << "b = "; print(b.begin(), b.end()); cout << '\n';
  cout << "c = "; print(c.begin(), c.end()); cout << '\n';
  cout << "d = "; print(d.begin(), d.end()); cout << '\n';
  cout << "e = "; print(e.begin(), e.end()); cout << '\n';
}
