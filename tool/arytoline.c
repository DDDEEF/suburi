#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  char *filepath = argv[1];
  FILE *fp;
  char ch;
  int lineCnt = 0;
  char **lines;
  char *p;
  int i;

  /* ファイルを開く */
  fp = fopen(filepath, "r");
  if(fp == NULL){
    perror("ファイルオープンエラー\n");
    return 1;
  }

  /* テキストの行数を調べる */
  while((ch = getc(fp)) != EOF){
    if(ch == '\n'){
      lineCnt++;
    }
  }

  /* ファイルの読み込み位置を元に戻す */
  rewind(fp);

  /* 行数分のポインタが必要になる */
  lines = (char **)malloc(sizeof(char *) * lineCnt);
  for(i = 0; i < lineCnt; i++){
    lines[i] = (char *)malloc(256);
  }

  /* 一行ずつ配列に読み込む */
  for(i = 0; i < lineCnt; i++){
    fgets(lines[i], 256, fp);
    p = strchr(lines[i], '\n');
    if(p){
      *p = '\0';
    }
  }

  /* 配列デバッグ用 */
  for(i = 0; i < lineCnt; i++){
    printf("lines[%d] = %s\n", i, lines[i]);
  }


  fclose(fp);
  return(0);
}
