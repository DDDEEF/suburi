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
  struct hostent *server_ent;
  struct sockaddr_in server;
  int soc;
  char hostname[] = "cisprof08";
  char buf[BUF_LEN];

  /* サーバ(相手)のホスト名からアドレス情報を得る */
  if((server_ent = gethostbyname(hostname)) == NULL){
    perror("gethostbyname");
    exit(1);
  }

  /* サーバ(相手)のアドレスをsockaddr_in構造体に格納 */
  memset((char*)&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  memcpy((char *)&server.sin_addr, server_ent->h_addr, server_ent->h_length);

  /* IPv4でストリーム型のソケットを作成 */
  if((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("socket");
    exit(1);
  }

  /* サーバ(相手)に接続 */
  if(connect(soc, (struct sockaddr *)&server, sizeof(server)) == -1){
    perror("connect");
    exit(1);
  }

  /* 相手が先 */
  write(1, "Wait\n", 5);

  /* 通信のループ */
  do{
    int n;

    n = read(soc, buf, BUF_LEN);
    write(1, buf, n);
    n = read(0, buf, BUF_LEN);
    write(soc, buf, n);
  }while(strncmp(buf, "quit", 4) != 0);

  /* ソケットを閉じる */
  close(soc);
}