/*
 * シグナルのサンプルコード
 */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define MY_SIGNAL SIGUSR1

volatile int g_count = 0;

void sample_signal_handler(int num){
  write(1, "IEEE\n", 5);
  g_count = -1;
}

int main(void){
  int i;
  int ret;
  int unmasked;
  struct sigaction sig;
  sigset_t setmask;
  sigset_t oldsetmask;

  //シグナルマスクの初期化
  sigemptyset(&setmask);
  sigaddset(&setmask, MY_SIGNAL);

  //シグナルハンドラの登録
  memset(&sig, 0, sizeof(sig));
  sig.sa_handler = sample_signal_handler;
  sig.sa_flags = 0;
  ret = sigaction(MY_SIGNAL, &sig, NULL);
  if(ret){
    perror("sigaction error");
  }

  //マスク
  ret = sigprocmask(SIG_SETMASK, &setmask, &oldsetmask);
  if(ret){
    perror("sigprocmask error");
  }

  //1秒ごとにカウントアップする
  unmasked = 0;
  for(i = 0; i < 60; i++){
    g_count++;
    printf("%d\n", g_count);
    sleep(1);

    if(i >= 20 && unmasked == 0){
      //マスク解除
      sigprocmask(SIG_SETMASK, &oldsetmask, NULL);
      unmasked = 1;
    }
  }
  return 0;
}
