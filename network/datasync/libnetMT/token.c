#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include "token.h"
#include "log.h"

/* staticプロトタイプ */
static int AddToken(TOKEN *token, char *buf, int len);

/* トークンの切り出し */
int GetToken(char *buf, int len, TOKEN *token, char *token_separate, char *token_separate_point){
  int token_len;
  char *ptr;
  char *ptr2;
  char *token_start;
  char point[10];
  char qt;

  token->token = NULL;
  token->size = 0;
  token->no = 0;
  token_start = buf;
  for(ptr = buf; ptr < buf+len; ptr++){
    /* SJIS漢字1バイト目、エスケープ */
    if(issjiskanji(*ptr) || *ptr == '\\'){
      ptr++;
    }else if(*ptr == '"' || *ptr == '\''){  /* "",''文字列 */
      qt = *ptr;
      for(ptr2 = ptr + 1; ptr2 < buf + len; ptr2++){
        /* SJIS漢字1バイト目、エスケープ */
        if(issjiskanji(*ptr2) || *ptr2 == '\\'){
          ptr2++;
          continue;
        }
        if(*ptr2 == qt){
          break;
        }
      }
      ptr = ptr2;
    }else if(strchr(token_separate, *ptr) != NULL){ /* 分離文字 */
      token_len = ptr - token_start;
      if(token_len > 0){
        AddToken(token, token_start, token_len);
      }
      token_start = ptr + 1;
    }else if(strchr(token_separate_point, *ptr) != NULL){
      token_len = ptr - token_start;
      if(token_len > 0){
        AddToken(token, token_start, token_len);
      }
      sprintf(point, "%c", *ptr);
      AddToken(token, point, 1);
      token_start = ptr + 1;
    }
  }
  token_len = ptr - token_start;
  if(token_len > 0){
    AddToken(token, token_start, token_len);
  }

  return(0);
}

/* トークンデータ追加 */
static int AddToken(TOKEN *token, char *buf, int len){
  int pack_flag;
  pack_flag = 0;
  
  if(buf[0] == '"' && buf[len-1] == '"'){
    pack_flag = 1;
  }else if(buf[0] == '\'' && buf[len-1] == '\''){
    pack_flag = 1;
  }

  if(token->size == 0){
    token->size = TOKEN_ALLOC_SIZE;
    token->token = (char **)malloc(token->size * sizeof(char *));
    if(token->token == NULL){
      SyslogPerror(LOG_ERR, "malloc");
      Syslog(LOG_ERR, "token.c:AddToken():malloc(%d):NULL\n", token->size * sizeof(char *));
      return(-1);
    }
  }else if(token->no + 1 >= token->size){
    token->size += TOKEN_ALLOC_SIZE;
    token->token = (char **)realloc((char *)token->token, token->size * sizeof(char *));
    if(token->token == NULL){
      SyslogPerror(LOG_ERR, "realloc");
      Syslog(LOG_ERR, "token.c:AddToken():realloc(%x, %d):NULL\n", (char *)token->token, token->size * sizeof(char *));
      return(-1);
    }
  }

  token->token[token->no] = malloc(len + 1);
  if(token->token[token->no] == NULL){
    SyslogPerror(LOG_ERR, "malloc");
    Syslog(LOG_ERR, "token.c:AddToken():token->token[%d]:malloc(%d):NULL\n", token->no, len + 1);
    return(-1);
  }
  if(pack_flag == 0){
    memcpy(token->token[token->no], buf, len);
    token->token[token->no][len] = '\0';
  }else{
    memcpy(token->token[token->no], buf + 1, len - 2);
    token->token[token->no][len - 2] = '\0';
  }
  token->no++;

  return(0);
}

/* トークンデータ解放 */
int FreeToken(TOKEN *token){
  int i;

  for(i = 0; i < token->no; i++){
    free(token->token[i]);
  }
  if(token->size > 0){
    free(token->token);
  }
  token->token = NULL;
  token->size = 0;
  token->no = 0;

  return(0);
}

/* 文字列を小文字に */
int CharSmall(char *buf){
  char *ptr;
  
  for(ptr = buf; *ptr != '\0'; ptr++){
    if(issjiskanji(*ptr)){
      ptr++;
      continue;
    }
    *ptr = tolower(*ptr);
  }
  return(0);
}

/* 大文字小文字無視文字列比較関数 */
int StrCmp(char *a, char *b){
  char *aa;
  char *bb;
  int ret;

  aa = strdup(a);
  if(aa == NULL){
    Syslog(LOG_ERR, "strdup");
    Syslog(LOG_ERR, "token.c:StrCmp():strdup(%s):NULL\n", a);
    return(strcmp(a, b));
  }
  CharSmall(aa);
  bb = strdup(b);
  if(bb == NULL){
    Syslog(LOG_ERR, "strdup");
    Syslog(LOG_ERR, "token.c:StrCmp():strdup(%s):NULL\n", b);
    free(aa);
    return(strcmp(a, b));
  }
  CharSmall(bb);

  ret = strcmp(aa, bb);

  free(aa);
  free(bb);

  return(ret);
}

/* 大文字小文字無視・長さ指定文字列比較関数 */
int StrNCmp(char *a, char *b, int n){
  char *aa;
  char *bb;
  int ret;

  aa = strdup(a);
  if(aa == NULL){
    Syslog(LOG_ERR, "strdup");
    Syslog(LOG_ERR, "token.c:StrNCmp():strdup(%s)=NULL\n", a);
    return(strncmp(a, b, n));
  }
  CharSmall(aa);
  bb = strdup(b);
  if(bb == NULL){
    Syslog(LOG_ERR, "strdup");
    Syslog(LOG_ERR, "token.c:StrNCmp():strdup(%s):NULL\n", b);
    free(aa);
    return(strncmp(a, b, n));
  }
  CharSmall(bb);

  ret = strncmp(aa, bb, n);

  free(aa);
  free(bb);

  return(ret);
}

/* 文字列CRLF削除 */
int CutCrLf(char *str){
  char *ptr;

  if((ptr = strchr(str, '\r')) != NULL){
    *ptr = '\0';
  }else if((ptr = strchr(str, '\n')) != NULL){
    *ptr = '\0';
  }

  return(0);
}
