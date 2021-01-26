#include "Player.h"

#include "Shot.h"
#include "Missile.h"

#include <stdlib.h>

typedef struct shotlist{
  Shot shot;
  struct shotlist* next;
}shotlist;

void list_add(shotlist** list_head, Shot shot)
{
  shotlist* list;
  list = (shotlist*)malloc(sizeof(shotlist));
  list->shot = shot;
  list->next = *list_head;
  *list_head = list;
}

int main()
{
  Player player;
  Player enemy;
  Shot shot;
  Missile missile;

  shotlist* list_head = NULL;
  shotlist* p;
  shotlist* pp;
  int gemeover = 1;

  player = Player_Create(10, 10, 1, -1);
  enemy = Player_Create(20, 20, -1, 0);

  do{
    Player_Move(player);
    Player_Move(enemy);

    shot = Shot_Create(player);
    list_add(&list_head, shot);

    missile = Missile_Create(player, enemy);
    list_add(&list_head, (Shot)missile);

    for(p = list_head; p != NULL; p = p->next){
      if(Shot_GetStatus(p->shot) == SHOT_ACTIVE){
        Shot_Move(p->shot);
      }
    }
  }while(!gameover);

  player = Player_Destroy(player);
  enemy = Player_Destroy(enemy);

  for(p = list_head; p != NULL; p = pp){
    p->shot = Shot_Destroy(p->shot);
    pp = p->next;
    free(p);
  }

  exit (0);
}
