#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 2048

int main(void){
  FILE *fp;
  char buf[MAX] = {0};
  char *ary[3];
  double data[3] = {0};

  if((fp = fopen("../tmp_area/sample.csv", "r")) != NULL){
    /* ファイルの終わりまで繰り返し読み込む */
    while(fgets(buf, MAX, fp) != NULL){
      /* 文字列(char配列)をカンマで分割する */
      ary[0] = strtok(buf, ",");
      ary[1] = strtok(NULL, ",");
      ary[2] = strtok(NULL, ",");

      /* 文字列(char配列)をdouble型に変換する */
      data[0] = atof(ary[0]);
      data[1] = atof(ary[1]);
      data[2] = atof(ary[2]);

      printf("文字->%s : %s : %s", ary[0], ary[1], ary[2]);
      printf("数値->%.2f : %.2f : %.2f\n", data[0], data[1], data[2]);
      printf("---------------------------\n");
    }
  }

  return(0);
}
