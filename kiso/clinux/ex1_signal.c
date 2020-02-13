/*
 * シグナルのサンプルコード
 */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

volatile int g_count = 0;

void sample_signal_handler(int num){
  write(1, "IEEE\n", 5);
  g_count = -1;
}

int main(void){
  int i, ret;
  struct sigaction sig;

  //シグナルハンドラの登録
  memset(&sig, 0, sizeof(sig));
  sig.sa_handler = sample_signal_handler;
  sig.sa_flags = 0;
  ret = sigaction(SIGUSR1, &sig, NULL);
  if(ret){
    perror("sigaction error");
  }

  //1秒ごとにカウントアップする
  for(i = 0; i < 60; i++){
    g_count++;
    printf("%d\n", g_count);
    sleep(1);
  }

  return 0;
}
