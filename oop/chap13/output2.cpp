#include <fstream>
#include <iostream>

using namespace std;

int main(){
  ofstream fos("HELLO", ios_base::app);
  if(!fos){
    cerr << "\aファイル\"HELLO\"をオープンできません。\n";
  }else{
    fos << "Fine, thanks.\n";
    fos << "And you?\n";
  }
}
