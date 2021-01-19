#include <iostream>
using namespace std;

class MyMessage{
public:
  void showMessage();
  void showMessage(const char* s);
  void showMessage(const char* s, int n);
};

void MyMessage::showMessage(){
  cout << "こんにちは。" << "\n";
}

void MyMessage::showMessage(const char* s){
  cout << s << "\n";
}

void MyMessage::showMessage(const char* s, int n){
  for(int i = 0; i < n; i++){
    cout << s << "\n";
  }
}

int main(){
  MyMessage obj;

  obj.showMessage();
  obj.showMessage("お元気ですか？");
  obj.showMessage("技術評論社", 3);

  return 0;
}
