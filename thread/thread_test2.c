#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

int Gint;

void *thread_func1(void *arg){
  int i;
  int x;

  printf("thead1 id[%ld]\n", pthread_self());

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

  printf("thread2 id[%ld]\n", pthread_self());
  
  for(x = 0; x < 10000000; x++){ 
  }

  Gint = 2000;

  printf("thread2 start Gint[%d]\n", Gint);

  for(x = 0; x < 10000; x++){
    Gint++;
    for(i = 0; i < 2000; i++){
    }
  }

  printf("thread2 end Gint[%d]\n", Gint);
  return NULL;
}

int main(void){
  int i;
  pthread_attr_t thread1_attr;
  pthread_attr_t thread2_attr;

  struct sched_param thread1_param;
  struct sched_param thread2_param;

  pthread_t thread1;
  pthread_t thread2;

  printf("メインスレッドのスレッドID = %ld\n", pthread_self());
  
  pthread_attr_init(&thread1_attr);
  pthread_attr_getschedparam(&thread1_attr, &thread1_param);
  thread1_param.sched_priority = 10000;
  pthread_attr_setschedparam(&thread1_attr, &thread1_param);
  if(pthread_create(&thread1, &thread1_attr, thread_func1, NULL)){
    printf("スレッド生成に失敗\n");
    abort();
  }

  pthread_attr_init(&thread2_attr);
  pthread_attr_getschedparam(&thread2_attr, &thread2_param);
  thread2_param.sched_priority = 0;
  pthread_attr_setschedparam(&thread2_attr, &thread2_param);
  if(pthread_create(&thread2, &thread2_attr, thread_func2, NULL)){
    printf("スレッド生成に失敗\n");
    abort();
  }

  if(pthread_join(thread1, NULL)){
    printf("スレッド1と合流に失敗\n");
    abort();
  }

  if(pthread_join(thread2, NULL)){
    printf("スレッド2と合流に失敗");
    abort();
  }

  exit(0);
}
