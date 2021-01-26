#include "ShotP.h"

#include <stdlib.h>

int Shot_Init(Shot shot, Player player)
{
  shot->x = Player_GetX(player);
  shot->y = Player_GetY(player);
  shot->vx = Player_GetVX(player);
  shot->vy = Player_GetVY(player);
  shot->status = SHOT_ACTIVE;
  return (0);
}

Shot Shot_Creaet(Player player)
{
  Shot shot;

  shot = (Shot)malloc(sizeof(_Shot));
  Shot_Init(shot, player);

  return (shot);
}

Shot_Status Shot_GetStatus(Shot shot)
{
  return (shot->status);
}

void Shot_Move(Shot shot)
{
  shot->x += shot->vx;
  shot->y += shot->vy;
}

int Shot_Done(Shot shot)
{
  return (0);
}

Shot Shot_Destroy(Shot shot)
{
  Shot_Done(shot);
  free(shot);
  return (NULL);
}
