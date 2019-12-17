#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define R 0
#define W 1

int popen2(char *command, int *fd_r, int *fd_w){
  int pipe_c2p[2];
  int pipe_p2c[2];
  int pid;

/*****************************************************************************/
/*                                     メモリ?                               */
/*  pipe_c2p[R] cはpに読み込む       |読み込み| <-- p                        */
/*  pipe_c2p[W] cはpに書き込む c --> |書き込み| これをcの0標準入力に切り替え */
/*                                                                           */
/*  pipe_p2c[R] pはcに読み込む c --> |読み込み| これをcの1標準出力に切り替え */
/*  pipe_p2c[W] pはcに書き込む       |書き込み| <-- p                        */
/*****************************************************************************/

  /* 2つのパイプを作成 */
  if(pipe(pipe_c2p) < 0){
    perror("popen2");
    return(-1);
  }
  if(pipe(pipe_p2c) < 0){
    perror("popen2");
    close(pipe_c2p[R]);
    close(pipe_c2p[W]);
    return(-1);
  }

  /* 子プロセスの生成 */
  if((pid = fork()) < 0){
    perror("popen2");
    close(pipe_c2p[R]);
    close(pipe_c2p[W]);
    close(pipe_p2c[R]);
    close(pipe_p2c[W]);
    return(-1);
  }else if(pid == 0){   /* 子プロセス側 */
    close(pipe_p2c[W]);
    close(pipe_c2p[R]);
    dup2(pipe_p2c[R], 0);
    dup2(pipe_c2p[W], 1);
    close(pipe_p2c[R]);
    close(pipe_c2p[W]);
    if(execlp("sh", "sh", "-c", command, NULL) < 0){
      perror("popen2");
      close(pipe_p2c[R]);
      close(pipe_c2p[W]);
      exit(1);
    }
  }
  /* 親プロセス側 */
  close(pipe_p2c[R]);
  close(pipe_c2p[W]);
  *fd_w = pipe_p2c[W];
  *fd_r = pipe_c2p[R];

  return(pid);
}

int main(){
  int fd_r;
  int fd_w;
  FILE *fp_r;
  FILE *fp_w;
  int pid;
  int status;
  char buf[512];
  
  if((pid = popen2("sort", &fd_r, &fd_w)) == -1){
    return(0);
  }

  fp_r = fdopen(fd_r, "r");
  fp_w = fdopen(fd_w, "w");
  fputs("z\n", fp_w);
  fputs("a\n", fp_w);
  fputs("h\n", fp_w);
  fputs("k\n", fp_w);
  fclose(fp_w);
  while(1){
    fgets(buf, sizeof(buf), fp_r);
    if(feof(fp_r)){
      break;
    }
    fputs(buf, stdout);
  }
  fclose(fp_r);
  pid = wait(&status);
  printf("pid = %d, status = %d\n", pid, status);

  return(0);
}
