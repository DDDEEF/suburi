#include <stdio.h>

#define FILENAME "sample.conf"  //マスターファイル
#define FILENAME_BAK "sample.conf~" //別ファイル

void read_data(int *val){
  FILE *fp;
  int n = 0;
  int ret;

  fp = fopen(FILENAME, "r");
  if(fp != NULL){
    ret = fscanf(fp, "%d", &n);
    if(ret == 1){
      printf("read data %d\n", n);
    }
    fclose(fp);
  }
  *val = n;
}

void write_data(int val){
  FILE *fp;
  int ret;

  //別ファイル名に書き込む
  fp = fopen(FILENAME_BAK, "w");
  if(fp != NULL){
    fprintf(fp, "%d", val);
    printf("write data %d\n", val);
    fclose(fp);
  }
}

int main(void){
  int num;
  int ret;

  //マスターファイルから現在の値を読み出す
  read_data(&num);
  num++;
  //別ファイルに書き込む
  write_data(num);

  //マスターファイルへりネームする
  ret = rename(FILENAME_BAK, FILENAME);
  if(ret == 0){
    printf("%s -> %s renamed.\n", FILENAME_BAK, FILENAME);
  }else{
    perror("rename failed.");
  }

  return 0;
}
