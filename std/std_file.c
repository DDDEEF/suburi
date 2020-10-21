#include <stdio.h>
#include <fcntl.h>

#define FILE_NAME "./file"

int main(int argc, char **argv){
  int FileDesc;
  int *pFileDesc = &FileDesc;
  *pFileDesc = open(FILE_NAME, O_RDWR);

  int Offset = 1024;
  int lseek_ret;
  lseek_ret = lseek64(FileDesc, Offset, SEEK_SET);

  FILE *fpp;
  int *pData;
  int Size = 1024;
  int closeSts = 0;
  int rw_ret;
  char fname[128];
  sprintf(fname, "./dump_%d_%d_%d.txt", Offset, Size, pData);

  fpp = fopen(fname, "wb");

  if(fpp != NULL){
    rw_ret = read(FileDesc, pData, Size);
    fwrite((void *)(pData), Size, 1, fpp);
    closeSts = fclose(fpp);
    if(closeSts < 0){
      printf("xxxxxFileCloseFailure!xxxxx\n");
    }else{
      printf("DumpCompleted!\n");
    }
  }else{
    printf("xxxxxFileOpenFailure!xxxxx\n");
  }
  rw_ret = Size;
  printf("rw_ret[%d]\n", rw_ret);
}
