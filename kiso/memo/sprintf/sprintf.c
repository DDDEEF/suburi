#include <stdio.h>
#include <string.h>

int main(){
  FILE *fpp;
  unsigned int closeSts = 0;
  unsigned char fname[128];
  unsigned long lines;
  unsigned long size = 0;

  memset(fname, NULL, sizeof(fname));

  size = 4;

  sprintf(fname, "./test/test/file_%x_%d.dat", lines, size);

  fpp = fopen(fname, "wb");

  if(fpp != NULL){
    int hogehoge = 10;
    int *Addr;
    Addr = &hogehoge;
    fwrite((void*)(Addr), size, 1, fpp);
    closeSts = fclose(fpp);

    if(closeSts < 0){
      printf("FileCloseFailure\n");
    }else{
      printf("WriteCompleted\n");
    }
  }else{
    printf("FileOpenFaiulure\n");
  }
}
