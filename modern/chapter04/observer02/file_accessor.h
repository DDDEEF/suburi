#ifndef _FILE_ACCESSOR_H_
#define _FILE_ACCESSOR_H_

#include <stdbool.h>
#include <stdio.h>

#include "buffer.h"
#include "array_list.h"

#ifdef __cplusplus
extern "C" {
#endif

struct FileAccessorContext;

typedef struct FileErrorObserver{
  void (*const onError)(struct FileErrorObserver *pThis, struct FileAccessorContext *pFileCtx);
} FileErrorObserver;

extern FileErrorObserver defalut_file_error_observer;

typedef struct FileAccessorContext{
  FILE *fp;
  const char *pFname;
  const char *pMode;
  ArrayList oberver_table;
  bool (*const processor)(struct FileAccessorContext *pThis);
} FileAccessorContext;

bool acess_file(FileAccessorContext *pThis);
FILE *get_file_pointer(FileAccessorContext *pThis);
long file_size(FileAccessorContext *pThis);
long file_current_pos(FileAccessorContext *pThis);
int set_file_pos(FileAccessorContext *pThis, long offset, int whence);
bool read_file(FileAccessorContext *pThis, BufferContext *pBufCtx);
bool write_file(FileAccessorContext *pThis, BufferContext *pBufCtx);
void add_file_error_observer(FileAccessorContext *pThis, FileErrorObserver *pErrorObserver);
void remove_file_error_observer(FileAccessorContext *pThis, FileErrorObserver *pErrorObserver);

#ifdef __cplusplus
}
#endif

#endif