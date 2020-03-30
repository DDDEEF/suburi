#include<stdio.h>
#include<stdlib.h>

#include "image.h"

typedef unsigned char byte;

void encodeImage(FILE *fp, ImageData *image);

int main(int ac, char *av[]){
  FILE *fp_o;
  ImageData *image;

  if(ac < 3){
    exit(8);
  }
  readBMPfile(av[1], &image);   // ファイルデータをバッファに取り込む
  //圧縮処理する
  fp_o = fopen(av[2], "wb");
  if(fp_o == NULL){
    fprintf(stderr, "Output File cannot open\n");
    exit(8);
  }
  encodeImage(fp_o, image);
  fclose(fp_o);
}

/* ファイルヘッダをファイルに出力する */

void writeImageHeader(char *identifier, long width, long height, FILE *fp_o){
  int i;
  for(i = 0; i < 4; i++){
    fputc(identier[i], fp_o);
  }
  fwriteDWORD(width, fp_o);
  fwriteDWORD(height, fp_o);
}

/*
  同じデータ並んでいる部分の長さを取得する
  datas中のx番目の位置を調べ、同じデータが並んでいる長さ(ラン長)をrunにデータ値をcodeに返す
  datasの大きさはdatasizeで指定する
  ラン長の最大値はlimitまでに制限する

  戻り値は次に処理対応となるデータの位置
*/
int getRunLebgth(byte *datas, int x, int datasize, int limit, int *run, int *code){
  int processingPoint; //処理中のデータの位置

  processingPoint = x;
  *run = 1;
  *code = datas[processingPoint];
  processingPoint++;
  while(processingPoint < datasize && *code == datas[processingPoint] && *run < limit){
    processingPoint++;
    (*run)++;
  }
  return processingPoint;
}

/*
  ランレングス圧縮して、結果をfpで指定されるファイルに出力する
*/
void encodeImage(FILE *fp, ImageData *image){
  int run;
  int code;
  int processingPoint;
  byte *datas;
  int datasize;

  long width;
  long height;
  int n;
  int x;
  int y;
  Coordinate coordinate;
  Pixel pixel;

  width = image->width;
  height = image->height;
  datasize = widht * height;
  datas = malloc(size(byte) * datasize);

  // 画素値をバッファに取り込む
  // 座標データの初期化
  initCoordinate(image, &coordinate, 1);
  // 処理対象画素がなくなるまでループする
  n = 0;  // バッファに格納すべき位置
  while(getNextCoordinate(image, &coordinate)){
    x = coordinate.x;
    y = coordinate.y;
    getPixel(image, x, y, &pixel);
    printf("[%d %d](%d)\n", coordinate.x, coordinate.y, pixel.r);
    datas[n] = pixel.r;
    n++;
  }

  writeImageHeader("RLE1", width, height, fp);

  processingPoint = 0;
  while(processingPoint < datasize){
    processingPoint = getRunLebgth(datas, processingPoint, datasize, 0xff, &run, &code);
    fputc(run, fp);
    fputc(code, fp);
  }
}
