#ifndef _SHOTP_H_INCLUDED_
#define _SHOTP_H_INCLUDED_

#include "Shot.h"

typedef struct _Shot{
  int x, y;
  int vx, vy;
  Shot_Status status;
} _Shot;

int Shot_Init(Shot shot, Player player);
int Shot_Done(Shot shot);

#endif
