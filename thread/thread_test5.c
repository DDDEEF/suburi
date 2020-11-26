#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>

int Gint;
sem_t sem;
int count;

void *thread_func1(void *arg){
  int i;
  int x;
  int ret;

  //セマフォの値がゼロ以上になるまでスレッドを停止
  ret = sem_wait(&sem);
  printf("thread1 id[%ld]\n", pthread_self());
  for(x = 0; x < 10000000; x++){
  }

  Gint = 1000;
  printf("thread1 start Gint[%d]\n", Gint);
  for(x = 0; x < 10000; x++){
    Gint++;
    for(i = 0; i < 2000; i++){
    }
  }
  printf("thread1 end Gint[%d]\n", Gint);
  return NULL;
}

void *thread_func2(void *arg){
  int i;
  int x;
  int ret;

  printf("thread2 id[%ld]\n", pthread_self());
  for(x = 0; x <10000000; x++){
  }

  Gint = 2000;
  printf("thread2 start Gint[%d]\n", Gint);
  for(x = 0; x < 10000; x++){
    Gint++;
    for(i = 0; i < 2000; i++){
    }
  }
  printf("thread2 end Gint[%d]\n", Gint);

  //セマフォの値に1を加算
  ret = sem_post(&sem);
  return NULL;
}

int main(void){
  int i;
  int ret;
  pthread_attr_t thread1_attr;
  pthread_attr_t thread2_attr;
  struct sched_param thread1_param;
  struct sched_param thread2_param;
  pthread_t thread1;
  pthread_t thread2;

  //このプロセスだけで使用できるセマフォ
  count = 0;
  ret = sem_init(&sem, 0, count);
  //

  printf("main thread id[%ld]\n", pthread_self());
  
  pthread_attr_init(&thread1_attr);
  pthread_attr_getschedparam(&thread1_attr, &thread1_param);
  thread1_param.sched_priority = 1000;
  pthread_attr_setschedparam(&thread1_attr, &thread1_param);
  if(pthread_create(&thread1, &thread1_attr, thread_func1, NULL)){
    printf("thread1 create failure\n");
    abort();
  }

  pthread_attr_init(&thread2_attr);
  pthread_attr_getschedparam(&thread2_attr, &thread2_param);
  thread2_param.sched_priority = 1000;
  pthread_attr_setschedparam(&thread2_attr, &thread2_param);
  if(pthread_create(&thread2, &thread2_attr, thread_func2, NULL)){
    printf("thread2 create failure\n");
    abort();
  }

  if(pthread_join(thread1, NULL)){
    printf("thread1 join failure\n");
    abort();
  }

  if(pthread_join(thread2, NULL)){
    printf("thread2 join failure\n");
    abort();
  }

  exit(0);
}
