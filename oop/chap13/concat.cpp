#include <fstream>
#include <iostream>

using namespace std;

void copy(istream& src, ostream& dst){
  char ch;
  src >> noskipws;
  while(src >> ch){
    dst << ch;
  }
}

int main(int argc, char** argv){
  ifstream is;
  if(argc < 2){
    copy(cin, cout);
  }else{
    while(--argc > 0){
      ifstream fs(*++argv);
      if(!fs){
        cerr << "ファイル" << *argv << "をオープンできません。\n";
      }else{
        copy(fs, cout);
      }
    }
  }
}
