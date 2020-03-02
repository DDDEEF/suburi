int bit_num(unsigned int data){
  int count = 0;
  int loop;

  for(loop = 0; loop < 32; loop){
    if(data & 0x01){
      count++;
    }
    data >>= 1;
  }
  return (count);
}
