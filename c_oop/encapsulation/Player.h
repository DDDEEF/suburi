#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

typedef struct _Player* Player;

int Player_GetX(Player player);
int Player_GetY(Player player);
int Player_GetVX(Player player);
int Player_GetVY(Player player);

Player Player_Create(int x, int y, int vx, int vy);
void Player_Move(Player player);
Player Player_Destroy(Player player);

#endif
