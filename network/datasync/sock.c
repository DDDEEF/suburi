#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>
#include <fcntl.h>
#include <poll.h>
#include "sock.h"
#include "log.h"

static int RecvTimeoutSec = RECV_TIMEOUT_SEC;

/* IPv6対応サーバソケット生成 */
int ServerSocketNew(char *portnm, int s[], int maxsock){
  struct addrinfo hints;
  struct addrinfo *res;
  struct addrinfo *res0;
  int error;
  int smax;
  char hbuf[NI_MAXHOST];
  char sbuf[NI_MAXSERV];
#ifdef IPV6_V6ONLY
  const int on = 1;
#endif
  
  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  error = getaddrinfo(NULL, portnm, &hints, &res0);
  if(error){
    Syslog(LOG_ERR, "sock2.c:ServerSocketNew:%s:%s\n", portnm, gai_strerror(error));
    return(-1);
  }

  smax = 0;
  for(res = res0; res&&smax < maxsock; res = res->ai_next){
    s[smax] = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(s[smax] < 0){
      continue;
    }
#ifdef IPV6_V6ONLY
    if(res->ai_family == AF_INET6){
      setsockopt(s[smax], IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on));
    }
#endif
    if(bind(s[smax], res->ai_addr, res->ai_addrlen) < 0){
      close(s[smax]);
      s[smax] = -1;
      continue;
    }
    if(listen(s[smax], 5) < 0){
      close(s[smax]);
      s[smax] = -1;
      continue;
    }
    error = getnameinfo(res->ai_addr, res->ai_addrlen, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST|NI_NUMERICSERV);
    if(error){
      Syslog(LOG_ERR, "sock2.c:ServerSocketNew:%s\n", gai_strerror(error));
      freeaddrinfo(res0);
      return(-1);
    }
    Syslog(LOG_INFO, "sock2.c:ServerSocketNew:listen to %s %s\n", hbuf, sbuf);
    smax++;
  }

  freeaddrinfo(res0);

  if(smax == 0){
    Syslog(LOG_ERR, "sock2.c:ServerSocketNew:no socket to listen to\n");
    return(-1);
  }

  return(smax);
}

/* IPv6対応クライアントソケット接続 */
int ClientSocketNew(char *hostnm, char *portnm){
  struct addrinfo hints;
  struct addrinfo *res;
  struct addrinfo *res0;
  int s;
  char hbuf[NI_MAXHOST];
  char sbuf[NI_MAXSERV];
  int error;
  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_STREAM;
  error = getaddrinfo(hostnm, portnm, &hints, &res0);
  if(error){
    Syslog(LOG_ERR, "sock2.c:ClientSocketNew:%s %s:%s\n", hostnm, portnm, gai_strerror(error));
    return(-1);
  }
  for(res = res0; res; res = res->ai_next){
    error = getnameinfo(res->ai_addr, res->ai_addrlen, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST|NI_NUMERICSERV);
    if(error){
      Syslog(LOG_ERR, "sock2.c:ClientSocketNew:%s %s:%s\n", hostnm, portnm, gai_strerror(error));
      continue;
    }
    Syslog(LOG_DEBUG, "sock2.c:ClientSocketNew:trying %s port %s\n", hbuf, sbuf);
    s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(s < 0){
      continue;
    }
    if(connect(s, res->ai_addr, res->ai_addrlen) < 0){
      close(s);
      s = -1;
      continue;
    }else{
      Syslog(LOG_DEBUG, "sock2.c:ClientSocketNew:connect:Success\n");
      freeaddrinfo(res0);
      return(s);
    }
  }
  freeaddrinfo(res0);
  Syslog(LOG_ERR, "sock2.c:ClientSocketNew:no destination to connect to \n");
  return(-1);
}

/* 受信タイムアウト設定 */
int SetRecvTimeoutSet(int sec){
  RecvTimeoutSec = sec;
  return(0);
}

/* タイムアウト付き受信(poll) */
int RecvTimeoutPoll(int soc, char *buf, int bufsize, int flag){
  struct pollfd targets[1];
  int nready;
  int len;
  int ret;
  int end;

  /* poll()用データの作成 */
  targets[0].fd = soc;
  targets[0].events = POLLIN|POLLERR;

  do{
    end = 0;
    switch((nready = poll(targets, 1, RecvTimeoutSec * 1000))){
      case -1:
        if(errno != EINTR){
          SyslogPerror(LOG_ERR, "poll");
          Syslog(LOG_ERR, "sock.c:RecvTimeoutPoll():poll():-1(errno = %d)\n", errno);
          ret = -1;
          end = 1;
        }
        break;
      case 0:
        Syslog(LOG_DEBUG, "sock.c:RecvTimeoutPoll():poll():Timeout\n");
        ret = -1;
        end = 1;
        break;
      default:
        if(targets[0].revents&(POLLIN|POLLERR)){
          if((len = recv(soc, buf, bufsize, flag)) < 0){
            SyslogPerror(LOG_ERR, "recv");
            Syslog(LOG_ERR, "sock.c:RecvTimeoutpoll():recv()<0\n");
            ret = -1;
            end = 1;
          }else{
            ret = len;
            end = 1;
          }
        }
        break;
    }
  }while(end != 1);

  return(ret);
}

