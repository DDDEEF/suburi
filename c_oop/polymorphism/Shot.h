#ifndef _SHOT_H_INCLUDED_
#define _SHOT_H_INCLUDED_

typedef enum{
  SHOT_ACTIVE,
  SHOT_EXPLOSION,
} Shot_Status;

typedef struct _Shot* Shot;

#include "Player.h"

Shot Shot_Create(Player player);
Shot_Status Shot_GetStatus(Shot shot);
void Shot_Move(Shot shot);
Shot Shot_Destroy(Shot shot);

#endif
