#ifndef BMP_H
#define BMP_H

#include <stdlib.h>

typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef unsigned long   LONG;
typedef int             BOOL;

extern int fwriteWORD(WORD, FILE *);
extern int fwriteDWORD(DWORD, FILE *);
extern int freadWORD(WORD *, FILE *);
extern int freadDWORD(DWORD *, FILE *);
extern int countOfDIBColorEntries(int);
extern int getDIBxmax(int, int);
extern int readBMPfile(char *, ImageData **);
extern int writeBMPfile(char *, ImageData *);

#endif /* BMP_H */
