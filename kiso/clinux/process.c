/*
 * マルチプロセスにおけるセマフォのサンプルコード
 * *プロセス終了時、掴んでいたセマフォを自動解放する。
 * cc -Wall process.c -o process
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// ファイルはプログラム実行前にあらかじめ作っておくこと
// $ touch ../../tmp_area/mysema.dat
#define SEMA_KEYFILE "../../tmp_area/mysema.dat"
#define SEMA_KEYID 'Y'

// プロセス終了時、掴んでいたセマフォを自動解放する。
#define SEMA_FLAG SEM_UNDO
// プロセス終了時、掴んでいたセマフォを自動解放しない。
// #define SEMA_FLAG 0

// クリティカルセクションでのスリープ時間
#define SLEEP_TIMEOUT 30

// SEMCTL(2) manページより引用
union semun{
  int val;                /* Value for SETVAL */
  struct semid_ds *buf;   /* Buffer for IPC_STAT, IPC_SET */
  unsigned short *array;  /* Array for GETALL, SETALL */
  struct seminfo *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

int g_semaid = -1;

void lock_sema(void){
  struct sembuf sb;
  int ret;

  sb.sem_num = 0;
  sb.sem_op = -1;   // P操作
  sb.sem_flg = SEMA_FLAG;  //プロセス終了時破棄の有無
  ret = semop(g_semaid, &sb, 1);
  if(ret == -1){
    perror("semop error");
    exit(1);
  }
  printf("Locked sema\n");
}

void unlock_sema(void){
  struct sembuf sb;
  int ret;

  sb.sem_num = 0;
  sb.sem_op = 1;  // V操作
  sb.sem_flg = SEMA_FLAG; //プロセス終了時破棄の有無
  ret = semop(g_semaid, &sb, 1);
  if(ret == -1){
    perror("semop error");
    exit(1);
  }
  printf("unlocked sema\n");
}

void remove_sema(void){
  int ret;
  union semun arg;

  memset(&arg, 0, sizeof(arg));
  arg.val = 1;
  ret = semctl(g_semaid, 0, IPC_RMID, arg);
  if(ret == -1){
    perror("Failed to remove");
  }else{
    printf("Removed semaphore %d(%d)\n", g_semaid, ret);
  }
}

void init_sema(void){
  key_t key;
  int id;
  int ret;
  union semun arg;

  key = ftok(SEMA_KEYFILE, SEMA_KEYID);
  if(key == -1){
    printf("[%s]\n", SEMA_KEYFILE);
    perror("ftok error");
    exit(1);
  }
  id = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL );
  if(id == -1){
    if(errno == EEXIST){
      //すでにセマフォが作成済み
      id = semget(key, 1, 0);
      if(id == -1){
        perror("semget error");
        exit(1);
      }
      g_semaid = id;
      printf("Already created semaphore %d\n", g_semaid);
      return ;
    }
    perror("semget error");
    exit(1);
  }
  g_semaid = id;
  printf("Created semaphore semid = %d key = 0x%x\n", g_semaid, key);
  memset(&arg, 0, sizeof(arg));
  arg.val = 1;
  ret = semctl(id, 0, SETVAL, arg);
  if(ret == -1){
    perror("semctl error");
    // セマフォを忘れずに削除しておく
    remove_sema();
    exit(1);
  }
}

int main(void){
  init_sema();  //セマフォ作成
  lock_sema();  //セマフォ取得

  //ここから〜クリティカルセクション
  printf("Sleeping...");
  fflush(stdout);
  sleep(SLEEP_TIMEOUT);
  printf("Done!\n");
  //ここまで〜クリティカルセクション

  unlock_sema();    //セマフォ解放

  printf("Hit any key.(will remove semaphore)\n");
  getchar();
  remove_sema();    //セマフォ削除

  return 0;
}
