#include <iomanip>
#include <fstream>
#include <iostream>

using namespace std;

int main(){
  double pi = 3.141592653589;

  ofstream fos("pi.bin", ios_base::binary);
  if(!fos){
    cout << "ファイルをオープンできません。\n";
  }else{
    fos.write(reinterpret_cast<char*>(&pi), sizeof(double));
    fos.close();
  }

  ifstream fis("pi.bin", ios_base::binary);
  if(!fis){
    cout << "ファイルをオープンできません。\n";
  }else{
    fis.read(reinterpret_cast<char*>(&pi), sizeof(double));
    cout << "piの値は" << fixed << setprecision(20) << pi << "です。\n";
    fis.close();
  }
}
