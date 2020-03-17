#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

int decodeData(FILE *fp_i, FILE *fp_o);

//---

// ファイルからlengthバイトだけデータを取り出して、dataに格納する
// (APIの違いに対応するためのカプセル関数)
int readData(unsigned char *data, int length, FILE *fp){
  return fread(data, length, sizeof(char), fp);
}

// ファイルからlongデータを取り出す
int fgetLong(FILE *fp){
  unsigned char buf[16];

  readData(buf, 4, fp);
  return (buf[0]<<24) | (buf[1]<<16) | (buf[2]<<8) | buf[3];
}

static int bits = 0;
static int bdata = 0;

//----ビット単位でのファイル入力を行う----
// *利用方法
// 1)最初にfgetBitInitを呼び出す
// 2)fgetBitでデータを読み出す

int fgetBitInit(){
  bits = 0;
  bdata = 0;
}

// 1ビット入力
int fgetBit(FILE *fp){
  unsigned char bbuf;
  unsigned char buf[16];
  int val;

  if(bits == 0){
    readData(&bbuf, 1, fp);
    bdata = bbuf;
  }
  val = (bdata >> 7)&1;
  bdata = (bdata<<1) & 0xff;
  bits++;
  if(bits >= 8){
    bits = 0;
    bdata = 0;
  }
  return val;
}
//---

// ワイル符号化のデータを読み出す
int freadWyleCode(FILE *fp){
  int sbit, bit;
  int i, cnt;
  int val;

  cnt = 0;
  while(fgetBit(fp) == 1){
    cnt++;
  }
  cnt += 2;
  val = 0;
  for(i = 0; i < cnt; i++){
    bit = fgetBit(fp) << i;
    val |= bit;
  }
  // if(sbit == 0) val = -val;
  return val + 1;
}

// ファイルからnビット入力する
int fgetBits(int n, FILE *fp){
  int i;
  int answer = 0;

  for(i = 0; i < n; i++){
    answer *= 2;
    answer += fgetBit(fp);
  }
  return answer;
}

int main(int ac, char *av[]){
  FILE *fp_i, *fp_o;

  if(ac < 3){
    exit(8);
  }
  fp_i = fopen(av[1], "rb");
  if(fp_i == NULL){
    fprintf(stderr, "Input File cannot open\n");
    exit(8);
  }

  // 伸張処理する
  fp_o = fopen(av[2], "wb");
  if(fp_o == NULL){
    fprintf(stderr, "Output File cannot open\n");
    exit(8);
  }
  decodeData(fp_i, fp_o);
  fclose(fp_i);
  fclose(fp_o);
}


/*
  fp_iで指定されるファイルデータをランレングス符号化による圧縮結果とし、
  それを伸張して、結果をfp_oで指定されるファイルに出力する
*/
int decodeData(FILE *fp_i, FILE *fp_o){
  int i;
  int point, datasize;
  int code;
  int length;

  datasize = fgetLong(fp_i);
  point = 0;
  fgetBitInit();
  while(point < datasize){
    length = freadWyleCode(fp_i);

    code = fgetBits(8, fp_i);
    for(i = 0; i < length; i++){
      fputc(code, fp_o);
    }
    point += length;
  }
  return 1;
}
