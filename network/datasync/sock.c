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
      setsockopt(s[smax], IPPROT_IPV6, IPV6_V6ONLY, &on, sizeof(on));
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

/* タイムアウトつきrecv(poll) */
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

/* 固定バッファ1行受信 */

/* 動的バッファ1行受信 */

/* 指定サイズ送信 */
