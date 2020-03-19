#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 102400

typedef unsigned char byte;

void encodeData(FILE *fp, byte *datas, int datasize);

int main(int ac, char *av[]){
  FILE *fp_i, *fp_o;
  int datasize, c;
  unsigned char buffer[BUFFER_SIZE];

  if(ac < 3){
    exit(8);
  }

  fp_i = fopen(av[1], "rb");
  if(fp_i == NULL){
    fprintf(stderr, "Input File cannot open\n");
    exit(8);
  }

  //ファイルデータをバッファに取り込む
  datasize = 0;
  while(datasize < BUFFER_SIZE && (c = fgetc(fp_i)) != EOF){
    buffer[datasize] = c;
    datasize++;
  }
  fclose(fp_i);

  //圧縮処理する
  fp_o = fopen(av[2], "wb");
  if(fp_o == NULL){
    fprintf(stderr, "Output File cannot open\n");
    exit(8);
  }

  encodeData(fp_o, buffer, datasize);
  fclose(fp_o);
}

/*
  同じデータが並んでいる部分の長さを取得する
  datas中のx番目の位置を調べ、同じデータ値が並んでいる長さ(ラン長)をrunに、
  データ値をcodeに返す
  datasの大きさはdatasizeで指定する
  ラン長の最大値はlimitまでに制限する
  
  戻り値は、次に処理対象となるデータの位置
*/
int getRunLebgth(byte *datas, int x, int datasize, int limit, int *run, int *code){
  int processingPoint;    //処理中のデータ位置

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
void encodeData(FILE *fp, byte *datas, int datasize){
  int run, code;
  int processingPoint;

  processingPoint = 0;
  while(processingPoint < datasize){
    processingPoint = getRunLebgth(datas, processingPoint, datasize, 0xff, &run, &code);
    fputc(run, fp);
    fputc(code, fp);
  }
}
