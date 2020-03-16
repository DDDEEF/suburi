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

  // 伸長処理する
  fp_o = fopen(av[2], "wb");
  if(fp_o == NULL){
    fprintf(stderr, "Output File cannnot open\n");
    exit(8);
  }
  decodeData(fp_i, fp_o);
  fclose(fp_i);
  fclose(fp_o);
}

/*
  fp_iで指定されるファイルデータをランレングス符号化による圧縮結果とし、
  それを伸長して、結果をfp_oで指定されるファイルに出力する
*/
int decodeData(FILE *fp_i, FILE *fp_o){
  int i;
  int code;
  int length;

  for(;;){
    length = fgetc(fp_i);
    if(length == EOF){
      break;
    }

    code = fgetc(fp_i);
    if(code == EOF){
      return 0;     //エラー
    }
    for(i = 0; i < length; i++){
      fputc(code, fp_o);
    }
  }
  return 1;
}
