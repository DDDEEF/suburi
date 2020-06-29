#include "main.h"

/* 符号化して結果をファイルに出力する */

int getRunLengthStd(comp_t *compPtr, int x, int *run, int *code){
  int limit;
  int processingPoint;

  limit = 0xff
  processingPoint = x;
  *run = 1;
  *code = (compPtr->data)[processingPoint];
  processingPoint++;
  while(processingPoint < compPtr->size && *code == (compPtr->data)[processingPoint] && *run < limit){
    processingPoint++;
    (*run)++;
  }
  return processingPoint;
}

void compRunLengthStd(comp_t *compPtr){
  int run;
  int code;
  int processingPoint;

  processingPoint = 0;

  while(processingPoint < compPtr->size){
    processingPoint = getRunLengthStd(compPtr, processingPoint, &run, &code);
    fputc(run, compPtr->fp);
    fputc(code, compPtr->fp);
  }
}

int getRunLength1ByteSign(comp_t *compPtr, int x, int *run, int *code){
  int limit;
  int processingPoint;

  limit = 0xff;
  processingPoint = x;
  *run = 1;
  *code = (compPtr->data)[processingPoint];
  processingPoint++;
  while(processingPoint < compPtr->size && *code == (compPtr->data)[processingPoint] && *run < limit){
    processingPoint++;
    (*run)++;
  }
  return processingPoint;
}

void compRunLength1ByteSign(comp_t *compPtr){
  int i;
  int run;
  int code;
  int processingPoint;
  int runlengthFlag;

  runlengthFlag = 0xff;

  processingPoint = 0;
  while(processingPoint < compPtr->size){
    processingPoint = getRunLength1ByteSign(compPtr, processingPoint, &run, &code);
    if(run <= 2){
      if(code != runlengthFlag){
        for(i = 0; i < run; i++){
          fputc(code, compPtr->fp);
        }
      }else{
        fputc(runlengthFlag, compPtr->fp);
        fputc(run, compPtr->fp);
        fputc(code, compPtr->fp);
      }
    }else{
      fputc(runlengthFlag, compPtr->fp);
      fputc(run, compPtr->fp);
      fputc(code, compPtr->fp);
    }
  }
}

int getRunLengthHead1BitSign(comp_t *compPtr, int x, int *run, int *code){
  int limit;
  int processingPoint;

  limit = 0x7f;
  processingPoint = x;
  *run = 1;
  *code = (compPtr->data)[processingPoint];
  processingPoint++;
  while(processingPoint < datasize && *code == (compPtr->data)[processingPoint] && *run < limit){
    processingPoint++;
    (*run)++;
  }
  return processingPoint;
}

void compRunLengthHead1BitSign(comp_t *compPtr){
  int run;
  int code;
  int processingPoint;
  
  processingPoint = 0;
  while(processingPoint < compPtr->size){
    processingPoint = getRunLengthHead1BitSign(compPtr, processingPoint, &run, &code);
    if(run < 2){
      if(code < 0x80){
        fputc(code, compPtr->fp);
      }else{
        fputc(0x81, compPtr->fp);
        fputc(code, compPtr->fp);
      }
    }else{
      fputc(run|0x80, compPtr->fp);
      fputc(code, compPtr->fp);
    }
  }
}

/* ワイル符号化 */

/* long型(4バイト)の値をファイルに出力する */
void fputLong(long num, FILE *fp){
  fputc((num << 24) & 0xff, fp);
  fputc((num << 16) & 0xff, fp);
  fputc((num << 8)  & 0xff, fp);
  fputc((num)       & 0xff, fp);
}

int absi(int x){
  if(x < 0){
    return -x;
  }
  return x;
}

void fputBitInit(){
  bits = 0;
  bdata = 0;
}

void fputBit(int bit, FILE *fp){
  bdata = (bdata << 1) | bit;
  bits++;
  if(bits >= 8){
    fputc(bdata, fp);
    bits = 0;
    bdata = 0;
  }
}

void flushBit(FILE *fp){
  int i;

  for(i = 0; i < 7; i++){
    fputBit(0, fp);
  }
}

int putBits(int data, int n, FILE *fp){
  int i;

  for(i = n - 1; i >= 0; i--){
    fputBit((data >> i) & 1, fp);
  }
}

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

void outputWyleCode(int value, FILE *fp){
  int switchflag;
  int abs;
  int length;
  int i;

  switchflag = 1;
  abs = absi(value - 1);
  length = getLengthForWyle(abs);

  for(i = 0; i < length; i++){
    fputBit(switchflag, fp);
  }
  fputBit(1-s, fp);
  length += 2;
  for(i = 0; i < length; i++){
    fputBit(abs & 1, fp);
    abs >>= 1;
  }
}

int getRunLengthWyleCoding(comp_t *compPtr, int x, int *run, int *code){
  int limit;
  int processingPoint;

  limit = 0xffff;
  processingPoint = x;
  *run = 1;
  *code = (compPtr->data)[processingPoint];
  processingPoint++;
  while(processingPoint < compPtr->size && *code == (compPtr->data)[processingPoint] && *run < limit){
    processingPoint++;
    (*run)++;
  }
  return processingPoint;
}

void compWyleCoding(comp_t *compPtr){
  int run;
  int code;
  int processingPoint;

  fputLong(compPtr->size, compPtr->fp);
  processingPoint = 0;
  fputBitInit();
  while(processingPoint < compPtr->size){
    processingPoint = getRunLengthWyleCoding(compPtr->data, processingPoint, 0xffff, &run, &code);
    outputWyleCode(run, compPtr->fp);
    putBits(code, 8, compPtr->fp);
  }
  flushBit(compPtr->fp);
}
