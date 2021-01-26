#include "Player.h"

#include <stdlib.h>

typedef struct _Player{
  int x, y;
  int vx, vy;
}_Player;

int Player_GetX(Player player) { return (player->x); }
int Player_GetY(Player player) { return (player->y); }
int Player_GetVX(Player player) { return (player->vx); }
int Player_GetVY(Player player) { return (player->vy); }

Player Player_Create(int x, int y, int vx, int vy)
{
  Player player;

  player = (Player)malloc(sizeof(_Player));
  player->x = x;
  player->y = y;
  player->vx = vx;
  player->vy = vy;

  return (player);
}

void Player_Move(Player player)
{
  player->x += player->vx;
  player->y += player->vy;
}

Player Player_Destroy(Player player)
{
  free(player);
  return (NULL);
}

