#include <stdio.h>

#define FILENAME "sample.conf"

void read_data(int *val){
  FILE *fp;
  int n = 0;
  int ret;

  fp = fopen(FILENAME, "r");
  if(fp != NULL){
    ret = fscanf(fp, "%d", &n);
    if(ret == 1){ //読み込み成功
      printf("read data %d\n", n);
    }
    fclose(fp);
  }
  *val = n;
}

void write_data(int val){
  FILE *fp;
  int ret;

  fp = fopen(FILENAME, "w");
  if(fp != NULL){
    fprintf(fp, "%d", val);
    printf("write data %d\n", val);
    fclose(fp);
  }
}

int main(void){
  int num;
  read_data(&num);
  num++;
  write_data(num);

  return 0;
}
