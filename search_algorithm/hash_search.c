#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 4096

static char **Str[HASH_SIZE];
static int Strmax[HASH_SIZE];

/* 文字列の固有キーの取得 */
int strno(char *str){
  static char *null = "";
  char *p;
  char *ptr;
  char *ptrc;
  int i;
  unsigned n;

  if(str == NULL){
    ptr = NULL;
  }else{
    ptr = str;
  }

  /* ハッシュキーの計算 */
  n = 0;
  for(ptrc = ptr; (*ptrc) != '\0'; ptrc++){
    n += (unsigned)(*ptrc);
  }
  n %= HASH_SIZE;

  /* 重複用配列の検索 */
  for(i = 0; i < Strmax[n]; i++){
    if(strcmp(Str[n][i], ptr) == 0){  /* 存在した場合 */
      return(i * HASH_SIZE + n + 1);  /* 存在したキーを返答 */
    }
  }

  /* 未登録の場合 */
  p = (char *)calloc(strlen(ptr) + 1, sizeof(char));
  strcpy(p, ptr);
  i = Strmax[n];
  Strmax[n]++;
  if(Strmax[n] == 1){
    Str[n] = (char **)calloc((Strmax[n] + 1), sizeof(char *));
  }else{
    Str[n] = (char **)realloc((char *)Str[n], (Strmax[n] + 1) * sizeof(char *));
  }
  Str[n][i] = p;

  /* 登録したキーを返答 */
  return(i * HASH_SIZE + n + 1);
}

/* 固有のキーから文字列の取得 */
char *nostr(int no){
  unsigned i, n;

  if(no < 0){
    return("未定義");
  }else if(no == 0){
    return("");
  }

  /* 格納場所の計算 */
  i = (unsigned)(no - 1) / HASH_SIZE;
  n = (unsigned)(no - 1) % HASH_SIZE;
  if(i < Strmax[n]){
    return(Str[n][i]);  /* 格納している文字列を返答 */
  }else{
    return("未定義");
  }
}

/* 文字列の登録の有無を調査 */
int strfind(char *str){
  static char *null = "";
  char *ptr;
  char *ptrc;
  int i;
  unsigned n;

  if(str == NULL){
    ptr = NULL;
  }else{
    ptr = str;
  }

  /* ハッシュキーの計算 */
  n = 0;
  for(ptrc = ptr; (*ptrc) != '\0'; ptrc++){
    n += (unsigned)(*ptrc);
  }
  n %= HASH_SIZE;

  /* 重複用配列の検索 */
  for(i = 0; i < Strmax[n]; i++){
    if(strcmp(Str[n][i], ptr) == 0){
      return(i * HASH_SIZE + n + 1);
    }
  }

  /* 未登録の場合、-1を返答 */
  return(-1);
}

int main(){
  int no;

  printf("strfind(\"test\") = %d\n", strfind("test"));
  no = strno("test");
  printf("no = %d\n", no);
  printf("strfind(\"test\") = %d\n", strfind("test"));
  printf("nostr(%d)=%s\n", no, nostr(no));

  return(0);
}
