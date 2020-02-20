/*
 * マルチスレッドにおけるpthread mutexのサンプルコード
 * cc -Wall thread_mutex.c -lpthread -o thread_mutex
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <syscall.h>

//クリティカルセクションでのスリープ時間
#define SLEEP_TIMEOUT 30

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

//生成するスレッドの最大数
const int ThreadMax = 5;

void lock_mutex(void){
  int ret;

  ret = pthread_mutex_lock(&g_mutex);
  printf("pthread_mutex_lock %d\n", ret);
  if(ret != 0){
    perror("pthread_mutex_lock");
  }
}

void unlock_mutex(void){
  int ret;

  ret = pthread_mutex_unlock(&g_mutex);
  printf("pthread_mutex_unlock %d\n", ret);
  if(ret != 0){
    perror("pthread_mutex_unlock");
  }
}

void remove_mutex(void){
  int ret;

  ret = pthread_mutex_destroy(&g_mutex);
  printf("pthread_mutex_destroy %d\n", ret);
  if(ret != 0){
    perror("pthred_mutex_destroy");
  }
}

void init_mutex(void){
  int ret;

  ret = pthread_mutex_init(&g_mutex, NULL);
  printf("pthread_mutex_init %d\n", ret);
  if(ret != 0){
    perror("pthread_mutex_init");
  }
}

pid_t my_gettid(void){
  return syscall(SYS_gettid);
}

void *sub_thread(void *arg){
  int n = (int)(long)arg;

  printf("%s[%d] pid=%d tid(LWP)=%d\n", __func__, n, getpid(), my_gettid());

  lock_mutex(); //ミューテックス取得

  // ここから〜クリティカルセクション
  printf("Sleeping...");
  fflush(stdout);
  sleep(SLEEP_TIMEOUT);
  printf("Done!\n");
  // ここまで〜クリティカルセクション

  unlock_mutex(); //ミューテックス解放

  return NULL;
}

int main(void){
  int ret;
  int i;

  pthread_t th[ThreadMax];

  init_mutex(); //ミューテックス作成

  printf("Thread start!\n");
  //スレッドを生成する
  for(i = 0; i < ThreadMax; i++){
    ret = pthread_create(&th[i], NULL, sub_thread, (void *)(long)i);
    printf("TH %d=%d\n", i, ret);
  }

  printf("Thread waiting!\n");
  //スレッドの終了を待つ
  for(i = 0; i < ThreadMax; i++){
    ret = pthread_join(th[i], NULL);
    printf("TH %d=%d\n", i, ret);
  }

  printf("Thread end!\n");

  printf("Hit any key.(will remove semaphore)\n");
  getchar();
  remove_mutex(); //ミューテックス削除

  return 0;
}
