#include <iostream>

using namespace std;

int main(){
  int hand;

  cout << "手を選んでください。(0:ぐー、1:ちょき、2:ぱー):";
  cin >> hand;

  switch(hand){
    case 0: cout << "グー\n"; break;
    case 1: cout << "チョキ\n"; break;
    case 2: cout << "パー\n"; break;
  }
}
