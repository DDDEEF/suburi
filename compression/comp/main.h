#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 102400

typedef unsigned char byte;

typedef struct{
  FILE *fp;
  byte *data;
  int size;
  char event;
}comp_t;

typedef enum{
  RUNLENGTH_STD,
  RUNLENGTH_1BYTE_SIGN,
  RUNLENGTH_HEAD1BIT_SIGN,
  WYLE_CODING,
  PACKBITS_STD,
  PACKBITS_SWITCH,
  RUNLENGTH_MEMBER_NUM,
}runlength_t;
