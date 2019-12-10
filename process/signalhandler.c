#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define USE_SIGNAL

/* コマンドライン引数、環境変数のアドレス保持用 */
int *Argc;
char ***Argv;
char ***Envp;

int HupFlag = 0;

void ReExec(){
  fprintf(stderr, "HupHandler() -> ReExec() signal = %d\n", HupFlag);

  /* sleep()によるSIGALRMを解除:linuxではおこなわなくても問題ないが念のため */
  alarm(0);

  /* 連続シグナル対策 */
  signal(SIGHUP, SIG_IGN);

  /* 自プロセスの上書き再実行 */
  if(execve((*Argv)[0], (*Argv), (*Envp)) == -1){
    perror("execve");
  }
}

void HupHandler(int sig){
  HupFlag = sig;
}

int main(int argc, char *argv[], char *envp[]){
  struct sigaction sa;
  int i;

  /* コマンドライン引数、環境変数のアドレスをグローバルに保持 */
  Argc = &argc;
  Argv = &argv;
  Envp = &envp;

  /* コマンドライン引数、環境変数の表示 */
/*
  fprintf(stderr, "start pid = %d\n", getpid());
  fprintf(stderr, "argc = %d\n", argc);
  for(i = 0; argv[i] != NULL; i++){
    fprintf(stderr, "argv[%d] = %s\n", i, argv[i]);
  }
  for(i = 0; envp[i] != NULL; i++){
    fprintf(stderr, "envp[%d] = %s\n", i, envp[i]);
  }
*/

  /* SIGHUPのシグナルハンドラを指定 */
#ifdef USE_SIGNAL
  signal(SIGHUP, HupHandler);

  /* 現状の表示 */
  sigaction(SIGHUP, (struct sigaction *)NULL, &sa);
  fprintf(stderr, "SA_ONSTACK = %d\n", (sa.sa_flags&SA_ONSTACK)?1:0);
  fprintf(stderr, "SA_RESETHAND = %d\n", (sa.sa_flags&SA_RESETHAND)?1:0);
  fprintf(stderr, "SA_NODEFER = %d\n", (sa.sa_flags&SA_NODEFER)?1:0);
  fprintf(stderr, "SA_RESTART = %d\n", (sa.sa_flags&SA_RESTART)?1:0);
  fprintf(stderr, "SA_SIGINFO = %d\n", (sa.sa_flags&SA_SIGINFO)?1:0);
  for(i = 1; i <= 31; i++){
    fprintf(stderr, "%d = %d\n", i, sigismember(&sa.sa_mask, i));
  }
  fprintf(stderr, "signal():end\n");
#else
  sigaction(SIGHUP, (struct sigaction *)NULL, &sa);
  sa.sa_handler = HupHandler;
  sa.sa_flags = SA_NODEFER;
  sigaction(SIGHUP, &sa, (struct sigaction *)NULL);

  /* 現状の表示 */
  sigaction(SIGHUP, (struct sigaction *)NULL, &sa);
  fprintf(stderr, "sigaction():end\n");
  fprintf(stderr, "SA_ONSTACK = %d\n", (sa.sa_flags&SA_ONSTACK)?1:0);
  fprintf(stderr, "SA_RESETHAND = %d\n", (sa.sa_flags&SA_RESETHAND)?1:0);
  fprintf(stderr, "SA_NODEFER = %d\n", (sa.sa_flags&SA_NODEFER)?1:0);
  fprintf(stderr, "SA_RESTART = %d\n", (sa.sa_flags&SA_RESTART)?1:0);
  fprintf(stderr, "SA_SIGINFO = %d\n", (sa.sa_flags&SA_SIGINFO)?1:0);
  for(i = 1; i <= 31; i++){
    fprintf(stderr, "%d = %d\n", i, sigismember(&sa.sa_mask, i));
  }
#endif

  /* 5秒おきにカウントを表示 */
  for(i = 0; ; i++){
    if(HupFlag){
      ReExec();
      HupFlag = 0;
    }
    fprintf(stderr, "count = %d\n", i);
    sleep(5);
  }
}

