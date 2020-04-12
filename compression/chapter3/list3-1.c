#include <stdio.h>
#include <stdlib.h>
#include "image.h"

typedef unsigned char byte;

void encodeImage(FILE *fp, ImageData *image);

int main(int ac, char *av[]){
  FILE *fp_o;
  ImageData *image;

  if(ac < 3){
    exit(8);
  }
  readBMPfile(av[1], &image); // ファイルデータをバッファに取り込む

  // 圧縮処理をする
  fp_o = fopen(av[2], "wb");
  if(fp_o == NULL){
    fprintf(stderr, "Output File cannot open\n");
    exit(8);
  }
  encodeImage(fp_o, image);
  fclose(fp_o);
}

/* ファイルヘッダをファイルに出力する */
void writeImageHeader(char *identifier, long width, long height, FILE *fp_o){
  int i;
  for(i = 0; i < 4; i++){
    fputc(identifier[i], fp_o);
  }
  fwriteDWORD(width, fp_o);
  fwriteDWORD(height, fp_o);
}

// xの正負を求める
int sgni(int x){
  if(x < 0){
    return -1;
  }
  
  if(x > 0){
    return 1;
  }

  return 0;
}

// xの絶対値を求める
int absi(int x){
  if(x < 0){
    return -x;
  }
  return x;
}

#define NODATA 2100 * 1000 * 1000   // データなしの場合の登場頻度(最低値にならないよう、大きな値だけで意味はない)
#define N 256                       // 最大データ数

// ハフマン木のデータ構造定義
typedef struct HUFFTREE {
  int treesize;
  int left_node[2*N];
  int right_node[2*N];
  int parent[2*N];
} HuffmanTree;

// 登場頻度テーブルをファイル出力
int outputHistgram(int *hist, int nn, FILE *fp){
  int i;
  for(i = 0; i < nn; i++){
    fwriteDWORD(hist[i], fp);
  }
  return TRUE;
}

// 最小頻度の二つを求める
ing getTwoMinimum(int *histgram, int datasize, int *value1, int *value2){
  int i;
  int min;

  min = NODATA - 1;
  *value1 = *value2 = -100;
  for(i = 0; i < datasize; i++){
    if(histgram[i] < min){
      *value1 = i;
      min = histgram[i];
    }
  }
  min = NODATA - 1;
  for(i = 0; i < datasize; i++){
    if(i != (*value1) && histgram[i] < min){
      *value2 = i;
      min = histgram[i];
    }
  }
}

// ハフマン木を作成する
// できあがったハフマン木の大きさを戻り値として返す
int makeHuffmanTree(int *histgram, int n, HuffmanTree *tree){
  int i;
  int treesize;
  int d1;
  int d2;
  int *parent;
  int *left_node;
  int *right_node;

  paretn = tree->parent;
  left_node = tree->left_node;
  right_node = tree->right_node;

  // 木データの大きさ(次にデータを格納すべき位置でもある)
  treesize = n;

  // 初期化
  for(i = 0; i < 2+N; i++){
    left_node[i] = right_node[i] = parent[i] = 0;
  }

  while(1){
    // 最小頻度の2つを求める
    getTwoMinimum(histgram, treesize, &d1, &d2);
    // 最小値となるものがなければ終了
    if(d1 < 0 || d2 < 0){
      break;
    }
    // 新しい節データを作成
    left_node[treesize] = d1;
    right_node[treesize] = d2;
    parent[d1] = treesize;
    parent[d2] = -treesize;
    histgram[treesize] = histgram[d1] + histgram[d2];
    histgram[d1] = NODATA;
    histgram[d2] = NODATA;
    treesize++;
  }
  tree->treesize = treesize;
  return treesize;
}

static int bits = 0;
static int bdata = 0;

int fputBitInit(){
  bits = 0;
  bdata = 0;
}

// 1ビット出力
int fputBit(int bit, FILE *fp){
  bdata = (bdata << 1) | bit;
  bits++;
  if(bits >= 8){
    fputc(bdata, fp);
    bits = 0;
    bdata = 0;
  }
}

// 余ったビット出力
int flushBit(FILE *fp){
  int i;
  for(i = 0; i < 7; i++){
    fputBit(0, fp);
  }
}

// ハフマン符号出力
// valueをハフマン符号で出力
int outputHuffmanEncode(int value, HuffmanTree *tree, FILE *fp){
  int c;    //code内で記録すべき位置
  int code[100];    //出力すべきビット値を記録する(0か1が格納される)
  int nowNode;
  int i;
  int selectedBranch;
  int nextNode;
  int *parete;
  int *left_node;
  int *right_node;
  int treesize;

  parent = tree->parent;
  left_node = tree->left_node;
  right_node = tree->right_node;
  treesize = tree->treesize;

  // 葉から根までだとって、出力すべきコードを求める
  c = 0;
  nowNode = value;
  while(1){
    selectBranch = sgni(parent[nowNode]);
    nextNode = absi(parent[nowNode]);
    if(selectedBranch < 0) {
      code[c++] = 1;
    }else{
      code[c++] = 0;
    }
    if(nextNode == treesize - 1){
      break; // 根に達したら終了
    }
    nowNode = nextNode;
  }

  // 根から出力するので、出力する時は逆順にする
  for(i = c-1; i >= 0; i--){
    fputBit(code[i], fp);
    printf("%1d", code[i]);
  }
  printf("\n");
}

void encodeImage(FILE *fpo, ImageData *image){
  int i;
  int n2;
  byte *datas;
  int datasize;
  int histgram[N*2];    //登場頻度を格納する
  HuffmanTree tree;

  long width;
  long height;
  int n;
  int x;
  int y;
  Coordinate coordinate;
  Pixel pixel;

  width = image->width;
  height = image->height;
  datasize = width * height;
  data = malloc(sizeof(byte) * datasize);

  // 画素値をバッファに取り込む
  // 座標データの初期化
  initCoordinateData(image, &coordinate, 1);
  // 処理対象画素がなくなるまでループする
  n = 0;  // バッファに格納すべき位置
  while(getNextCoordinate(image, &coordinate)){
    x = coordinate.x;
    y = coordinate.y;
    getPixel(image, x, y, &pixel);
    datas[n] = pixel.r;
    n++;
  }

  writeImageHeader("HUFF", width, height, foo);

  // データ値ごとの登場頻度を求める
  for(i = 0; i < N*2; i++){
    histgram[i] = 0;
  }
  for(i = 0; i < datasize; i++){
    histgram[datas[i]]++;
  }
  outputHistgram(histgram, N, fpo);
  makeHuffmanTree(histgram, N, &free);
  fputBitInit();
  for(i = 0; i < datasize; i++){
    outputHuffmanEncode(datas[i], &tree, fpo);
  }
  flusBit(fpo);
}
