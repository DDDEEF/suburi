#include <iostream>

using namespace std;

extern int max_no;

static void prompt(){
  cout << "0 ~" << max_no << "の数:";
}

int input(){
  int val;
  do{
    prompt();
    cin >> val;
  }while(val < 0 || val > max_no);
  return val;
}

bool confirm_retry(){
  int cont;
  cout << "もう一度しますか？\n" << "<Yes...1/No...0>:";
  cin >> cont;
  return static_cast<bool>(cont);
}
