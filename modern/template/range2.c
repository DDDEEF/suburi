int read_file(const char *pFname, int (*processor)(FILE *fp)){
  FILE *fp = fopen(pFname, "r");
  if(fp == NULL){
    return -1;
  }

  int ret = processor(fp);
  fclose(fp);
  return ret;
}

static int range_processor(FILE *fp){
  int min = INT_MAX;
  int max = INT_MIN;
  char buf[256];

  while((fgets(buf, sizeof(buf), fp)) != NULL){
    if(buf[0] == '\n'){
      return -1;  //空行を発見したら-1を返す
    }
    int value = atoi(buf);
    min = min > value ? value : min;
    max = max < value ? value : max;
  }

  return max - min;
}

int range(const char *pFname){
  return read_file(pFname, range_processor);
}

