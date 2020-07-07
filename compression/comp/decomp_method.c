static void selectDecompMethod(comp_t *paramsPtr){
  switch(paramsPtr->event){
    case RUNLENGTH_STD:
      decompRunLengthStd(paramsPtr);
      break;
    case RUNLENGTH_1BYTE_SIGN:
      decompRunLength1ByteSign(paramsPtr);
      break;
    case RUNLENGTH_HEAD1BIT_SIGN:
      decompRunLengthHead1BitSign(paramsPtr);
      break;
    case WYLE_CODING:
      decompWyleCoding(paramsPtr);
      break;
    case PACKBITS_STD:
      decompPackBitsStd(paramsPtr);
      break;
    case PACKBITS_SWITCH:
      decompPackBitsSwitch(paramsPtr);
      break;
    default:
      break;
  }
}

/* list1-7 方法A */
int decompRunLengthStd(comp_t *paramsPtr){
  int i;
  int code;
  int length;

  while(1){
    length = fgetc(paramsPtr->fp_i);
    if(length == EOF){
      break;
    }
    code = fgetc(paramsPtr->fp_i);
    if(code == EOF){
      return 0; //エラー
    }
    for(i = 0; i < length; i++){
      fputc(code, paramsPtr->fp_o);
    }
  }
  return 1;
}

/* list1-8 方法B */
int decompRunLength1ByteSign(comp_t *paramsPtr){
  int i;
  int length;
  int value;
  int runlengthFlag;

  runlengthFlag = RUNLENGTH_FLAG;

  while(1){
    value = fgetc(paramsPtr->fp_i);
    if(value == EOF){
      break;
    }

    if(value == runlengthFlag){
      length = fgetc(paramsPtr->fp_i);
      if(length == EOF){
        return 0; //エラー
      }
      code = fgetc(paramsPtr->fp_i);
      if(code == EOF){
        return 0; //エラー
      }
      for(i = 0; i < length; i++){
        fputc(code, paramsPtr->fp_o);
      }
    }else{
      fputc(value, paramsPtr->fp_o);
    }
  }
  return 1;
}

/* list1-9 方法C */
int decompRunLengthHead1BitSign(comp_t *paramsPtr){
  int i;
  int length;
  int code;
  int value;

  while(1){
    value = fgetc(paramsPtr->fp_i);
    if(value == EOF){
      break;
    }
    if(value >= 0x80){
      length = value & 0x7f;
      code = fgetc(fp_i);
      if(code == EOF){
        return 0; //エラー
      }
      for(i = 0; i < length; i++){
        fputc(code, paramsPtr->fp_o);
      }
    }else{
      fputc(value, paramsPtr->fp_o);
    }
  }
  return 1;
}

/* list1-10 方法D */
int readData(unsigned char *data, int length, FILE *fp){
  return fread(data, length, sizeof(char), fp);
}

int fgetLong(FILE *fp){
  unsigned char buf[16];

  readData(buf, 4, fp);
  return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

int fgetBitInit(wyle_t *wylePtr){
  wylePtr->bits = 0;
  wylePtr->bdata = 0;
}

int fgetBit(FILE *fp, wyle_t *wylePtr){
  unsigned char bbuf;
  unsigned char buf[16];
  int val;

  if(wylePtr->bits == 0){
    readData(&bbuf, 1, fp);
    wylePtr->bdata = bbuf;
  }
  val = (wylePtr->bdata >> 7) & 1;
  wylePtr->bdata = (wylePtr->bdata << 1) & 0xff;
  wylePtr->bits++;
  if(wylePtr->bits >= 8){
    wylePtr->bits = 0;
    wylePtr->bdata = 0;
  }

  return val;
}

int freadWyleCode(FILE *fp, wyle_t *wyleptr){
  int sbit;
  int bit;
  int i;
  int cnt;
  int val;

  cnt = 0;
  while(fgetBit(fp, wylePtr) == 1){
    cnt++;
  }
  cnt += 2;
  val = 0;
  for(i = 0; i < cnt; i++){
    bit = fgetBit(fp, wylePtr) << i;
    val |= bit;
  }

  return val + 1;
}

int fgetBits(int n, FILE *fp, wyle_t *wylePtr){
  int i;
  int answer;

  answer = 0;

  for(i = 0; i < n; i++){
    answer *= 2;
    answer += fgetBit(fp, wylePtr);
  }

  return answer;
}

int decompWyleCoding(comp_t *paramsPtr){
  int i;
  int point;
  int datasize;
  int code;
  int length;
  wyle_t wyleParams;

  datasize = fgetLong(paramsPtr->fp_i);
  point = 0;
  fgetBitInit(&wyleParams);
  while(point < datasize){
    length = freadWyleCode(paramsPtr->fp_i, &wyleParams);

    code = fgetBits(8, paramsPtr->fp_i, &wyleParams);
    for(i = 0; i < length; i++){
      fputc(code, paramsPtr->fp_o);
    }
    point += length;
  }
  return 1;
}

/* list1-11 方法E */
int decompPackBitsStd(comp_t *paramsPtr){
  
}

/* list1-12 方法F */
int decompPackBitsSwitch(comp_t *paramsPtr){
  
}
