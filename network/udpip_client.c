#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>

#define SOCK_NO 16

int main(int argc, char *argv[]){
  char *hostnm;
  char *portnm;
  struct addrinfo hints;
  struct addrinfo *res, *res0;
  int s[SOCK_NO];
  int smax;
  int i;
  struct sockaddr_storage to[SOCK_NO];
  int tolen[SOCK_NO];
  char hbuf[NI_MAXHOST];
  char sbuf[NI_MAXSERV];
  int error;
  struct pollfd targets[SOCK_NO + 1];
  int nready;
  int len;
  int end;
  char buf[1024];
  struct sockaddr_storage from;
  socklen_t fromlen;

  if(argc < 3){
    fprintf(stderr, "%s host port\n", argv[0]);
    exit(1);
  }
  hostnm = argv[1];
  portnm = argv[2];

  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_DGRAM;
  error = getaddrinfo(hostnm, portnm, &hints, &res0);
  if(error){
    fprintf(stderr, "getaddrinfo:%s %s:%s\n", hostnm, portnm, gai_strerror(error));
    return(-1);
  }

  smax = 0;
  for(res = res0; res&&smax < SOCK_NO; res = res->ai_next){
    error = getnameinfo(res->ai_addr, res->ai_addrlen, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST|NI_NUMERICSERV);
    if(error){
      fprintf(stderr, "getnameinfo:%s %s:%s\n", hostnm, portnm, gai_strerror(error));
      continue;
    }
    s[smax] = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(s[smax] < 0){
      continue;
    }
    memcpy(&to[smax], res->ai_addr, res->ai_addrlen);
    tolen[smax] = res->ai_addrlen;
    fprintf(stderr, "target %d : %s port %s\n", smax, hbuf, sbuf);
    smax++;
  }
  freeaddrinfo(res0);
  if(smax == 0){
    fprintf(stderr, "no destination to send\n");
    return(-1);
  }
  for(i = 0; i < smax; i++){
    targets[i].fd = s[i];
    targets[i].events = POLLIN|POLLERR;
  }
  targets[smax].fd = fileno(stdin);
  targets[smax].events = POLLIN|POLLERR;

  setbuf(stdout, NULL);

  end = 0;
  do{
    switch((nready = poll(targets, smax + 1, -1))){
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
            if((len = recvfrom(s[i], buf, sizeof(buf), 0, (struct sockaddr *)&from, &fromlen)) < 0){
              perror("recvfrom");
              end = 1;
            }else{
              if(getnameinfo((struct sockaddr *)&from, fromlen, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST|NI_NUMERICSERV)){
                fprintf(stderr, "getnameinfo():error\n");
              }else{
                buf[len] = '\0';
                fprintf(stderr, "recvfrom(%d):%s:%s=%s\n", i, hbuf, sbuf, buf);
              }
            }
          }
        }
        if(targets[smax].revents&(POLLIN|POLLERR)){
          if(fgets(buf, sizeof(buf), stdin) == NULL){
            perror("fgets");
            end = 1;
          }else{
            for(i = 0; i < smax; i++){
              if(getnameinfo((struct sockaddr *)&to[i], tolen[i], hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST|NI_NUMERICSERV)){
                fprintf(stderr, "getnameinfo():error\n");
              }else{
                fprintf(stderr, "sendto(%d):%s:%s\n", i, hbuf, sbuf);
              }
              sendto(s[i], buf, strlen(buf), 0, (struct sockaddr *)&to[i], tolen[i]);
            }
          }
        }
        break;
    }
  }while(end != 1);

  for(i = 0; i < smax; i++){
    close(s[i]);
  }
  return(0);
}
