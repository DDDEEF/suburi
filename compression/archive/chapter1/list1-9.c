#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

int decodeData(FILE *fp_i, FILE *fp_o);

int main(int ac, char *av[]){
  FILE *fp_i, *fp_o;

  if(ac < 3){
    exit(8);
  }
  fp_i = fopen(av[1], "rb");
  if(fp_i == NULL){
    fprintf(stderr, "Input File cannot open\n");
    exit(8);
  }

  //伸張処理する
  fp_o = fopen(av[2], "wb");
  if(fp_i == NULL){
    fprintf(stderr, "Output File cannnot open\n");
    exit(8);
  }
  decodeData(fp_i, fp_o);
  fclose(fp_i);
  fclose(fp_o);
}

/*
  fp_iで指定されるファイルデータをランレングス符号化による圧縮結果とし、
  それを伸張して、結果をfp_oで指定されるファイルに出力する
  runlengthFlagは、ランレングス符号として出力されていることを示すフラグの値
*/
int decodeData(FILE *fp_i, FILE *fp_o){
  int i;
  int length, code;
  int value;

  for(;;){
    value = fgetc(fp_i);
    if(value == EOF){
      break;
    }

    if(value >= 0x80){
      length = value&0x7f;
      code = fgetc(fp_i);
      if(code == EOF){
        return 0;   // エラー
      }
      for(i = 0; i < length; i++){
        fputc(code, fp_o);
      }
    }else{
      // ランレングス以外の部分は、値をそのまま出力
      fputc(value, fp_o);
    }
  }
  return 1;
}
