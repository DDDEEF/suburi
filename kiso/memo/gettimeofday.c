#include <stdio.h>
#include <sys/time.h>

#define howmany(x, y)   (((x) + ((y) - 1)) / (y))
#define roundup(x, y)   ((((x) + ((y) - 1)) / (y)) * (y))
#define rounddown(x, y) (((x) / (y)) * (y))

int main(int argc, char **argv){
  struct timeval tv = { 0, 0 };
  gettimeofday(&tv, NULL);
  printf("%ld %06lu\n", tv.tv_sec, tv.tv_usec);

  unsigned long unix_time;
  //マイクロ秒に揃えて足し合わせる
  unix_time = (unsigned long)((tv.tv_sec * 1000000) + tv.tv_usec);

  //ミリ秒に調整して表示する
  printf("[%d]ms\n", howmany(unix_time, 1000));

  sleep(1);
  gettimeofday(&tv, NULL);
  unix_time = (unsigned long)((tv.tv_sec * 1000000) + tv.tv_usec);
  printf("[%d]ms\n", howmany(unix_time, 1000));
}
