#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>
#include <sys/wait.h>

#define SOCK_NO 16

void ChildEnd(int sig){
  int pid;
  pid = waitpid(-1, NULL, WNOHANG);
  fprintf(stderr, "ChildEnd:%d\n", pid);
}

int main(int argc, char *argv[]){
  char *portnm;
  int s[SOCK_NO];
  struct addrinfo hints;
  struct addrinfo *res, *res0;
  int error;
  int smax;
  char hbuf[NI_MAXHOST];
  char sbuf[NI_MAXSERV];
#ifdef IPV6_V6ONLY
  const int on = 1;
#endif
  char buf[1024];
  int acc, end;
  struct pollfd targets[SOCK_NO];
  int nready;
  int len;
  int i;
  socklen_t fromlen;
  struct sockaddr_storage from;
  pid_t pid;

  if(argc < 2){
    fprintf(stderr, "%s port\n", argv[0]);
    return(1);
  }
  portnm = argv[1];

  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  error = getaddrinfo(NULL, portnm, &hints, &res0);
  if(error){
    fprintf(stderr, "getaddrinfo():%s:%s\n", portnm, gai_strerror(error));
    return(-1);
  }

  smax = 0;
  for(res = res0; res&&smax < SOCK_NO; res = res->ai_next){
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
      fprintf(stderr, "getnameinfo():%s\n", gai_strerror(error));
      freeaddrinfo(res0);
      return(-1);
    }
    fprintf(stderr, "listen to %s %s\n", hbuf, sbuf);
    smax++;
  }
  freeaddrinfo(res0);

  if(smax == 0){
    fprintf(stderr, "no socket to listen to\n");
    return(-1);
  }

  signal(SIGCHLD, ChildEnd);

  for(i = 0; i < smax; i++){
    targets[i].fd = s[i];
    targets[i].events = POLLIN|POLLERR;
  }

  end = 0;
  do{
    switch((nready = poll(targets, smax, -1))){
      case -1:
        if(errno != EINTR){
          perror("poll");
          end = 1;
        }
        break;
      case 0:
        fprintf(stderr, "Timeout\n");
        break;
      default:
        for(i = 0; i < smax; i++){
          if(targets[i].revents&(POLLIN|POLLERR)){
            fromlen = sizeof(from);
            acc = accept(s[i], (struct sockaddr *)&from, &fromlen);
            if(acc < 0){
              if(errno != EINTR){
                perror("accept");
              }
            }else{
              if(getnameinfo((struct sockaddr *)&from, fromlen, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST|NI_NUMERICSERV)){
                fprintf(stderr, "getnameinfo():error\n");
              }else{
                fprintf(stderr, "accept(%d):%s:%s\n", i, hbuf, sbuf);
                if((pid = fork()) == 0){
                  for(i = 0; i < smax; i++){
                    close(s[i]);
                  }
                  end = 0;
                  do{
                    if((len = recv(acc, buf, sizeof(buf), 0)) < 0){
                      perror("recv");
                      end = 1;
                    }else if(len == 0){
                      fprintf(stderr, "closed\n");
                      end = 1;
                    }else{
                      send(acc, buf, len, 0);
                    }
                  }while(end != 1);
                  close(acc);
                  fprintf(stderr, "Child(%d):end\n", getpid());
                  return(0);
                }else if(pid > 0){
                  fprintf(stderr, "ChildStart:%d\n", pid);
                  close(acc);
                }else{
                  perror("fork");
                  close(acc);
                }
              }
            }
          }
        }
        break;
    }
  }while(end != 1);
  for(i = 0; i <smax; i++){
    close(s[i]);
  }
  return(0);
}
