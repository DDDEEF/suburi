#include <new>
#include <iostream>
#include "Twin.h"
#include "Array.h"

using namespace std;

int main(){
  Array<Twin<int> > x(3);
  Array<Twin<int> > y = x;
  y[1] = Twin<int>(4, 5);
  Array<Twin<int> > z(2);
  z = y;

  cout << "---- x ----\n";
  for(int i = 0; i < x.size(); i++){
    cout << "x[" << i << "] = " << x[i] << '\n';
  }

  cout << "---- y ----\n";
  for(int i = 0; i < y.size(); i++){
    cout << "y[" << i << "] = " << y[i] << '\n';
  }

  cout << "---- z ----\n";
  for(int i = 0; i < z.size(); i++){
    cout << "z[" << i << "] = " << z[i] << '\n';
  }
}
