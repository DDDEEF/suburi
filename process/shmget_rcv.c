#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

int EndFlag = 0;

void sigHandler(int sig){
  EndFlag = sig;
}

int main(){
  int id;
  char *adr;

  signal(SIGINT, sigHandler);
  signal(SIGTERM, sigHandler);
  signal(SIGQUIT, sigHandler);

  if((id = shmget(IPC_PRIVATE, 512, IPC_CREAT|0666)) == -1){
      perror("shmget");
      return(-1);
  }
  printf("共有メモリーID = %d\n", id);

  if((adr = shmat(id, NULL, 0)) == (char *)-1){
    perror("shmat");
  }else{
    strcpy(adr, "Initial");
    while(1){
      printf("%s\n", adr);
      if(strcmp(adr, "end") == 0){
        break;
      }
      if(EndFlag != 0){
        fprintf(stderr, "EndFlag = %d\n", EndFlag);
        break;
      }
      sleep(3);
    }
    if(shmdt(adr) == -1){
      perror("shmdt");
    }
  }
  if(shmctl(id, IPC_RMID, 0) == -1){
    perror("shmctl");
  }

  return(0);
}
