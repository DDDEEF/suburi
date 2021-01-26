#include "Shot.p"

#include <stdlib.h>

static void _Shot_Move(Shot shot);
static void _Shot_Destroy(Shot shot);

int Shot_Init(Shot shot, Player player,
              void (*move_method)(Shot shot),
              void (*destroy_method)(Shot shot))
{
  shot->x = Player_GetX(player);
  shot->y = Player_GetY(player);
  shot->vx = Player_GetVX(player);
  shot->vy = Player_GetVY(player);
  shot->status = SHOT_ACTIVE;
  shot->move_method = move_method;
  shot->destroy_method = destory_method;
  return (0);
}

Shot Shot_Create(Player player)
{
  Shot shot;

  shot = (Shot)malloc(sizeof(_Shot));
  Shot_Init(shot, player, _Shot_Move, _Shot_Destroy);

  return (shot);
}

Shot_Status Shot_GetStatus(Shot shot){ return (shot->status); }

void Shot_Move(Shot shot)
{
  (*(shot->move_method)(shot));  
}

static void _Shot_Move(Shot shot)
{
  shot->x += shot->vx;
  shot->y += shot->vy;
}

int Shot_Done(Shot shot)
{
  return (0);
}

Shot Shot_Destory(Shot shot)
{
  (*(shot->destory_method)(shot));
  return (NULL);
}

static void _Shot_Destory(Shot shot)
{
  Shot_Done(shot);
  free(shot);
}
