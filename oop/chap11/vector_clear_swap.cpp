#include <vector>
#include <iostream>

using namespace std;

void print_vector_int(const vector<int>& v){
  cout << "{";
  for(vector<int>::size_type i = 0; i != v.size(); i++){
    cout << v[i] << ' ';
  }
  cout << "}";
}

int main(){
  int a[] = {1, 2, 3, 4, 5};
  int b[] = {4, 3, 2, 1 };

  vector<int> x(a, a + sizeof(a) / sizeof(a[0]));
  vector<int> y(b, b + sizeof(b) / sizeof(b[0]));

  cout << "x = "; print_vector_int(x); cout << '\n';
  cout << "y = "; print_vector_int(y); cout << '\n';

  x.swap(y);
  cout << "xとyの全要素を交換しました。\n";
  cout << "x = "; print_vector_int(x); cout << '\n';
  cout << "y = "; print_vector_int(y); cout << '\n';

  x.clear();
  cout << "xとyの全要素を削除しました。\n";
  cout << "x = "; print_vector_int(x); cout << '\n';
  cout << "y = "; print_vector_int(y); cout << '\n';
}

