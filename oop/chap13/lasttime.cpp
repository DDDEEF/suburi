#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

char fname[] = "lasttime.txt";

void get_data(){
  ifstream fis(fname);

  if(fis.fail()){
    cout << "本プログラムを実行するのは初めてですね。\n";
  }else{
    int year, month, day, h, m, s;
    fis >> year >> month >> day >> h >> m >> s;
    cout << "前回は" << year << "年" << month << "月" << day << "日"
         << h << "時" << m << "分" << s << "秒でした。\n";
  }
}

void put_data(){
  ofstream fos(fname);

  if(fos.fail()){
    cout << "ファイルをオープンできません。\n";
  }else{
    time_t t = time(NULL);
    struct tm* local = localtime(&t);
    fos << local->tm_year + 1900 << ' ' << local->tm_mon + 1 << ' '
        << local->tm_mday        << ' ' << local->tm_hour    << ' '
        << local->tm_min         << ' ' << local->tm_sec     << '\n';
  }
}

int main(){
  get_data();
  put_data();
}