/* ソケットから1行受信：固定バッファ */
int RecvOneLine_1(int soc, char *buf, int bufsize, int flag){
  int len;
  int pos;
  int end;
  int ret;
  char c;

  /* 初期化 */
  buf[0] = '\0';

  pos = 0;
  do{
    end = 0;
    /* 1バイト受信 */
    c = '\0';
    len = RecvTimeoutPoll(soc, &c, 1, flag);
    if(len == -1){
      /* エラー:エラー終了 */
      SyslogPerror(LOG_ERR, "recv");
      Syslog(LOG_ERR, "sock.c:RecvOneLine_1():RecvTimeoutPoll():%d\n", len);
      ret = -1;
      end = 1;
    }else if(len == 0){
      /* 切断 */
      Syslog(LOG_DEBUG, "sock.c:RecvOneLine_1():recv():EOF\n");
      if(pos > 0){
        /* すでに受信データを有り:正常終了 */
        ret = pos;
        end = 1;
      }else{
        /* 受信データ無し:切断終了 */
        ret = 0;
        end = 1;
      }
    }else{
      /* 正常受信 */
      buf[pos] = c;
      pos++;
      if(buf[pos-1] == '\n'){
        /* 改行:終了 */
        ret = pos;
        end = 1;
      }
      if(pos == bufsize - 1){
        /* 指定サイズ:終了 */
        ret = pos;
        end = 1;
      }
    }
  }while(end != 1);

  buf[pos] = '\0';
  return(ret);
}

/* ソケットから1行受信:動的バッファ */
int RecvOneLine_2(int soc, char **ret_buf, int flag){
  #define RECV_ONE_LINE_2_ALLOC_SIZE 1024
  #define RECV_ONE_LINE_2_ALLOC_LIMIT 1024*1024+1
  char buf[RECV_ONE_LINE_2_ALLOC_SIZE+1];
  int size = 0;
  int now_len = 0;
  int end;
  int len;
  int ret;
  char *data = NULL;

  *ret_buf = NULL;

  do{
    end = 0;
    /* 1行受信 */
    len = RecvOneLine_1(soc, buf, sizeof(buf), flag);
    if(len < 0){
      /* エラー */
      Syslog(LOG_ERR, "sock.c:RecvOneLine_2():RecvOneLine1():%d\n", len);
      free(data);
      data = NULL;
      ret = -1;
      end = 1;
    }else if(len == 0){
      /* 切断 */
      if(now_len > 0){
        /* 受信データ有り */
        ret = now_len;
        end = 1;
      }else{
        /* 受信データ無し */
        ret = 0;
        end = 1;
      }
    }else{
      /* 正常受信 */
      if(now_len + len >= size){
        /* 領域不足 */
        if(size == 0){
          size = RECV_ONE_LINE_2_ALLOC_SIZE + 1;
        }else{
          size += RECV_ONE_LINE_2_ALLOC_SIZE;
        }
        if(size > RECV_ONE_LINE_2_ALLOC_LIMIT){
          free(data);
          data = NULL;
        }else if(data == NULL){
          data = malloc(size);
        }else{
          data = realloc(data, size);
        }
      }
      if(data == NULL){
        /* メモリ確保エラー */
        SyslogPerror(LOG_ERR, "sock.c:RecvOneLine_2():malloc or limit-over");
        ret = -1;
        end = 1;
      }else{
        /* データ格納 */
        memcpy(&data[now_len], buf, len);
        now_len += len;
        data[now_len] = '\0';
        if(data[now_len - 1] == '\n'){
          /* 末尾が改行 */
          ret = now_len;
          end = 1;
        }
      }
    }
  }while(end != 1);

  *ret_buf = data;
  return(ret);
}

/* 指定サイズソケットに送信 */
int SendSize(int soc, char *buf, int size){
  int lest;
  int len;
  char *ptr;
  lest = size;
  ptr = buf;
  do{
    len = send(soc, ptr, lest, 0);
    if(len <= 0){
      SyslogPerror(LOG_ERR, "send");
      Syslog(LOG_ERR, "sock.c:SendSize():send(%d):%d", lest, len);
      return(-1);
    }
    lest -= len;
    ptr += len;
  }while(lest>0);

  return(size);
}
