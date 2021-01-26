#ifndef _MISSILE_H_INCLUDED_
#define _MISSILE_H_INCLUDED_

#include "Player.h"

typedef struct _Missile* Missile;

Missile Missile_Create(Player player, Player, target);
void Missile_Move(Missile missile);
Missile Missile_Destroy(Missile missile);

#endif
