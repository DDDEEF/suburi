#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
  int qid;
  char *ptr;
  struct msqid_ds ds;
  
  struct msgbuf{
    long mtype;       /* message type must be > 0 */
    char mtext[512];  /* message data */
  }buf;

  if((qid = msgget(123, 0666|IPC_CREAT)) == -1){
    perror("msgget");
    return(-1);
  }

  if(msgctl(qid, IPC_STAT, &ds) == -1){
    perror("msgctl");
  }else{
    fprintf(stderr, "qid=%d:msg_zbytes=%lu\n", qid, ds.msg_qbytes);
  }

  while(1){
    fgets(buf.mtext, sizeof(buf.mtext), stdin);
    if((ptr = strrchr(buf.mtext, '\n')) != NULL){
      *ptr = '\0';
    }
    buf.mtype = 1L;
    if(msgsnd(qid, &buf, sizeof(buf.mtext) - sizeof(buf.mtype), 0) == -1){
      perror("msgsnd");
      break;
    }
    if(strcmp(buf.mtext, "end") == 0){
      break;
    }
  }
  return(0);
}
