#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

typedef struct{
  char str[512];
  long lval;
  double dval;
}SSS;

#define NUMBER (10000) //10 * 1000

int main(){
  int fd;
  long psize;
  long size;
  SSS *ptr;
  long i;

  /* マップ用ファイルオープン */
  if((fd = open("../tmp_area/mmapfile", O_RDWR)) == -1){
    perror("open");
    exit(-1);
  }

  /* ページサイズで境界合わせをおこなったサイズを計算 */
  psize = sysconf(_SC_PAGE_SIZE);
  size = (NUMBER * sizeof(SSS) / psize + 1) * psize;

  /* マップ */
  ptr = (SSS *)mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  /* テスト */
  while(1){
    /* 1000個毎にデータの表示 */
    for(i = 0; i < NUMBER; i++){
      if(i % 1000 == 0){
        printf("{%5ld:%ld,%g,%s }\n", i, ptr[i].lval, ptr[i].dval, ptr[i].str);
      }
    }
    printf("\n");
    /* 1秒待ち */
    sleep(1);
  }

  return(0);
}
