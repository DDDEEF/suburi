#include <iostream>
#include "Date.h"

using namespace std;

void display(const Date& day){
  string dw[] = { "日", "月", "火", "水", "木", "金", "土" };
  cout << ".日付" << day << "に関する情報\n";
  cout << " 曜日は" << dw[day.day_of_week()] << "曜日";
  cout << " 年内経過日数は" << day.day_of_year() << "日";
  cout << " その年は閏年で" << (day.leap_year() ? "ある" : "はない。") << '\n';
}

void change(Date& day){
  while(true){
    cout << "[1]年変更 [2]月変更 [3]日変更 [4]年月日変更"
         << "[5]n日進める [6]n日戻す [0]戻る:";
    int selected;
    cin >> selected;
    if(selected == 0){
      return;
    }
    int y, m, d, n;
    if(selected == 1 || selected == 4){ cout << "年:"; cin >> y; }
    if(selected == 2 || selected == 4){ cout << "月:"; cin >> m; }
    if(selected == 3 || selected == 4){ cout << "日:"; cin >> d; }
    if(selected == 5 || selected == 6){ cout << "日数:"; cin >> n; }

    switch(selected){
      case 1: day.set_year(y); break;
      case 2: day.set_month(m); break;
      case 3: day.set_day(d); break;
      case 4: day.set(y, m, d); break;
      case 5: day += n; break;
      case 6: day -= n; break;
    }
    cout << day << "に更新されました。\n";
  }
}

void inc_dec(Date& day){
  while(true){
    cout << "[1]++day [2]day++ [3]--day [4]day-- [0]戻る:";
    int selected;
    cin >> selected;
    if(selected == 0) return;
    switch(selected){
      case 1: cout << "++day = " << ++day << '\n'; break;
      case 2: cout << "day++ = " << day++ << '\n'; break;
      case 3: cout << "--day = " << --day << '\n'; break;
      case 4: cout << "day-- = " << day-- << '\n'; break;
    }
    cout << "day = " << day << '\n';
  }
}

void before_after(Date& day){
  while(true){
    cout << "[1]翌日 [2]前日 [3]n日後(day+n) [4]n日後(n+day)";
    cout << "[5]n日前 [0]戻る:";

    int selected;
    cin >> selected;
    if(selected == 0){
      return;
    }
    int n;
    if(selected >= 3 && selected <= 5){
      cout << "日数:";
      cin >> n;
    }
    cout << "それは";
    switch(selected){
      case 1: cout << day.following_day();
      case 2: cout << day.preceding_day();
      case 3: cout << day + n;
      case 4: cout << n + day;
      case 5: cout << day - n;
    }
    cout << "です。\n";
  }
}

void compare(const Date& day){
  int y, m, d;
  cout << "比較対象の日付day2を入力せよ\n";
  cout << "年:"; cin >> y;
  cout << "月:"; cin >> m;
  cout << "日:"; cin >> d;

  Date day2(y, m, d);

  cout << boolalpha;
  cout << "day = " << day << '\n';
  cout << "day2 = " << day2 << '\n';
  cout << "day - day2 = " << (day - day2) << '\n';
  cout << "day2 - day = " << (day2 - day) << '\n';
  cout << "day == day2 = " << (day == day2) << '\n';
  cout << "day != day2 = " << (day != day2) << '\n';
  cout << "day > day2 = " << (day > day2) << '\n';
  cout << "day >= day2 = " << (day >= day2) << '\n';
  cout << "day < day2 = " << (day < day2) << '\n';
  cout << "day <= day2 = " << (day <= day2) << '\n';
}

int main(){
  int y, m, d;
  cout << "日付dayを入力せよ\n";
  cout << "年:"; cin >> y;
  cout << "月:"; cin >> m;
  cout << "日:"; cin >> d;

  Date day(y, m, d);

  while(true){
    cout << "[1]情報表示 [2]日付の変更 [3]増減分演算子 [4]前後の日付"
         << "[5]比較 [0]終了:";

    int selected;
    cin >> selected;
    if(selected == 0){
      break;
    }
    switch(selected){
      case 1: display(day); break;
      case 2: change(day); break;
      case 3: inc_dec(day); break;
      case 4: before_after(day); break;
      case 5: compare(day); break;
    }
  }
}
