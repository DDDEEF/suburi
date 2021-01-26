#include "Shot.h"

#include <stdlib.h>

typedef struct{
  int x, y;
  int vx, vy;
  Shot_Status status;
}_Shot;

Shot Shot_Create(Player player)
{
  Shot shot;

  shot = (Shot)malloc(sizeof(_Shot));
  shot->x = Player_GetX(player);
  shot->y = Player_GetY(player);
  shot->vx = Player_GetVX(player);
  shot->vy = Player_GetVY(player);
  shot->status = SHOT_ACTIVE;

  return (shot);
}

Shot_Status Shot_GetStatus(Shot shot){ return (shot->status); }

void Show_Move(Shot shot)
{
  shot->x += shot->vx;
  shot->y += shot->vy;
}

Shot Shot_Destory(Shot shot)
{
  free(shot);
  return (NULL);
}
