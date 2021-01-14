#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

int main(){
  int a[] = { 1, 2, 3, 4, 5 };
  vector<int> x(a, a + sizeof(a) / sizeof(a[0]));
  try{
    for(vector<int>::size_type i = 0; i <= 10; i++){
      cout << "x[" << i << "] = " << x.at(i) << '\n';
    }
  }catch(const out_of_range&){
    cout << "不正な添字です。\n";
    return 1;
  }
}
