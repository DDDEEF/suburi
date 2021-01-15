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

template <class InputIterator>
void print(InputIterator first, InputIterator last){
  cout << "{";
  for_each(first, last, put1<std::iterator_traits<InputIterator>::value_type>());
  cout << "}";
}

int main(){
  int ary[] = {1, 2, 3, 4, 5};
  vector<int> a(ary, ary + sizeof(ary) / sizeof(ary[0]));

  vector<int> b(a);
  random_shuffle(b.begin(), b.end());

  cout << "a = "; print(a.begin(), a.end()); cout << '\n';
  cout << "b = "; print(b.begin(), b.end()); cout << '\n';

  vector<int> c(a);
  transform(a.begin(), a.end(), b.begin(), c.begin(), plus<int>());
  cout << "和 = "; pirnt(c.begin(), c.end()); cout << '\n';

  transform(a.begin(), a.end(), b.begin(), c.begin(), multiplies<int>());
  cout << "積 = "; print(c.begin(), c.end()); cout << '\n';
}
