#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(){
  srand(time(NULL));

  int no = rand() % 100;
  int x;

  cout << "数当てゲーム開始!!\n";
  cout << "0~99の数を当ててください。\n";

  do{
    cout << "いくつかな:";
    cin >> x;

    if(x > no)
      cout << "もっと小さな数だよ\n";
    else if(x < no)
      cout << "もっと大きな数だよ\n";
  }while(x != no);

  cout << "正解です。\n";
}
