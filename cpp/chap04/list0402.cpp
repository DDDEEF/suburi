#include <climits>
#include <iostream>

using namespace std;

int main(){
  cout << "この処理系の単なる文字型は"
       << (CHAR_MIN ? "符号付き" : "符号無し") << "文字型です。\n";
}
