#include <iostream>

using namespace std;

namespace English{
  int x = 1;
  void print_x(){
    cout << "the value of x is " << x << ".\n";
  }
  void hello(){
    cout << "Hello\n";
  }
}

namespace Japanese{
  int x = 2;
  void print_x(){
    cout << "変数xの値は" << x << "です。\n";
  }
  void hello(){
    cout << "こんにちは\n";
  }
}

int main(){
  cout << "English::x = " << English::x << '\n';
  English::print_x();
  English::hello();

  cout << "Japanese::x = " << Japanese::x << '\n';
  Japanese::print_x();
  Japanese::hello();
}
