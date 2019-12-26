#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <poll.h>

/*
 *@brief 標準入力から標準出力へエコーする
 */
static int echo_process(void){
  ssize_t rnum = 0;
  ssize_t wnum = 0;
  char buf[BUFSIZ] = {"\0"};

  rnum = read(0, buf, sizeof(buf));
  if(rnum < 0){
    printf("Error:read(%d)%s\n", errno, strerror(errno));
    return(-1);
  }

  wnum = write(1, buf, rnum);
  if(wnum < 0){
    printf("Error:write(%d)%s\n", errno, strerror(errno));
    return(-1);
  }

  return(0);
}

/*
 *@brief 標準入力を待ち合わせる
 *@param[in] filepath ファイルパス名
 *@return 0:success/-1:failure
 */ 
static int select_stdin(void){
  int rc = 0;
  struct pollfd fds[1];
  fds[0].fd = 0;
  fds[0].events = POLLIN;
  fds[0].revents = 0;

  /* 待ち合わせ時間:3.5秒 */
  rc = poll(fds, 1, 3500);
  if(rc < 0){
    printf("Error:poll() %s\n", strerror(errno));
    return(-1);
  }else if(rc == 0){
    /* タイムアウト */
    printf("CAUTION:timeout\n");
    return(-1);
  }

  if(fds[0].revents&POLLIN){
    /* 待ち合わせ時間内に到着 */
    echo_process();
  }

  return(0);
}

int main(int argc, char *argv[]){
  int rc = 0;

  if(argc != 1){
    fprintf(stderr, "Usage:%s\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  rc = select_stdin();
  if(rc != 0){
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
