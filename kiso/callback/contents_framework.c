#include <stdio.h>

#include "contents_framework.h"

/* run methodd. */
void run(){
  // callback関数(update)を設定
  contents_run(update);

  return;
}

/* callback関数 */
void update(char *str){
  printf("%s", str);
  return;
}
