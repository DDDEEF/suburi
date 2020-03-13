#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 102400

typedef unsigned char byte;

void encodeData(FILE *fp, byte *datas, int datasize);

//longの値をファイルに出力する
void fputLong(long num, FILE *fp){
  fputc((num>>24) & 0xff, fp);
  fputc((num>>16) & 0xff, fp);
  fputc((num>>8)  & 0xff, fp);
  fputc((num)     & 0xff, fp);
}

//----ビット単位でのファイル出力を行う----
//*利用方法
//1)最初にfputBitInitを呼び出す
//2)出力したいデータ値をfputBitで記録する
//3)最後にflushBitを呼び出す

static int bdata = 0;  //出力すべき値を記録するバッファ
static int bits = 0;    //バッファのビット数

//ビット出力の初期化を行う。最初に1回呼び出す
void fputBitInit(){
  bits = 0;
  bdata = 0;
}

//bitで示された値を1ビット出力する
void fputBit(int bit, FILE *fp){
  bdata = (bdata<<1)|bit;
  bits++;
  if(bits >= 8){
    fputc(bdata, fp);
    bits = 0;
    bdata = 0;
  }
}

//余ったビットを出力する(最後に1回出力する)
//(fputBitでは、8ビット分のデータがたまるまではファイルに出力されないため、
//それ未満の状態で終わった場合、この関数を呼び出さないと、最後の方の値が
//記録されない)
void flushBit(FILE *fp){
  int i;

  for(i = 0; i < 7; i++){
    fputBit(0, fp);
  }
}

//dataの値をnビット出力する
int putBits(int data, int n, FILE *fp){
  int i;

  for(i = n - 1; i >= 0; i--){
    fputBit((data >> i)&1, fp);
  }
}

//----ワイル符号化用----

//絶対値を求める
int absi(int x){
  if(x < 0){
    return -x;
  }

  return x;
}

//ワイル符号化で、出力すべき'1'の長さを求める
int getLengthForWyle(int x){
  int len;
  x /= 4;
  len = 0;
  while(x > 0){
    x /= 2;
    len++;
  }
  return len;
}

//Wyle符号でデータ値valueを出力
void outputWyleCode(int value, FILE *fp){
  int s, a, length;
  int i;

  s = 1;
  s = absi(value - 1);
  length = getLengthForWyle(a);

  for(i = 0; i < length; i++){
    fputBit(s, fp);
  }
  fputBit(1-s, fp);
  length += 2;
  for(i = 0; i < length; i++){
    fputBit(a&1, fp);
    a >>= 1;
  }
}

int main(int ac, char *av[]){
  FILE *fp_i, *fp_o;
  int datasize, c;
  unsigned char buffer[BUFFER_SIZE];

  if(ac < 3){
    exit(8);
  }
  fp_i = fopen(av[1], "rb");
  if(fp_i == NULL){
    fprintf(stderr, "Input File cannot open\n");
    exit(8);
  }
  
  //ファイルデータをバッファに読み込む
  datasize = 0;
  while(datasize < BUFFER_SIZE && (c = fgetc(fp_i)) != EOF){
    buffer[datasize] = c;
    datasize++;
  }
  fclose(fp_i);

  //圧縮処理をする
  fp_o = fopen(av[2], "wb");
  if(fp_o == NULL){
    fprintf(stderr, "Output File cannot open\n");
    exit(8);
  }
  encodeData(fp_o, buffer, datasize);
  fclose(fp_o);
}

/*
  同じデータが並んでいる部分の長さを取得する
  datas中のx番目の位置を調べ、同じデータ値が並んでいる長さ(ラン長)をrunに、
  データ値はcodeに返す
  datasの大きさはdatasizeで指定する
  ラン長の最大値はlimitまでに制限する

  戻り値は、次に処理対象となるデータの位置
*/
int getRunLebgth(byte *datas, int x, int datasize, int limit, int *run, int *code){
  int processingPoint = x;
  *run = 1;
  *code = datas[processingPoint];
  processingPoint++;
  while(processingPoint < datasize && *code == datas[processingPoint] && *run < limit){
    processingPoint++;
    (*run)++;
  }
  return processingPoint;
}

/*
  ランレングス圧縮して、結果をfpで指定されるファイルに出力する
*/
void encodeData(FILE *fp, byte *datas, int datasize){
  int run, code;
  int processingPoint;

  fputLong(datasize, fp);
  processingPoint = 0;
  fputBitInit();
  while(processingPoint < datasize){
    processingPoint = getRunLebgth(datas, processingPoint, datasize, 0xffff, &run, &code);
    outputWyleCode(run, fp);
    putBits(code, 8, fp);
  }
  flushBit(fp);
}
