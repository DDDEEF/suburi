#ifndef _INT_SORTER_H_
#define _INT_SORTER_H_

#ifdef __cpluscplus
extern "C" {
#endif

typedef enum {
  ERR_CAT_OK = 0,
  ERR_CAT_FILE,
  ERR_CAT_MEMORY
} IntSorterError;

typedef struct {
  const char * const pFname;
  int errorCategory;
} Context;

#ifdef __cpluscplus
}
#endif

#endif