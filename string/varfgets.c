#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 動的ファイル1行読み込み */
int varfgets(char **ret_buf, FILE *fp){
  char data[1024];
  char *buf;
  int len;
  int now_len;
  int size;

  size = 0;
  buf = NULL;
  now_len = 0;

  while(1){
    fgets(data, sizeof(data), fp);
    if(feof(fp)){
      break;
    }
    len = strlen(data);
    if(now_len + len >= size){
      if((now_len + len - size) > 4096){
        size = now_len + len + 1;
      }else{
        size += 4096;
      }
      if(buf == NULL){
        buf = (char *)calloc(size, sizeof(char));
      }else{
        buf = (char *)realloc(buf, size * sizeof(char));
      }
    }
    strncpy(&buf[now_len], data, size - now_len - 1);
    now_len += len;
    if(now_len > 0 && (buf[now_len - 1] == '\n')){
      break;
    }
  }
  *ret_buf = buf;
  
  return(now_len);
}

int main(){
  char *ptr;

  while(1){
    varfgets(&ptr, stdin);
    if(feof(stdin)){
      break;
    }
    fputs(ptr, stdout);
    free(ptr);
  }
  return(0);
}
