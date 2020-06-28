#include <stdio.h>
#include <stdlib.h>

#define NOT_RUN 1   // 同じ値が連続していない部分を示す
#define RUN 0       // 同じ値が連続している部分を示す

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
    fprintf(stderr, "Input File cannot open");
    exit(8);
  }

  // ファイルデータをバッファに取り込む
  datasize = 0;
  while(datasize < BUFFER_SIZE && (c = fgetc(fp_i)) != EOF){
    buffer[datasize] = c;
    datasize++;
  }
  fclose(fp_i);

  // 圧縮処理する
  fp_o = fopen(av[2], "wb");
  if(fp_o == NULL){
    fprintf(stderr, "Output File cannot open\n");
    exit(8);
  }
  encodeData(fp_o, buffer, datasize);
  fclose(fp_o);
}

void getPackBits(byte *datas, int datasize, int point, int *packBitMode, int *length){
  if(point >= datasize - 1){    // 1バイトだけが残っている場合
    *packBitMode = NOT_RUN;    
    *length = 1;
    return;
  }else{
    // RUNの有無の判定
    if(datas[point] == datas[point + 1]){
      *packBitMode = RUN;
    }else{
      *packBitMode = NOT_RUN;
    }
  }
  if(*packBitMode == RUN){
    *length = 1;
    for(;;){
      if(point >= datasize - 1){
        //(*length)++;
        break;
      }
      if(datas[point] != datas[point + 1]){
        break;
      }
      (*length)++;
      point++;
    }
  }else{
    *length = 0;
    for(;;){
      if(point >= datasize - 1){
        (*length)++;
        break;
      }
      if(datas[point] == datas[point + 1]){
        break;
      }
      (*length)++;
      point++;
    }
  }
}

void outputPackBitsCode(FILE *fp, int mode, int length, byte *datas, int point){
  int i;

  if(mode == RUN){
    fputc(length, fp);
    fputc(datas[point], fp);
  }else{
    fputc(-length, fp);
    for(i = 0; i < length; i++){
      fputc(datas[point + i], fp);
    }
  }
  printf("\n");
}

/*
  PackBitsによる圧縮をして、結果をfpで指定されるファイルに出力する
*/
void encodeData(FILE *fp, byte *datas, int datasize){
  int point;
  int mode, length;

  int MAXLENGTH = 127;

  point = 0;
  while(point < datasize){
    getPackBits(datas, datasize, point, &mode, &length);
    while(length > MAXLENGTH){
      outputPackBitsCode(fp, mode, MAXLENGTH, datas, point);
      point += MAXLENGTH;
      length -= MAXLENGTH;
    }
    outputPackBitsCode(fp, mode, length, datas, point);
    point += length;
  }
}
