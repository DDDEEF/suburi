#include <vector>
#include <iostream>
#include "Shape.h"

using namespace std;

int main(){
  vector<Shape*> v;

  int count = 0;
  while(true){
    int type;
    cout << "No." << cout << "の図形の種類" << "(1...点/2...水平直線/3...垂直直線/4...長方形/0...終了) :";
    cin >> type;
    if(type == 0) break;

    Shape* s;
    switch(type){
      case 1: s = new Point(); break;
      case 2:
      case 3: {
                int len;
                cout << "長さ:"; cin >> len;
                if(type == 2){
                  s = new HorzLine(len);
                }else{
                  s = new VertLine(len);
                }
              }
              break;
      case 4: {
                int width, height;
                cout << "横幅:"; cin >> width;
                cout << "高さ:"; cin >> height;
                s = new Rectangle(width, height);
              }
              break;
    }
    v.push_back(s);
  }
  for(vector<Shape>::size_type i = 0; i < v.size(); i++){
    cout << "a[" << i << "]\n";
    v[i]->print();
    v[i]->debug();
    cout << '\n';
  }
  for(vector<Shape>::size_type i = 0; i < v.size(); i++){
    delete v[i];
  }
}
