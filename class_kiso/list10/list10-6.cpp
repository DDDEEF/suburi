#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Hand{
public:
  virtual void judge(Hand *h) = 0;
  virtual void vsGu() = 0;
  virtual void vsChoki() = 0;
  virtual void vsPa() = 0;
};

class Gu : public Hand{
public:
  void judge(Hand *h);
  void vsGu();
  void vsChoki();
  void vsPa();
};

void Gu::judge(Hand *h){
  h->vsGu();
}

void Gu::vsGu(){
  cout << "あいこです。\n";
}

void Gu::vsChoki(){
  cout << "グーの勝ちです。\n";
}

void Gu::vsPa(){
  cout << "グーの負けです。\n";
}

class Choki : public Hand{
public:
  void judge(Hand *h);
  void vsGu();
  void vsChoki();
  void vsPa();
};

void Choki::judge(Hand *h){
  h->vsChoki();
}

void Choki::vsGu(){
  cout << "チョキの負けです。\n";
}

void Choki::vsChoki(){
  cout << "あいこです。\n";
}

void Choki::vsPa(){
  cout << "チョキの勝ちです。\n";
}

class Pa : public Hand{
public:
  void judge(Hand *h);
  void vsGu();
  void vsChoki();
  void vsPa();
};

void Pa::judge(Hand *h){
  h->vsPa();
}

void Pa::vsGu(){
  cout << "パーの勝ちです。\n";
}

void Pa::vsChoki(){
  cout << "パーの負けです。\n";
}

void Pa::vsPa(){
  cout << "あいこです。\n";
}

int main(){
  Gu g;
  Choki c;
  Pa p;

  cout << "グー vs チョキ...\n";
  c.judge(&g);

  cout << "グー vs パー...\n";
  p.judge(&g);

  cout << "グー vs グー...\n";
  g.judge(&g);

  return 0;
}
