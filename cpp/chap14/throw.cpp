#include <new>
#include <iostream>

using namespace std;

class OverFlow { };

int f(int x){
  if(x < 0){
    throw "おかしい。値が負になっています。\n";
  }else if(x > 30000){
    throw OverFlow();
  }else{
    return 2 * x;
  }
}

int main(){
  int a;
  cout << "整数:";
  cin >> a;

  try{
    int b = f(a);
    cout << "その数の2倍は" << b << "です。\n";
  }catch(const char *str){
    cout << "例外発生:" << str;
  }catch(OverFlow){
    cout << "オーバフローしました。プログラムを終了します。\n";
    return 1;
  }
}
