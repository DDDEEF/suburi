#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/fcntl.h>

int main(){
  int fd;
  int len;
  char buf[256];

  if((fd = open("../tmp_area/FifoTest", O_RDONLY)) == -1){
    perror("open");
    return(-1);
  }

  while(1){
    len = read(fd, buf, sizeof(buf) - 1);
    if(len == 0){
      break;
    }
    buf[len] = '\0';
    fputs(buf, stdout);
  }

  close(fd);
  
  unlink("../tmp_area/FifoTest");

  return(0);
}
