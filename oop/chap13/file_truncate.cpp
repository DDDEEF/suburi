#include <string>
#include <fstream>
#include <iostream>

using namespace std;

bool file_truncate(const char* filename){
  ifstream fis(filename);
  if(fis){
    fis.close();
    ofstream fos(filename);
    return fos.is_open();
  }
  return false;
}

int main(){
  string file_name;
  cout << "中身を消したいファイルの名前:";
  cin >> file_name;

  if(file_truncate(file_name.c_str())){
    cout << "中身を消しました。\n";
  }else{
    cout << "その名前のファイルは存在しないか、消去に失敗しました。\n";
  }
}
