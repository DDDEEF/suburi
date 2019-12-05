#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

/* ソースがSJISの場合SJISを定義する */
#ifndef SJIS
#define iseuckanji(c)   (0xa1 <= (unsigned char)(c&0xff) && (unsigned char)(c&0xff) <= 0xfe)
#define iseuckana(c)    (0x8e == (unsigned char)(c&0xff))
#define iskanji(c)      (iseuckanji(c)||iseuckana(c))
#else
#define issjiskanji(c)  ((0x81 <= (unsigned char)(c&0xff) && (unsigned char)(c&0xff) <= 0x9f) || (0xe0 <= (unsigned char)(c&0xff) && (unsigned char)(c&0xff) <= 0xfc))
#define issjiskana(c)   ((0xa1 <= (unsigned char)(c&0xff) && (unsigned char)(c&0xff) <= 0xdf))
#define iskanji(c)      (issjiskanji(c))
#endif

#ifdef SJIS
#define issjiskanji(c) ((0x81 <= (unsigned char)(c&0xff) && (unsigned char)(c&0xff) <= 0x9f) || (0xe0 <= (unsigned char)(c&0xff) && (unsigned char) (c&0xff) <= 0xfc))
#else
#define issjiskanji(c) 0
#endif

#define TOKEN_ALLOC_SIZE (128)

char *Buffer;

/* トークンデータ */
typedef struct {
  char **token;
  int size;
  int no;
}TOKEN;

/* トークンデータを追加 */
int AddToken(TOKEN *token, char *buf, int len){
  int pack_flag;
  pack_flag = 0;

  if((buf[0] == '"') && (buf[len-1] == '"')){
    pack_flag = 1;
  }else if((buf[0] == '\'') && (buf[len-1] == '\'')){
    pack_flag = 1;
  }

  if(token->size == 0){
    token->size = TOKEN_ALLOC_SIZE;
    token->token = (char **)malloc(token->size * sizeof(char *));
    token->token[token->no] = malloc(len+1);
    if(pack_flag == 0){
      memcpy(token->token[token->no], buf, len);
      token->token[token->no][len] = '\0';
    }else{
      memcpy(token->token[token->no], buf+1, len-2);
      token->token[token->no][len-2] = '\0';
    }
    token->no++;
  }else{

    if(token->no+1 >= token->size){
      token->size = TOKEN_ALLOC_SIZE;
      token->token = (char **)realloc((char *)token->token, token->size * sizeof(char *));
    }
    
    token->token[token->no] = malloc(len+1);
    if(pack_flag == 0){
      memcpy(token->token[token->no], buf, len);
      token->token[token->no][len] = '\0';
    }else{
      memcpy(token->token[token->no], buf+1, len-2);
      token->token[token->no][len-2] = '\0';
    }
    token->no++;
  }
  return(0);
}

/* トークンデータを解放 */
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

/* トークンの切り出し */
int GetToken(char *buf, int len, TOKEN *token, char *token_separate, char *token_separate_point){
  int token_start, token_len;
  int i, j;
  char point[10];

  token->token = NULL;
  token->size = 0;
  token->no = 0;

  token_start = 0;
  for(i = 0; i < len; i++){
    /* SJIS漢字1バイト目かエスケープ*/
    if((issjiskanji(buf[i])) || (buf[i] == '\\')){
      i++;
    }else if(buf[i] == '"'){  /* "文字列 */
      for(j = i + 1; j < len; j++){
        /* SJIS漢字1バイト目かエスケープ */
        if(issjiskanji((buf[j])) || (buf[j] == '\\')){
          continue;
        }
        if(buf[j] == '"'){
          break;
        }
      }
      i = j;
    }else if(buf[i] == '\''){ /* '文字列 */
      for(j = i + 1; j < len; j++){
        /* SJIS漢字1バイト目かエスケープ */
        if((issjiskanji(buf[j])) || (buf[j] == '\\')){
          continue;
        }
        if(buf[j] == '\''){
          break;
        }
      }
      i = j;
    }else if(strchr(token_separate, buf[i]) != NULL){ /* 分離文字 */
      token_len = i - token_start;
      if(token_len > len > 0){
        AddToken(token, &buf[token_start], token_len);
      }
      token_start = i + 1;
    }else if(strchr(token_separate_point, buf[i]) != NULL){ /* 区切り分離文字 */
      token_len = i - token_start;
      if(token_len > 0){
        AddToken(token, &buf[token_start], token_len);
      }
      sprintf(point, "%c", buf[i]);
      AddToken(token, point, 1);
      token_start = i + 1;
    }
  }
  token_len = i - token_start;
  if(token_len > 0){
    AddToken(token, &buf[token_start], token_len);
  }
  return(0);
}

