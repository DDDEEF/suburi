#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

#define NUMBER (10000)  //10 * 10000

typedef struct {
  char str[512];
  long lval;
  double dval;
}SSS;

int main(){
  int fd;
  char c;
  long psize;
  long size;
  SSS *ptr;
  long i;
  long lval;
  double dval;
  char buf[512];
  char *p;

  /* mmap用ファイルオープン */
  if((fd = open("../tmp_area/mmapfile", O_RDWR|O_CREAT, 0666)) == -1){
    perror("open");
    exit(-1);
  }

  /* ページサイズで境界合わせをおこなったサイズを計算 */
  psize = sysconf(_SC_PAGE_SIZE);
  size = (NUMBER * sizeof(SSS) / psize + 1) * psize;

  /* ファイルの必要サイズ分先にシークし、0を書き込み */
  /* (mmapfileのサイズをマップしたいサイズにするため) */
  if(lseek(fd, size, SEEK_SET) < 0){
    perror("lseek");
    exit(-1);
  }

  if(read(fd, &c, sizeof(char)) == -1){
    c = '\0';
  }
  if(write(fd, &c, sizeof(char)) == -1){
    perror("write");
    exit(-1);
  }

  /* マップ */
  ptr = (SSS *)mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if((int)ptr == -1){
    perror("mmap");
    exit(-1);
  }

  /* テスト */
  while(1){
    /* 標準入力からデータを読み込み */
    fgets(buf, sizeof(buf), stdin);

    /* 標準入力がEOF(Ctrl + D)で終了 */
    if(feof(stdin)){
      break;
    }

    /* 改行をカット */
    if((p = strchr(buf, '\n')) != NULL){
      *p = '\0';
    }
    /* 数値化 */
    lval = atoi(buf);
    dval = atof(buf);
    /* マップ先のptrポインタに全データの値(同値)をセット */
    for(i = 0; i < NUMBER; i++){
      strcpy(ptr[i].str, buf);
      ptr[i].lval = lval;
      ptr[i].dval = dval;
    }
    /* 実際にファイルに書き込みたい場合はmsyn()する */
    /* msync(ptr, size, MS_ASYNC) */
  }

  /* 実際にファイルに書き込み、同期を取る */
  msync(ptr, size, 0);

  /* アンマップ */
  if(munmap(ptr, size) == -1){
    perror("munmap");
  }

  /* ファイルクローズ */
  close(fd);

  return(0);
}
