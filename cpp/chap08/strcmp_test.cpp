#include <cstring>
#include <iostream>

using namespace std;

int main(){
  char st[128];

  cout << "\"ABCDE\"との比較を行います。\n";
  cout << "\"XXXXX\"で終了します。\n";

  while(1){
    cout << "\n文字列st:";
    cin >> st;

    if(strcmp(st, "XXXXX") == 0){
      break;
    }

    cout << "strcmp(\"ABCDEF\", st) = " << strcmp("ABCDE", st) << '\n';
    cout << "strncmp(\"ABCDE\", st, 3) = " << strncmp("ABCDE", st, 3) << '\n';
  }
}
