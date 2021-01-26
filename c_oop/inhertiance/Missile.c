#include "Missile.h"

#include <stdlib.h>
#include "ShotP.h"

typedef struct _Missile{
  _Shot shot; /* shotクラスを継承するので、このメンバは先頭に置くこと */
  int quick;
  Player target;
} _Missile;

static int sign(int x)
{
  if(x > 0) return (1);
  if(x < 0) return (-1);
  return (0);
}

Missile Missile_Create(Player player, Player target)
{
  Missile missile;

  missile = (Missile)malloc(sizeof(_Missile));
  Shot_Init((Shot)missile, player);
  missile->quick = 1;
  missile->target = target;

  return (missile);
}

void Missile_Move(Missile missile)
{
  int ax, ay;
  ax = sign(Player_GetX(missile->target) - ((Shot)missile)->x);
  ay = sign(Player_GetY(missile->target) - ((Shot)missile)->y);
  ax *= missile->quick;
  ay *= missile->quick;
  ((Shot)missile)->vx += ax;
  ((Shot)missile)->vy += ay;
  ((Shot)missile)->x += ((Shot)missile)->vx;
  ((Shot)missile)->y += ((Shot)missile)->vy;
}

Missile Missile_Destroy(Missile missile)
{
  Shot_Done((Shot)missile);
  free(missile);
  return (NULL);
}



