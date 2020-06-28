#include <stdio.h>
#include <stdlib.h>

#define NOT_RUN 1   // 同じ値が連続していない部分を示す
#define RUN 0       // 同じ値が連続している部分を示す

typedef unsigned char byte;

int decodeData(FILE *fp_i, FILE *fp_o);

int main(int ac, char *av[]){
    FILE *fp_i, *fp_o;

    if(ac < 3){
      exit(8);
    }
    fp_i = fopen(av[1], "rb");
    if(fp_i == NULL){
      fprintf(stderr, "Output File cannot open\n");
      exit(8);
    }

    //伸張処理する
    fp_o = fopen(av[2], "wb");
    if(fp_o == NULL){
      fprintf(stderr, "Output File cannot open\n");
      exit(8);
    }
    decodeData(fp_i, fp_o);
    fclose(fp_i);
    fclose(fp_o);
}

/*
  fp_iで指定されるファイルデータをPackBitsによる圧縮結果とし、
  それを展開して結果をfp_oで指定されるファイルに出力する
*/
int decodeData(FILE *fp_i, FILE *fp_o){
  int i;
  int code;
  int packBitsMode, length;

  packBitsMode = 0;
  while((length = fgetc(fp_i)) != EOF){
    if(length > 0){
      if(packBitsMode == NOT_RUN){
        for(i = 0; i < length; i++){
          code = fgetc(fp_i);
          if(code == EOF){
            return 0;     //エラー
          }
          fputc(code, fp_o);
        }
      }else{
        code = fgetc(fp_i);
        if(code == EOF){
          return 0;       //エラー
        }
        for(i = 0; i < length; i++){
          fputc(code, fp_o);
        }
      }
    }
    //モードの切り替え
    packBitsMode = 1 - packBitsMode;
  }
  return 1;
}
