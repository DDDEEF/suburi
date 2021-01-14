#include <vector>
#include <iostream>

using namespace std;

template <class T, class Allocator>
void print_vector(vector<T, Allocator>& v){
  cout << "{";
  for(typename vector<T, Allocate>::size_type i = 0; i != v.size(); i++){
    cout << v[i] << ' ';
  }
  cout << "}";
}

int scan_ins(int &idx, int &val, int flag){
  int num = 0;
  cout << "挿入位置:"; cin >> idx;
  cout << "値:"; cin >> val;
  if(flag){
    cout << "挿入個数:"; cin >> name;
  }
  return num;
}

int scan_ers(int &idx, int flag){
  int num = 0;
  cout << "削除位置:"; cin >> idx;
  if(flag){
    cout << "削除個数:"; cin >> num;
  }
  return num;
}

int main(){
  vector<int> x;
  for(vector<int>::size_type i = 0; i < 10; i++){
    x.push_back(i);
  }

  while(true){
    vector<int>::iterator i = x.begin();
    int menu;
    cout << "(1)挿入 (2)連続挿入 (3)削除 (4)連続削除 (5)表示 (0)終了:";
    cin >> menu;
    if(!menu){
      break;
    }
    switch(menu){
      int idx, val, n;
      case 1: scan_ins(idx, val, 0);     x.insert(i + idx, val);        break;
      case 2: n = scan_ins(idx, val, 1); x.insert(i + idx, n, val);     break;
      case 3: scan_ers(idx, 0);          x.erase(i + idx);              break;
      case 4: n = scan_ers(idx, 1);      x.erase(i + idx, i + idx + n); break
      case 5: print_vector(x); cout << '\n';
    }
  }
}
