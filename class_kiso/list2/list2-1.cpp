#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GU 0
#define CHOKI 1
#define PA 2

#define WIN 0
#define LOSE 1
#define DRAW 2

int getUserHand();
int getComputerHand();
int doJudge(int user, int computer);
void showJudge(int judge);

int main(){
  int user, computer, judge; 
  srand(time(NULL));
  user = getUserHand();
  computer = getComputerHand();
  judge = doJudge(user, computer);
  showJudge(judge);
  return 0;
}

int getUserHand(){
  int hand;
  printf("0:グー, 1:チョキ, 2:パー\n");
  printf("ユーザーの手=");

  do{
    scanf("%d", &hand);
  }while(!(0 <= hand && hand < 3));
  return hand;
}

int getComputerHand(){
  int hand;

  hand = rand() % 3;
  printf("コンピュータの手=%d\n", hand);

  return hand;
}

int doJudge(int user, int computer){
  int judge;

  if(user == computer){
    judge = DRAW;
  }else if(user == GU && computer == CHOKI || user == CHOKI && computer == PA || user == PA && computer == GU ){
    judge = WIN;
  }else{
    judge = LOSE;
  }
  return judge;
}

void showJudge(int judge){
  if(judge == WIN){
    printf("ユーザーの勝ちです。\n");
  }else if(judge == LOSE){
    printf("コンピュータの勝ちです。\n");
  }else if(judge == DRAW){
    printf("あいこです。\n");
  }
}
