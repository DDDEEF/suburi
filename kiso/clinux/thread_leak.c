/*
 * マルチスレッドにおけるメモリリークのサンプルコード
 * cc -Wall thread_leak.c -lpthread -o thread_leak
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

// クリティカルセクションでのスリープ時間
#define SLEEP_TIMEOUT 3000

// 生成するスレッドの最大数
const int ThreadMax = 1;

pid_t my_gettid(void){
  return syscall(SYS_gettid);
}

void *sub_thread(void *arg){
  static int flag = 0;
  int n = (int)(long)arg;

  if(flag == 0){
    flag = 1;
    printf("%s[%d] pid=%d tid(LWP)=%d\n", __func__, n, getpid(), my_gettid());
  }

  return NULL;
}

int main(void){
  unsigned long counter = 0;
  int ret;
  int i;
  pthread_t th[ThreadMax];

  printf("Thread start!\n");

  for(;;){
    counter++;
    if(counter > 35000){
      printf("counter %lu\n", counter);
      break;
    }

    //スレッドを生成する
    for(i = 0; i < ThreadMax; i++){
      ret = pthread_create(&th[i], NULL, sub_thread, (void *)(long)i);
      if(ret != 0){
        printf("counter %lu\n", counter);
        perror("pthread_create");
        goto end;
      }
      usleep(SLEEP_TIMEOUT);
    }

    // 下記スレッド終了待ち合わせをしないと、
    // プロセスメモリリークする。
#if 0
    // スレッドの終了を待つ
    for(i = 0; i < ThreadMax; i++){
      ret = pthread_join(th[i], NULL);
      if(ret != 0){
        perror("pthread_join");
        goto end;
      }
    }
#endif
  }

end:
  printf("Hit any key.(will remove semaphore)\n");
  getchar();

  return 0;
}
