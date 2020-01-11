#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SJIS漢字コード1バイト目判定 */
#define issjiskanji(c) ((0x81 <= (unsigned char)(c&0xff) && (unsigned char)(c&0xff) <= 0x9f) || (0xe0 <= (unsigned char)(c&0xff) && (unsigned char)(c&0xff) <= 0xfc))

/* SJIS半角カタカナ1バイト目判定 */
#define issjiskana(c) ((0xa1 <= (unsigned char)(c&0xff) && (unsigned char)(unsigned char)(c&0xff) <= 0xdf))

/* EUC漢字コード1バイト目判定 */
#define iseuckanji(c) ((0xa1 <= (unsigned char)(c&0xff) && (unsigned char)(c&0xff) <= 0xdf))

/* EUC半角カタカナ1バイト目判定 */
#define iseuckana(c) (0x8e == (unsigned char)(c&0xff)) 

#ifndef SJIS
#define iskanji(c) (iseuckanji(c) || iseuckana(c))
#else
#define iskanji(c) issjiskanji(c)
#endif

/* 専用構造体 */
typedef struct{
  char *buf;
  char *ptr;
}ST_STR;

/* strpbrk()の2バイト文字対応版 */
char *StrPBrk(char *str, char *sep){
  register char *ptr;
  register char *p;
  register int k_flag;

  for(ptr = str; *ptr != '\0'; ptr++){
    if(iskanji(*ptr)){
      k_flag = 1;
    }else{
      k_flag = 0;
    }
    for(p = sep; *p != '\0'; p++){
      if(iskanji(*p)){
        if(k_flag){
          if((*ptr == *p) && (*(ptr + 1) == *(p + 1))){
            return(ptr);
          }
        }
        p++;
      }else{
        if(!k_flag){
          if(*ptr == *p){
            return(ptr);
          }
        }
      }
    }
    if(k_flag){
      ptr++;
    }
  }
  return(NULL);
}

/* 専用構造体の初期化 */
int InitStrTok(ST_STR *st_str){
  st_str->buf = NULL;
  st_str->ptr = NULL;
  return(0);
}

/* 専用構造体の解放 */
int FreeStrTok(ST_STR *st_str){
  free(st_str->buf);
  return(0);
}

/* strtok()の漢字・重複呼び出し対応版 */
char *StrTok(char *str, char *sep, ST_STR *st_str){
  char *p;
  char *p2;

  /* 対象文字列セット時 */
  if(str != NULL){
    if(st_str->buf != NULL){
      free(st_str->buf);
    }
    st_str->buf = strdup(str);
    st_str->ptr = st_str->buf;
  }
  if(st_str->buf == NULL || st_str->ptr == NULL){
    return(NULL);
  }
  while(1){
    if(*(st_str->ptr) == '\0'){
      st_str->ptr = NULL;
      return(NULL);
    }
    p = StrPBrk(st_str->ptr, sep);
    if(p == NULL){
      p = st_str->ptr;
      st_str->ptr = NULL;
      return(p);
    }else if(p == st_str->ptr){
      if(iskanji(*p)){
        st_str->ptr += 2;
      }else{
        st_str->ptr++;
      }
    }else{
      if(iskanji(*p)){
        *p = '\0';
        p++;
        *p = '\0';
      }else{
        *p = '\0';
      }
      p2 = p + 1;
      p = st_str->ptr;
      st_str->ptr = p2;
      return(p);
    }
  }
}

int main(){
  char str[512];
  char sep[512];
  char *ptr;
  ST_STR st;

  setbuf(stdout, NULL);
  printf("sep=");
  fgets(sep, sizeof(sep)-1, stdin);
  printf("str=");
  fgets(str, sizeof(str)-1, stdin);

  InitStrTok(&st);
  for(ptr = StrTok(str, sep, &st); ptr != NULL; ptr = StrTok(NULL, sep, &st)){
    printf("%s\n", ptr);
  }
  FreeStrTok(&st);

  return(0);
}
