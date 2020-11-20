#include <iostream>

using namespace std;

int main(){
  int hand;

  do{
    cout << "手を選んでください。(0...ぐー/1...ちょき/2...ぱー):";
    cin >> hand;
  }while(hand < 0 || hand > 2);

  switch(hand){
    case 0: cout << "ぐー\n";   break;
    case 1: cout << "ちょき\n"; break;
    case 2: cout << "ぱー\n"; break;
  }
}
