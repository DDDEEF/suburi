#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]){
  int id;
  char *adr;
  char *ptr;

  if(argc <= 1){
    fprintf(stderr, "共有メモリーIDを引数に指定すること。\n");
    return(-1);
  }
  id = atoi(argv[1]);

  if((adr = shmat(id ,NULL, 0)) == (char *)-1){
    perror("shmat");
  }else{
    while(1){
      fgets(adr, 512, stdin);
      if((ptr = strrchr(adr, '\n')) != NULL){
        *ptr = '\0';
      }
      if(strcmp(adr, "end") == 0){
        break;
      }
    }
    if(shmdt(adr) == -1){
      perror("shmat");
    }
  }
  return(0);
}
