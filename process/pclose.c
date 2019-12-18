#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define R 0
#define W 1

static struct pid{
  struct pid *next;
  FILE *fp;;
  pid_t pid;
}*pidlist;

FILE *popen_err(char *command, char *option){
  struct pid *cur;
  int pipe_c2p_e[2];
  int pid;
  FILE *fp;

  if((*option != 'r')||option[1]){
    fprintf(stderr, "popen_err():option error:return(NULL)\n");
    return(NULL);
  }

  if((cur = (struct pid *)malloc(sizeof(struct pid)) == NULL)){
    fprintf(stderr, "popen_err():malloc error:return(NULL)\n");
    return(NULL);
  }

  /* 2つのパイプの作成 */
  if(pipe(pipe_c2p_e) < 0){
    perror("pipe");
    return(NULL);
  }

  /* 子プロセスの生成 */
  if((pid = fork()) < 0){
    perror("fork");
    close(pipe_c2p_e[R]);
    close(pipe_c2p_e[W]);
    return(NULL);
  }else if(pid == 0){     /* 子プロセス側 */
    close(pipe_c2p_e[R]);
    dup2(pipe_c2p_e[W], 2); /* 標準エラー出力 */
    close(pipe_c2p_e[W]);
    execlp("sh", "sh", "-c", command, NULL);
    _exit(127);
  }

  close(pipe_c2p_e[W]);
  fp = fdopen(pipe_c2p_e[R], option);

  /* リストに登録 */
  cur->fp = fp;
  cur->pid = pid;
  cur->next = pidlist;
  pidlist = cur;

  return(fp);
}

int pclose_err(FILE *fp){
  register struct pid *cur;
  register struct pid *last;
  sigset_t set, omask;
  int pstat;
  pid_t pid;
  extern int errno;

  fclose(fp);

  /* リストから対象のファイルポインタを検索 */
  for(last = NULL, cur = pidlist; cur; last = cur, cur = cur->next){
    if(cur->fp == fp){
      break;
    }
  }
  if(cur == NULL){
    return(-1);
  }

  /* 子プロセスの終了ステータスを取得 */
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  sigaddset(&set, SIGQUIT);
  sigaddset(&set, SIGHUP);
  sigprocmask(SIG_SETMASK, &set, &omask);
  do{
    pid = waitpid(cur->pid, (int *)&pstat, 0);
  }while(pid == -1 && errno == EINTR);
  sigprocmask(SIG_SETMASK, &omask, NULL);

  /* リストから削除 */
  if(last == NULL){
    pidlist = cur->next;
  }else{
    last->next = cur->next;
  }
  free(cur);
  return(pid == -1 ? -1 : pstat);
}

int main(){
  FILE *fp;
  char buf[512];
  int ret;

  if((fp = popen_err("ls -1 /abc/def/ghi", "r")) == NULL){
    return(-1);
  }
  while(1){
    fgets(buf, sizeof(buf), fp);
    if(feop(fp)){
      break;
    }
    printf("---> %s", buf);
  }

  ret = pclose_err(fp);
  printf("pclose_err ret = %d\n", ret);

  return(0);
}
