#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/*
 セマフォセットをゲットするsem_get()内のsemctlで使用する共有体
union semun {
  int             val;     SETVALの値
  struct semid_ds *buf;    IPC_STAT, IPC_SET用のバッファ
  unsigned short  *array;  GETALL, SETALL用の配列
  struct seminfo  *__buf;  IPC_INFO用のバッファ(Linux固有)
};
*/

int sem_lock(int sid){
  struct sembuf sb;

  sb.sem_num = 0;
  sb.sem_op = -1;
  sb.sem_flg = SEM_UNDO;
  if(semop(sid, &sb, 1) == -1){
    perror("semop");
    return(-1);
  }
  return(1);
}

int sem_unlock(int sid){
  struct sembuf sb;
  int val;

  /* セマフォの状態取得 */
  val = semctl(sid, 0, GETVAL);

  if(val > 0){
    fprintf(stderr, "already unlocked\n");
    return(0);
  }

  sb.sem_num = 0;
  sb.sem_op = 1;
  sb.sem_flg = SEM_UNDO;
  if(semop(sid, &sb, 1) == -1){
    perror("semop");
    return(-1);
  }
  return(1);
}

int sem_get(char *path){
  int sid;
  int val;
  union semun arg;

  /* セマフォセットの獲得 */
  if((sid = semget(ftok(path, 0), 1, 0666|IPC_CREAT|IPC_EXCL)) >= 0){
    /* 新規に作成した:初期化する */
    fprintf(stderr, "sem_get:new create\n");
    arg.val = 1;
    if(semctl(sid, 0, SETVAL, arg) == -1){
      perror("semctl");
      return(-1);
    }
    sem_unlock(sid);
  }else if(errno == EEXIST){
    /* 既に存在しているものを獲得 */
    fprintf(stderr, "sem_get:already created\n");
    sid = semget(ftok(path, 0), 1, 0666);
    val = semctl(sid, 0, GETVAL);
    fprintf(stderr, "val = %d\n", val);
  }else{
    perror("semget");
    return(-1);
  }
  return(sid);
}

int main(){
  int sid;
  int ret;
  char buf[128];

  setbuf(stdout, NULL);

  /* セマフォセットの獲得 */
  if((sid = sem_get("../tmp_area/semaphoreSharedFile")) == -1){
    return(-1);
  }
  printf("sid = %d\n", sid);

  /* ロック */
  printf("Try lock\n");
  ret = sem_lock(sid);
  printf("sem_lock() = %d\n", ret);

  printf("Enter to unlock\n");
  fgets(buf, sizeof(buf) - 1, stdin);

  /* アンロック */
  ret = sem_unlock(sid);
  printf("sem_unlock() = %d\n", ret);

  return(0);
}
