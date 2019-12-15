#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

/* 待ちフラグ */
static int ringring = 0;

static void sleephandler(int sig){
  if(sig == SIGALRM){
    ringring = 1;
  }
}

/***************************************/
/* 1秒(1s)      1000 * 1000 * 1000nsec */ 
/* 1ミリ秒(1ms)        1000 * 1000nsec */
/* 1マイクロ秒(1us)           1000nsec */
/* 1ナノ秒(1ns)                  1nsec */
/***************************************/
int MicroSleep(long sec, long usec){
  struct itimerval val, oval;
  sigset_t mask;

  /* 待つ必要なし */
  if(sec == 0 && usec == 0){
    return(0);
  }

  /* 実時間タイマの現在値をクリア */
  timerclear(&val.it_interval);
  timerclear(&val.it_value);

  /* インターバルタイマの値をセット */
  if(setitimer(ITIMER_REAL, &val, &oval) < 0){
    return(sec);
  }

  fprintf(stderr, "\tbefore = %lu.%06d\n", oval.it_value.tv_sec, oval.it_value.tv_usec);
  fprintf(stderr, "\t    -%lu.%06lu\n", sec, usec);

  /* 実時間タイマの現在値と指定値を比較し残り時間を計算しておく */
  val.it_value.tv_sec = sec;
  val.it_value.tv_usec = usec;
  if(timerisset(&oval.it_value)){
    if(timercmp(&oval.it_value, &val.it_value, >)){
      timersub(&oval.it_value, &val.it_value, &oval.it_value);
    }else{
      val.it_value = oval.it_value;
      oval.it_value.tv_sec = 1;
      oval.it_value.tv_usec = 0;
    }
  }

  /* シグナルハンドラ登録 */
  signal(SIGALRM, sleephandler);
  ringring = 0;

  /* 実時間タイマに指定時間をセット */
  setitimer(ITIMER_REAL, &val, (struct itimerval *)NULL);

  /* 待ち */
  sigfillset(&mask);
  sigdelset(&mask, SIGALRM);
  while(!ringring){
    //sigpause(SIGALRM);
    sigsuspend(&mask);
  }

  ringring = 0;

  /* 元のタイマの残り時間をセット */
  setitimer(ITIMER_REAL, &oval, (struct itimerval *)NULL);
  fprintf(stderr, "\tset   =%lu.%06d\n", oval.it_value.tv_sec, oval.it_value.tv_usec);
  return(0);
}

int main(){
  int i;
  struct timeval start, now, result;
  sigset_t mask;
  int timerVal = 5;
  double timerLest;

  gettimeofday(&start, NULL);
  fprintf(stderr, "Set alarm %d sec\n", timerVal);
  alarm(timerVal);
  timerLest = timerVal;

  for(i = 0; i < 4; i++){
    fprintf(stderr, "MicroSleep(0, 500000)\n");
    MicroSleep(0, 500000);
    gettimeofday(&now, NULL);
    timersub(&now, &start, &result);
    fprintf(stderr, "LapTime = %lu.%06d\n", result.tv_sec, result.tv_usec);
    timerLest -= 0.5;
  }

  fprintf(stderr, "Wait lest %g sec\n", timerLest);
  sigfillset(&mask);
  sigdelset(&mask, SIGALRM);
  while(!ringring){
    //sigpause(SIGALRM);
    sigsuspend(&mask);
  }
  ringring = 0;
  gettimeofday(&now, NULL);
  timersub(&now, &start, &result);
  fprintf(stderr, "Total  =%lu.%06d\n", result.tv_sec, result.tv_usec);
  return(0);
}
