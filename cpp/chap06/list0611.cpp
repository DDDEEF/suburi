#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

bool confirm_retry(){
  int retry;
  do{
    cout << "もう一度?<Yes...1/No...0>";
    cin >> retry;
  }while(retry != 0 && retry != 1);
  return static_cast<bool>(retry);
}

int main(){
  srand(time(NULL));
  cout << "暗算トレーニング開始\n";
  do{
    int x = rand() % 900 + 100;
    int y = rand() % 900 + 100;
    int z = rand() % 900 + 100;

    while(true){
      int k;
      cout << x << " + " << y << " + " << z << " = ";
      cin >> k;
      if(k == x + y + z){
        break;
      }
      cout << "違いますよ!\n";
    }
  }while(confirm_retry());
}

