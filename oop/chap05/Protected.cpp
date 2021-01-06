#include "Super.h"
class Sub : proteched Super{
  void f(){
    //pri = 1;
    pro = 1;
    pub = 1;
  }
};

int main(){
  Sub x;

  //x.pri = 1;
  //x.pro = 1;
  //x.pub = 1;
}
