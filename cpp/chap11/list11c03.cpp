#include <ctime>
#include <iostream>

using namespace std;

int main(){
  time_t current = time(NULL);
  struct tm* timer = localtime(&current);
  char *wday_name[] = { "日", "月", "火", "水", "木", "金", "土"};

  cout << "現在の日付・時刻は"
       << timer->tm_year + 1900 << "年"
       << timer->tm_mon + 1 << "月"
       << timer->tm_mday << "日("
       << wday_name[timer->tm_wday] << ")"
       << timer->tm_hour << "時"
       << timer->tm_min << "分"
       << timer->tm_sec << "秒です。\n";
}
