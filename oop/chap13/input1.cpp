#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main(){
  ifstream fis("HELLO");

  if(!fis){
    cerr << "\aファイル\"HELLO\"をオープンできません。\n";
  }else{
    while(true){
      string text;
      fis >> text;
      if(!fis) break;
      cout << text << '\n';
    }
  }
}
