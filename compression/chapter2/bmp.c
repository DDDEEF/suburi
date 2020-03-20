#include "image.h"

typedef unsigned long   DWORD;
typedef int             BOOL;
typedef unsigned short  WORD;
typedef unsigned long   LONG;

#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L

// BMPヘッダ部のデータ構造定義
typedef struct tagBITMAPFILEHEADER{
  WORD   bfType;
  DWORD  bfSize;
  WORD   bfReserved1;
  WORD   bfReserved2;
  DWORD  bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPCOREHEADER{
  DWORD  bcSize;
  WORD   bcWidth;
  WORD   bcHeight;
  WORD   bcPlanes;
  WORD   bcBitCount;
} BITMAPCOREHEADER, *PBITMAPCOREHEADER;

typedef struct tagBITMAPINFOHEADER{
  DWORD  biSize;
  LONG   biWidth;
  LONG   biHeight;
  WORD   biPlanes;
  WORD   biBitCount;
  DWORD  biCompression;
  DWORD  biSizeImage;
  LONG   biXPelsPerMeter;
  LONG   biYPelsPerMeter;
  DWORD  biClrUsed;
  DWORD  biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