/* トークンデータデバッグ用 */
int DebugToken(FILE *fp, TOKEN *token){
  int i;
  char buf[512];

  for(i = 0; i < token->no; i++){
    sprintf(buf, "[%s]", token->token[i]);
    fprintf(fp, "%s", buf);
  }
  fprintf(fp, "\r\n");
  return(0);
}

/* 名前:値 形式の切り出し */
int GetNameVal(char *buf, int len, char *name, char *val, char *sep){
  int name_flag;
  int i, next;

  strcpy(name, "");
  strcpy(val, "");

  name_flag = 0;
  for(i = 0; i < len; i++){
    if(issjiskanji(buf[i])){
      i++;
      continue;
    }else if(strchr(sep, buf[i]) != NULL){
      name_flag = 1;
      strncpy(name, buf, i);
      name[i] = '\0';
      next = i + 1;
      break;
    }
  }

  if(name_flag == 0){
    return(0);
  }

  for(i = next; i < len; i++){
    if((!(isascii(buf[i]))) && (isspace(buf[i]))){
      next = i;
      break;
    }
  }

  strcpy(val, &buf[next]);

  return(1);
}

/* 文字列を小文字に */
int CharSmall(char *buf){
  char *ptr;
  for(ptr = buf; *ptr != '\0'; ptr++){
    *ptr = tolower(*ptr);
  }
  return(0);
}

/* 文字列CRLFを削除 */
int CutCrLf(char *str){
  char *ptr;
  if((ptr = strchr(str, '\r')) != NULL){
    *ptr = '\0';
  }else if((ptr = strchr(str, '\n')) != NULL){
    *ptr = '\0';
  }

  return(0);
}

/* 大文字小文字無視文字列比較 */
int StrCmp(char *a, char *b){
  char *aa, *bb;
  int ret;

  aa = strdup(a);
  CharSmall(aa);
  bb = strdup(b);
  CharSmall(bb);

  ret = strcmp(aa, bb);

  free(aa);
  free(bb);

  return(ret);
}

/* 行番号の取得 */
int LineNo(char *adr){
  char *ptr;
  int line;

  line = 1;

  for(ptr = Buffer; *ptr != '\0'; ptr++){
    if(ptr == adr){
      break;
    }

    if(iskanji(*ptr)){
      ptr++;
      if(ptr == adr){
        break;
      }
      continue;
    }

    if(*ptr == '\n'){
      line++;
    }
  }
  return(line);
}

/* ファイル全体をバッファに読み込み */
int ReadFile(char *file, char **buf){
  FILE *fp;
  struct stat st;

  if((fp = fopen(file, "r")) == NULL){
    perror("fopen");
    return(-1);
  }

  if(fstat(fileno(fp), &st) != 0){
    perror("fstat");
    fclose(fp);
    return(-1);
  }

  if(((*buf) = (char *)calloc(st.st_size+1, sizeof(char))) == NULL){
    perror("calloc");
    fclose(fp);
    return(-1);
  }

  fread((*buf), st.st_size, sizeof(char), fp);
  fclose(fp);
  return(0);
}

