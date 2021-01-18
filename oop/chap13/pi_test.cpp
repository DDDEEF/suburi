#include <iomanip>
#include <fstream>
#include <iostream>

using namespace std;

int main(){
  double pi = 3.141592653;

  ofstream fos("pi.txt");
  if(!fos){
    cout << "ファイルをオープンできません。\n";
  }else{
    fos << pi;
    fos.close();
  }

  ifstream fis("pi.txt");
  if(!fis){
    cout << "ファイルをオープンできません。\n";
  }else{
    fis >> pi;
    cout << "piの値は" << fixed << setprecision(20) << pi << "です。\n";
    fis.close();
  }
}
