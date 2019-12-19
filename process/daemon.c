#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* クローズする最大ディスクリプタ値 */
#define MAXFD 64

/* デーモン化 */
void InitDaemon(int chdir_root, int all_fd_close){
  int i;
  int fd;
  pid_t pid;

  sleep(5);
  if((pid = fork()) != 0){
    /* 親プロセスの終了 */
    exit(0);
  }

  sleep(5);
  /* 最初の子プロセス */
  /* セッションリーダー */
  setsid();

  /* HUPシグナルを無視するようにする */
  signal(SIGHUP, SIG_IGN);

  sleep(5);
  /* 再びfork()し、子プロセスを生成し、最初の子プロセスの終了 */
  if((pid = fork()) != 0){
    exit(0);
  }

  sleep(5);
  /* デーモンプロセスと化す */
  if(chdir_root){
    /* ルートディレクトリに移動 */
    chdir("/");
  }
  
  sleep(5);
  if(all_fd_close){
    for(i = 0; i < MAXFD; i++){
      close(i);
    }

    if((fd = open("/dev/null", O_RDWR, 0)) != -1){
      (void)dup2(fd, 0);
      (void)dup2(fd, 1);
      (void)dup2(fd, 2);
      if(fd > 2){
        (void)close(fd);
      }
    }
  }
}

int main(){
  FILE *fp;
  int fd;
  char buf[512];

  InitDaemon(1, 1);

  fprintf(stderr, "stderr\n");

  sprintf(buf, "/tmp/testXXXXXX");

  if((fd = mkstemp(buf)) == -1){
    perror("mkstemp");
    return(-1);
  }

  if((fp = fdopen(fd, "w")) == NULL){
    perror("fdopen");
    return(-1);
  }

  fprintf(fp, "cwd = %s\n", getcwd(buf, sizeof(buf)));

  fclose(fp);

  return(0);
}
