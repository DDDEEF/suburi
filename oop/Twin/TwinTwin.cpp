#include <string>
#include <iostream>
#include "Twin.h"

using namespace std;

template <>
inline std::ostream& operator<<(std::ostream& os, const Twin<std::string>& st)
{
  return os << "[\"" << st.first() << "\",\"" << st.second() << "\"]";
}

template <class Type>
bool operator<(const Twin<Type>& a, const Twin<Type>& b)
{
  if(a.first() < b.first()){
    return true;
  }else if(!(b.first() < a.first()) && a.second() < b.second()){
    return true;
  }
  return false;
}

int main(){
  Twin<Twin<int> > t1(Twin<int>(36, 57), Twin<int>(23, 48));
  cout << "t1 = " << t1 << '\n';

  Twin<Twin<string> > t2(Twin<string>("ABC", "XYZ"), Twin<string>("ABC", "ZZZ"));
  cout << "t2 = " << t2 << '\n';

  cout << "t2の値を変更します\n";
  cout << "新しい第一値の第一値:"; cin >> t2.first().first();
  cout << "新しい第一値の第二値:"; cin >> t2.first().second();
  cout << "新しい第二値の第一値:"; cin >> t2.second().first();
  cout << "新しい第二値の第二値:"; cin >> t2.second().second();

  if(!t2.ascending()){
    cout << "第一値<第二値が成立しませんのでソートします。\n";
    t2.sort();
    cout << "t2は" << t2 << "に変更されました。\n";
  }
}
