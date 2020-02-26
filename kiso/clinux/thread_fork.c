/*
 * マルチスレッドとforkのサンプルコード
 * cc -Wall thread_fork.c -lpthread -o thread_fork
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <pthread.h>
#include <syscall.h>

// ファイル
#define FILENAME "/myfile.dat"

// 生成するスレッドの最大数
const int ThreadMax = 2;

// ファイルオープン情報
volatile int g_file_opened = 0;
volatile int g_forked = 0;

pid_t my_gettid(void){
  return syscall(SYS_gettid);
}

void *sub_thread2(void *arg){
  int n = (int)(long)arg;
  pid_t pid;

  printf("(2)%s[%d] pid=%d tid(LWP)=%d\n", __func__, n, getpid(), my_gettid());
  printf("(2)Waiting fileopening...\n");
  while(g_file_opened == 0){
    sleep(1);
  }
  printf("(2)fileopened!\n");

  pid = fork();
  if(pid < 0){
    perror("fork");
    goto end;
  }

  if(pid == 0){ // 子プロセス
    printf("(2)Child pid = %d ppid=%d tid=%d\n", getpid(), getppid(), my_gettid());

    sleep(30);

    _exit(0);
  }else{        // 親プロセス
    g_forked = 1;

    printf("(2)Parent pid=%d ppid=%d tid=%d\n", getpid(), getppid(), my_gettied());

    waitpid(pid, NULL, 0);

    printf("(2)Child process terminated.\n");
  }
end:
  return NULL;
}

void *sub_thread1(void *arg){
  int n = (int)(long)arg;
  FILE *fp;

  printf("(1)%s[%d] pid=%d tid(LWP)=%d\n", __func__, n, getpid(), my_gettid());

  fp = fopen(FILENAME, "w");
  if(fp == NULL){
    perror("fopen");
    goto end;
  }
  g_file_opened = 1;
  printf("(1)%s was opened\n", FILENAME);

  printf("(1)Waiting forking...\n");
  while(g_forked == 0){
    sleep(1);
  }
  printf("(1)forked!\n");

  sleep(10);

  fclose(fp);
  g_file_opened = 0;
  printf("(1)%s was closed\n", FILENAME);

end:
  return NULL;
}

int main(void){
  int ret;
  int i;
  pthread_t th[ThreadMax];

  // スレッドを生成する
  ret = pthread_create(&th[0], NULL, sub_thread1, (void*)(long)0);
  if(ret != 0){
    perror("pthread_create");
    goto end;
  }
  ret = pthread_create(&th[1], NULL, sub_thread2, (void*)(long)1);
  if(ret != 0){
    perror("pthread_create");
    goto end;
  }

  // 下記スレッド終了待ち合わせをしないと
  // プロセスメモリリークする
  // スレッドの終了を待つ
  for(i = 0; i < ThreadMax; i++){
    ret = pthread_join(th[i], NULL);
    if(ret != 0){
      perror("pthread_join");
      goto end;
    }
  }

end:
  printf("Hit any key.(will be terminated)\n");
  getchar();

  return 0;
}
