#include <iostream>

using namespace std;

int main(){
  int n;
  cout << "何個*を表示しますか？";
  cin >> n;

  if(n > 0){
    for(int i = 0; i < n; i++){
      cout << '*';
    }
    cout << '\n';
  }
}
