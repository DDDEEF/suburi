#ifndef __Class_Counter
#define __Class_Counter

#include <climits>

class Counter{
  unsigned cnt;

public:
  Counter() : cnt(0){}

  void increment(){
    if(cnt < UINT_MAX) cnt++;
  }

  void decrement(){
    if(cnt > 0) cnt--;
  }

  unsigned value(){
    return cnt;
  }
};

#endif
