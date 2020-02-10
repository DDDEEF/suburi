#include <stdio.h>
#include <errno.h>

#define FILENAME_BAK "/sample.conf"
#define FILENAME "/dev/shm/sample.conf"

int main(void){
  int ret;

  //マスターファイルへリネームする
  ret = rename(FILENAME_BAK, FILENAME);
  if(ret == 0){
    printf("%s -> %s renamed.\n", FILENAME_BAK, FILENAME);
  }else{
    printf("errno %d\n", errno);
    perror("rename failed.");
  }

  return 0;
}
