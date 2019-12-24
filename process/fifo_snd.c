#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/fcntl.h>

int main(){
  int fd;
  char buf[256];

  if(mkfifo("../tmp_area/FifoTest", 0666) == -1){
    perror("mkfifo");
    /* エラーでも継続 */
  }

  if((fd = open("../tmp_area/FifoTest", O_WRONLY)) == -1){
    perror("open");
    return(-1);
  }

  while(1){
    fgets(buf, sizeof(buf) - 1, stdin);
    if(feof(stdin)){
      break;
    }
    write(fd, buf, strlen(buf));
  }

  close(fd);

  return(0);
}
