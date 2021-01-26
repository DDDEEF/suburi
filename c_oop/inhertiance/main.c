#include "Player.h"
#include "Shot.h"
#include "Missile.h"

#include <stdlib.h>

#define SHOT_NUM 3
#define MISSILE_NUM 3

int main(){
  Player player;
  Player enemy;
  Shot shot[SHOT_NUM];
  Missile missile[MISSILE_NUM];

  int i;
  int gameover = 1;

  player = Player_Create(10, 10, 1, -1);

  enemy = Player_Create(20, 20, -1, 0);

  for(i = 0; i < SHOT_NUM; i++){
    shot[i] = NULL;
  }

  for(i = 0; i < MISSILE_NUM; i++){
    missile[i] = NULL;
  }

  do{
    Player_Move(player);
    Player_Move(enemy);

    for(i = 0; i < SHOT_NUM; i++){
      if(shot[i] == NULL){
        shot[i] = Shot_Create(plyaer);
        break;
      }
    }

    for(i = 0; i < MISSILE_NUM; i++){
      if(missile[i] == NULL){
        missile[i] = Missile_Create(player, enemy);
        break;
      }
    }

    for(i = 0; i < SHOT_NUM; i++){
      if(shot[i] == NULL) continue;
      if(Shot_GetStatus(shot[i]) == SHOT_ACTIVE){
        Shot_Move(shot[i]);
      }
    }

    for(i = 0; i < MISSILE_NUM; i++){
      if(missile[i] == NULL) continue;
      if(Shot_GetStatus((Shot)(missile[i])) == SHOT_ACTIVE){
        Missile_Move(missile[i]);
      }
    }
  }while(!gameover);

  player = Player_Destroy(player);
  enemy = Player_Destroy(enemy);

  for(i = 0; i < SHOT_NUM; i++){
    if(shot[i] != NULL){
      shot[i] = Shot_Destroy(shot[i]);
    }
  }

  for(i = 0; i < MISSILE_NUM; i++){
    if(missile[i] != NULL){
      missile[i] = Missile_Destroy(missile[i]);
    }
  }

  exit(0);
}
