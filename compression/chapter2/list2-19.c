#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "bmp.h"
#include "list2-16.h"

typedef unsigned char byte;

//void initCoordinateData(ImageData *image, Coordinate *coordinate);
//int getNextCoordinate(ImageData *image, Coordinate *coordinate);

int decodeImage(ImageData **image, FILE *fp_i);

int main(int ac, char *av[]){
  FILE *fp_i;
  ImageData *image;

  if(ac < 3){
    exit(8);
  }
  fp_i = fopen(av[1], "rb");
  if(fp_i == NULL){
    fprintf(stderr, "Input File cannot open\n");
    exit(8);
  }

  // 展開処理する
  if(!decodeImage(&image, fp_i)){
    fprintf(stderr, "Decode error\n");
    exit(8);
  }
  fclose(fp_i);

  // ファイルに書き出す
  writeBMPfile(av[2], image);
}

/*
  ヘッダの読込
  戻り値 0:エラー, 1:正常
*/
int readHeader(char *identifier, long *width, long *height, FILE *fp_i){
  int i;
  int c;

  // 識別子の読込(一致しなければエラー)
  for(i = 0; i < 4; i++){
    c = fgetc(fp_i);
    if(identifier[i] != c){
      return 0;
    }
  }
  if(freadDWORD(width, fp_i) == 0){
    return 0;
  }
  if(freadDWORD(height, fp_i) == 0){
    return 0;
  }
  return 1;
}

/*
  fp_iで指定されるファイルデータをランレングス符号化による圧縮結果とし、それを展開して、結果をimageに格納する
*/
int decodeImage(ImageData **image_pointer, FILE *fp_i){
  long width;
  long height;

  int i;
  int code;
  int length;

  ImageData *image;

  int x;
  int y;
  Coordinate coordinate;
  Pixel pixel;

  if(readHeader("RLE1", &width, &height, fp_i) == 0){
    return 0;
  }
  printf("%d %d\n", width, height);

  image = createImage(width, height, 24);
  *image_pointer = image;
  initCoordinateData(image, &coordinate);
  for(;;){
    length = fgetc(fp_i);
    if(length == EOF){
      break;
    }
    code = fgetc(fp_i);
    if(code == EOF){
      return 0;   //エラー
    }

    pixel.r = code;
    pixel.g = code;
    pixel.b = code;
    for(i = 0; i < length; i++){
      if(!getNextCoordinate(image, &coordinate)){
        printf("ERROR");
        return 0;
      }
      x = coordinate.x;
      y = coordinate.y;
      setPixel(image, x, y, &pixel);
      // fputc(code, fp_o);
    }
  }
  return 1;
}
