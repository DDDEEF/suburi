#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT (in_port_t)50000
#define BUF_LEN 512

main()
{
  /* 変数宣言 */
  struct sockaddr_in me;
  int soc_waiting;
  int soc;
  char buf[BUF_LEN];

  /* サーバ(自分)のアドレスをsockaddr_in構造体に格納 */
  memset((char *)&me, 0, sizeof(me));
  me.sin_family = AF_INET;
  me.sin_addr.s_addr = htonl(INADDR_ANY);
  me.sin_port = htons(PORT);

  /* IPv4でストリーム型のソケットを生成 */
  if((soc_waiting = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("socket");
    exit(1);
  }

  /* ソケットで待ち受けることを設定 */
  listen(soc_waiting, 1);

  /* 接続要求が来るまでブロックする */
  soc = accept(soc_waiting, NULL, NULL);

  /* 接続待ちのためのソケットを閉じる */
  close(soc_waiting);

  write(1, "Go ahead!\n", 10);

  /* 通信のループ */
  do{
    int n;
    n = read(0, buf, BUF_LEN);
    write(soc, buf, n);
    n = read(soc, buf, BUF_LEN);
    write(1, buf, n);
  }while(strncmp(buf, "quit", 4) != 0);

  /* ソケットを閉じる */
  close(soc);
}