/* 指定文字列までスキップ */
char *Skip(char *buf, char *sep){
  char *ptr;
  int sep_len;

  sep_len = strlen(sep);
  
  for(ptr = buf; *ptr != '\0'; ptr++){
    /* 漢字1バイト目 */
    if(iskanji(*ptr)){
      ptr++;
      continue;
    }

    /* エスケープ */
    if(*ptr == '\\'){
      ptr++;
      continue;
    }

    /* 指定文字列 */
    if(strncmp(ptr, sep, sep_len) == 0){
      return(ptr + sep_len - 1);
    }
  }

  fprintf(stderr, "%d 行目:指定文字列(%s)までスキップできない\n", LineNo(buf), sep);
  return(NULL);
}

/* 対応する'}'までスキップ */
char *SkipKakko(char *buf){
  char *ptr;

  for(ptr = buf; *ptr != '\0'; ptr++){
    /* 漢字1バイト目 */
    if(iskanji(*ptr)){
      ptr++;
      continue;
    }
    
    /* 対応する'}' */
    if(*ptr == '}'){
      return(ptr);
    }

    switch(*ptr){
      /* エスケープ */
      case '\\' :
        ptr++;
        break;
      /* コメントアウト */
      case '/' :
        if(*(ptr+1) == '*'){
          ptr = Skip(ptr+1, "*/");
        }else{
          ptr = ptr;
        }
        break;
      /* 文字列 */
      case '"' :
        ptr = Skip(ptr+1, "\"");
        break;
      /* 文字 */
      case '\'' :
        ptr = Skip(ptr+1, "'");
        break;
      /* 構造 */
      case '{' :
        ptr = SkipKakko(ptr+1);
        break;
      default :
        break;
    }
    if(ptr == NULL){
      break;
    }
  }
  fprintf(stderr, "%d 行目:対応する'}'が見つからない\n", LineNo(buf));
  return(NULL);
}

/* プロトタイプ出力 */
int ProtoPrint(char *buf, int len){
  TOKEN token;
  int i;
  int ansii;

  GetToken(buf, len, &token, "\b\t\r\n", ",()");

  if(strcmp(token.token[token.no-1], ")") == 0){
    ansii = 1;
  }else{
    ansii = 0;
  }

  for(i = 0; i < token.no; i++){
    printf("%s", token.token[i]);
    if((ansii == 0) && (strcmp(token.token[i], "(") == 0)){
      /* K&Rの場合は引数を出さない */
      printf(")");
      break;
    }

    if((i != token.no-1) && (strcmp(token.token[i],"(") != 0) && (strcmp(token.token[i], ",") != 0)){
      if((strcmp(token.token[i+1], "(") != 0) && (strcmp(token.token[i+1], ",") != 0) && (strcmp(token.token[i+1], ")") != 0)){
        printf(" ");
      }
    }
  }
  printf(";\n");

  FreeToken(&token);
  return(0);
}

/* 関数の処理 */
char *Function(char *start, char *kakko){
  int len;
  char *ptr;

  len = kakko - start;

  ProtoPrint(start, len);

  for(ptr = kakko+1; *ptr != '\0'; ptr++){
    /* 漢字1バイト目 */
    if(iskanji(*ptr)){
      ptr++;
      continue;
    }

    /* スペース */
    if((isascii(*ptr)) && isspace(*ptr)){
      continue;
    }

    /* 関数の終り */
    if(*ptr == '}'){
      return(ptr);
    }

    switch(*ptr){
      /* エスケープ */
      case '\\' :
        ptr++;
        break;
      /* コメントアウト */
      case '/' :
        if(*(ptr+1) == '*'){
          ptr = Skip(ptr+1, "*/");
        }else{
          ptr = ptr;
        }
        break;
      /* 文字列 */
      case '"' :
        ptr = Skip(ptr+1, "\"");
        break;
      /* 文字 */
      case '\'' :
        ptr = Skip(ptr+1, "'");
        break;
      /* 構造 */
      case '{' :
        ptr = SkipKakko(ptr+1);
        break;
      default :
        break;
    }
    if(ptr == NULL){
      break;
    }
  }
  fprintf(stderr, "%d行目:対応する'}'が見つからない\n", LineNo(kakko));
  return(NULL);
}

