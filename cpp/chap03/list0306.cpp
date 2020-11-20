#include <iostream>

using namespace std;

int main(){
  int n;
  cout << "何個表示しますか:";
  cin >> n;

  if(n > 0){
    int i = 0;
    while(i < n){
      cout << '*';
      i++;
    }
    cout << '\n';
  }
}
