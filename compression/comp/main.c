#include "main.h"

static void printMenu(void);
static void selectCompMethdo();

int main(void){
  char input[] = "/home/vagrant/tmp/input/test.jpg";
  char output[] = "/home/vagrant/tmp/output/test";
  FILE *fp_i;
  FILE *fp_o;
  int datasize;
  int c;
  unsigned char buffer[BUFFER_SIZE];
  char str[8];
  comp_t compParams;

  printMenu();

  fgets(str, sizeof(str), stdin);
  val = atoi(str);

  fp_i = fopen(input, "rb");
  if(fp_i == NULL){
    fprintf(stderr, "Input File cannot opne.\n");
    exit(8);
  }

  datasize = 0;
  while(datasize < BUFFER_SIZE && (c=fgetc(fp_i)) != EOF){
    buffer[datasize] = c;
    datasize++;
  }
  fclose(fp_i);

  fp_o = fopen(output, "wb");
  if(fp_o == NULL){
    fprintf(stderr, "Output File cannot open.\n");
    exit(8);
  }

  compParams.fp = fp_o;
  compParams.data = buffer;
  compParams.size = datasize;
  compParams.event = val;

  selectCompMethod(&compParams);
}

static void printMenu(void){
  printf("-------------------圧縮・伸張プログラム-------------------\n");
  printf("好きなアルゴリズムで圧縮してください\n");
  printf("[0] ランレングス符号化A 単純にデータをラン長+データ値で圧縮します。\n");
  printf("[1] ランレングス符号化B 二つ以上続くデータ値のみラン長として符号化します。\n");
  printf("[2] ランレングス符号化C ラン長の1bit目でランレングス符号の始まりを示すように符号化します。\n");
  printf("[3] ワイル符号化 符号の先頭に0で終わる1の並びによって、ラン長を示すビット数を決定します。\n");
  printf("[4] PackBits ラン長を示す数が正のとき、同じデータ値が並び、負のとき、違いデータ値が並んでるとして、圧縮します。\n");
  printf("[5] PackBits 同じデータ値が連続して並ぶとき、違うデータ値が連続して並ぶときは間にラン長0があるとして圧縮します。\n");
}

static void selectCompMethod(comp_t *paramsPtr){
  switch(paramsPtr->event){
    case RUNLENGTH_STD:
      compRunLengthStd(paramsPtr);
      break;
    case RUNLENGTH_1BYTE_SIGN:
      compRunLength1ByteSign(paramsPtr);
      break;
    case RUNLENGTH_HEAD1BIT_SIGN:
      compRunLengthHead1BitSign(paramsPtr);
      break;
    case WYLE_CODING:
      compWyleCoding(paramsPtr);
      break;
    case PACKBITS_STD:
      compPackBitsStd(paramsPtr);
      break;
    case PACKBITS_SWITCH:
      compPackBitsSwitch(paramsPtr);
      break;
    default:
      break;
  }
}
