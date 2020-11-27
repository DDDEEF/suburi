#include <iostream>

using namespace std;

int main(){
  enum animal {Dog, Cat, Monkey, Invalid};
  int type;

  do{
    cout << "0...犬 1...猫 2...猿 3...終了:";
    cin >> type;
  }while(type < Dog || type > Invalid);

  if(type != Invalid){
    animal selected = static_cast<animal>(type);
    switch(selected){
      case Dog: cout << "わんわん!!\n"; break;
      case Cat: cout << "にゃーん\n";   break;
      case Monkey: cout << "うきき\n";  break;
    }
  }
}
