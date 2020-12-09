#include <iostream>
#include "Date.h"

using namespace std;

int main(){
  Date today;

  cout << "今日は" << today << "です。\n";
  cout << "昨日は" << today.preceding_day() << "です。\n";
}
