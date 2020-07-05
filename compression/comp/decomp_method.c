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
int decompWyleCoding(comp_t *paramsPtr){
 
}

/* list1-11 方法E */
int decompPackBitsStd(comp_t *paramsPtr){
  
}

/* list1-12 方法F */
int decompPackBitsSwitch(comp_t *paramsPtr){
  
}
