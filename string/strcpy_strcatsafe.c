#include <stdio.h>
#include <string.h>

size_t strLcpy(char *dst, const char *src, size_t size){
  char *pd;
  const char *ps;
  char *pde = dst + size - 1;

  for(pd = dst, ps = src; *ps != '\0' && pd < pde; pd++, ps++){
    *pd = *ps;
  }

  for(; pd <= pde; pd++){
    *pd = '\0';
  }

  while(*ps++);

  return(ps - src - 1);
}

size_t strLcat(char *dst, const char *src, size_t size){
  char *pd;
  const char *ps;
  char *pde;
  size_t lest;
  size_t dlen;

  for(pd = dst, lest = size; *pd != '\0' && lest != 0; pd++, lest--);

  dlen = pd - dst;
  if(size - dlen == 0){
    fprintf(stderr, "Warning : strLcat():dst : no '\\0'\n");
    return(dlen + strlen(src));
  }

  pde = dst + size - 1;
  for(ps = src; *ps != '\0' && pd < pde; pd++, ps++){
    *pd = *ps;
  }

  for(; pd <= pde; pd++){
    *pd = '\0';
  }

  while(*ps++){
    return(dlen + (ps - src - 1));
  }
}

/* 動作確認用のmain() */
int main(){
  char dst[8];
  char src[512];
  char *ptr;
  int i;
  size_t ret;

  /* dstがヌル文字終端されていない場合のstrLcat()テスト */
  memcpy(dst, "12345678", 8);
  ret = strLcat(dst, "1234", sizeof(dst));
  if(ret >= sizeof(dst)){
    fprintf(stderr, "strLcat():truncated:ret=%d\n", ret);
  }else{
    fprintf(stderr, "strLcat():success:ret=%d\n", ret);
  }
  for(i = 0; i < sizeof(dst); i++){
    fprintf(stderr, "[%c:%02x]", dst[i], dst[i]);
  }
  fprintf(stderr, "\n");

  /* 標準入力からのstrLcpy(), strLcat()テスト */
  while(1){
    fgets(src, sizeof(src), stdin);
    if(feof(stdin)){
      break;
    }
    if((ptr = strchr(src, '\n')) != NULL){
      *ptr = '\0';
    }

    ret = strLcpy(dst, src, sizeof(dst));
    if(ret >= sizeof(dst)){
      fprintf(stderr, "strLcpy():truncated:ret=%d\n", ret);
    }else{
      fprintf(stderr, "strLcpy():success:ret=%d\n", ret);
    }
    for(i = 0; i < sizeof(dst); i++){
      fprintf(stderr, "[%c:%02x]", dst[i], dst[i]);
    }
    fprintf(stderr, "\n");

    fgets(src, sizeof(src), stdin);
    if(feof(stdin)){
      break;
    }
    if((ptr = strchr(src, '\n')) != NULL){
      *ptr = '\0';
    }

    ret = strLcat(dst, src, sizeof(dst));
    if(ret >= sizeof(dst)){
      fprintf(stderr, "strLcat():truncated:ret:=%d\n", ret);
    }else{
      fprintf(stderr, "strLcat():success:ret=%d\n", ret);
    }
    for(i = 0; i < sizeof(dst); i++){
      fprintf(stderr, "[%c:%02x]", dst[i], dst[i]);
    }
    fprintf(stderr, "\n");
  }
  
  return(0);
}
