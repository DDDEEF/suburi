#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Player{
protected:
  char mark;
  int number;
public:
  virtual void select() = 0;
  char getMark();
  int getNumber();
  Player(char mark);
};

class User : public Player{
public:
  void select();
  User(char mark);
};

class Computer : public Player{
public:
  void select();
  Computer(char mark);
};

class Board{
private:
  char cell[3][3];
public:
  void show();
  bool setCell(Player *player);
  bool judge(Player *player);
  Board();
};

char Player::getMark(){
  return mark;
}

int Player::getNumber(){
  return number;
}

Player::Player(char mark){
  this->mark = mark;
}

void User::select(){
  int n;
  do{
    cout << mark << "の手を選んでください=";
    cin >> n;
  }while(n < 1 || n > 9);
  number = n;
}

User::User(char mark) : Player(mark){
}

void Computer::select(){
  number = rand() % 9 + 1;
  cout << mark << "の手を選んでください=" << number << "\n";
}

Computer::Computer(char mark) : Player(mark){ 
}

void Board::show(){
  cout << "\n";
  for(int v = 0; v < 3; v++){
    cout << "+-+-+-+\n";
    for(int h = 0; h < 3; h++){
      cout << "|" << cell[v][h];
    }
    cout << "|\n";
  }
  cout << "+-+-+-+\n";
}

bool Board::setCell(Player *player){
  int number = player->getNumber();
  int v = (number - 1) / 3;
  int h = (number - 1) % 3;

  if(cell[v][h] >= '1' && cell[v][h] <= '9'){
    cell[v][h] = player->getMark();
    return true;
  }else{
    cout << "そこには書き込めません。\n";
    return false;
  }
}

bool Board::judge(Player* player){
  char mark = player->getMark();
  if(cell[0][0] == mark && cell[0][1] == mark && cell[0][2] == mark ||
     cell[1][0] == mark && cell[1][1] == mark && cell[1][2] == mark ||
     cell[2][0] == mark && cell[2][1] == mark && cell[2][2] == mark ||
     cell[0][0] == mark && cell[1][0] == mark && cell[2][0] == mark ||
     cell[0][1] == mark && cell[1][1] == mark && cell[2][1] == mark ||
     cell[0][2] == mark && cell[1][2] == mark && cell[2][2] == mark ||
     cell[0][0] == mark && cell[1][1] == mark && cell[2][2] == mark ||
     cell[2][0] == mark && cell[1][1] == mark && cell[0][2] == mark )
  {
    cout << "\nゲーム終了" << mark << "の勝ちです。\n";
    return true;
  }

  bool draw = true;
  for(int v = 0; v < 3 && draw; v++){
    for(int h = 0; h < 3 && draw; h++){
      if(cell[v][h] >= '1' && cell[v][h] <= '9'){
        draw = false;
      }
    }
  }
  if(draw){
    cout << "\nゲーム終了:" << "引き分けです。\n";
    return true;
  }
  return false;
}

Board::Board(){
  for(int v = 0; v < 3; v++){
    for(int h = 0; h < 3; h++){
      cell[v][h] = (v * 3 + h + 1) + '0';
    }
  }
}

int main(){
  Player* player[2];
  User user('o');
  Computer computer('x');
  player[0] = &computer;
  player[1] = &user;
  Board board;
  int turn = 0;

  srand(time(NULL));
  while(true){
    board.show();
    do{
      player[turn]->select();
    }while(board.setCell(player[turn]) == false);

    if(board.judge(player[turn])){
      break;
    }

    if(turn == 0){
      turn = 1;
    }else{
      turn = 0;
    }
  }
  board.show();
  return 0;
}
