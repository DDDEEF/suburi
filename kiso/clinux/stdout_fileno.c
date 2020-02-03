#include <stdio.h>

#define FILENO(X) printf(#X "%d %p\n", fileno(X), X)
#define FILENO_REF(X) printf(#X "%d %p\n", X->_fileno, X);

int main(void){
  //fileno関数によるファイルディスクリプタの確認
  FILENO(stdin);
  FILENO(stdout);
  FILENO(stderr);
  
  printf("\n");

  //構造体参照によるファイルディスクリプタの確認
  FILENO_REF(stdin);
  FILENO_REF(stdout);
  FILENO_REF(stderr);

  return 0;
}
