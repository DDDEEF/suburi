#ifndef _SHOTP_H_INCLUDED_
#define _SHOTP_H_INCLUDED_

#include "Shot.h"

typedef struct _Shot{
  int x, y;
  int vx, vy;
  Shot_Status status;
  void (*move_method)(struct _Shot* shot);
  void (*destroy_method)(struct _Shot* shot);
} _Shot;

int Shot_Init(Shot shot, Player playr, 
              void (*move_method)(Shot shot),
              void (*destroy_method)(Shot shot));

int Shot_Done(Shot shot);

#endif