/* 関数かどうかの解析 */
char *Analize(char *buf){
  char *ptr;
  char *kakko_close;
  int arg_kakko;

  /* デファインなど */
  if(buf[0] == '#'){
    ptr = Skip(buf+1, "\n");
    return(ptr);
  }

  arg_kakko = 0;

  for(ptr = buf; *ptr != '\0'; ptr++){
    /* 漢字1バイト目 */
    if(iskanji(*ptr)){
      ptr++;
      continue;
    }

    switch(*ptr){
      /* エスケープ */
      case '\\' :
        ptr++;
        break;
      /* コメントアウト */
      case '/' :
        if(*(ptr+1) == '*'){
          ptr = Skip(ptr+1, "*/");
        }
        break;
      /* 文字列 */
      case '"' :
        ptr = Skip(ptr+1, "\"");
        break;
      /* 文字 */
      case '\'' :
        ptr = Skip(ptr+1, "'");
        break;
      /* ( */
      case '(' :
        /* 次の'('が出てきたので、')'まで戻ってやり直し */
        if(arg_kakko == 2){
          return(kakko_close);
        /* '('が2回出てきたのでエラー */
        }else if(arg_kakko == 1){
          fprintf(stderr, "%d行目:'('が2回登場:エラー\n", LineNo(ptr));
          return(NULL);
        }
        arg_kakko = 1;
        break;
      /* 閉じた場所を記憶 */
      case ')' :
        kakko_close = ptr;
        arg_kakko = 2;
        break;
      case ';' :
        /* 関数ではない */
        if(arg_kakko == 0){
          return(ptr);
        }
        break;
      case '{' :
        /* 構造 */
        if(arg_kakko == 0){
          ptr = SkipKakko(ptr+1);
          return(ptr);
        /* 関数 */
        }else{
          ptr = Function(buf, ptr);
          return(ptr);
        }
        break;
      default :
        break;
    }
    if(ptr == NULL){
      break;
    }
  }
  return(NULL);
}

/* プロトタイプ出力メイン関数 */
int mkproto(char *file){
  char *ptr;
  char *buf;

  fprintf(stderr, "%s を処理\n", file);

  /* ファイル読み込み */
  if(ReadFile(file, &Buffer) == -1){
    return(-1);
  }

  buf = Buffer;

  /* ファイル名を出力 */
  printf("/* %s */\n", file);

  for(ptr = buf; *ptr != '\0'; ptr++){
    /* 漢字1バイト目 */
    if(iskanji(*ptr)){
      ptr++;
      continue;
    }

    /* スペース */
    if((isascii(*ptr)) && (isspace(*ptr))){
      continue;
    }

    switch(*ptr){
      /* エスケープ */
      case '\\' :
        ptr++;
        break;
      /* コメントアウト */
      case '/' :
        if(*(ptr+1) == '*'){
          ptr = Skip(ptr+1, "*/");
        }
        break;
      /* 文字列 */
      case '"' :
        ptr = Skip(ptr+1, "\"");
        break;
      /* 文字 */
      case '\'' :
        ptr = Skip(ptr+1, "'");
        break;
      /* 関数かどうかの解析 */
      default:
        ptr = Analize(ptr);
        break;
    }
    if(ptr == NULL){
      break;
    }
  }
  free(Buffer);
  return(0);
}

int main(int argc, char *argv[]){
  int i;

  if(argc <= 1){
    fprintf(stderr, "mkproto file [file ...]\n");
    return(-1);
  }

  for(i = 1; i < argc; i++){
    mkproto(argv[i]);
  }

  return(0);
}
