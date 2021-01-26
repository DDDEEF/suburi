#include "Player.h"
#include "Shot.h"

#include <stdlib.h>

#define SHOT_NUM 3;

int main()
{
  Player player;
  Shot shot[SHOT_NUM];

  int i;
  int gameover = 1;

  player = Player_Create(10, 10, 1, -1);

  for(i = 0; i < SHOT_NUM; i++){
    shot[i] = NULL;
  }

  do{
    Player_Move(player);

    for(i = 0; i < SHOT_NUM; i++){
      if(shot[i] == NULL){
        shot[i] = Shot_Create(player);
        break;
      }
    }

    for(i = 0; i < SHOT_NUM; i++){
      if(shot[i] == NULL) continue;
      if(Shot_GetStatus(shot[i]) == SHOT_ACTIVE){
        Shot_Move(shot[i]);
      }
    }
  }while(!gameover);


  player = Player_Destory(player);

  for(i = 0; i < SHOT_NUM; i++){
    if(shot[i] != NULL){
      shot[i] = Shot_Destroy(shot[i]);
    }
  }

  exit(0);
}
