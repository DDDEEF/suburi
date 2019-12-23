#include <stdio.h>

int main(int argc, char *argv[]){
  FILE *fp;
  fp = freopen("../tmp_area/debug.log", "w", stdout);

  printf("Content-type:text/html\n\n");
  printf("<html>\n");
  printf("<head>\n");
  printf("<META HTTP-EQUIV=\"Content-type\"CONTENT=\"text/html; charset=x-euc\">\n");
  printf("<title>テスト</title>\n");
  printf("</head>\n");
  printf("<body>\n");
  printf("<p>テストです</p>\n");
  printf("</body>\n");
  printf("</html>\n");
  return(0);
}
