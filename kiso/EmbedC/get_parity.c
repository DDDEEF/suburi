int get_parity(unsigned int val){
  int loop;
  int count = 0;

  for(loop = 0; loop < 32; loop++){
    if(val & 0x01){
      count++;
    }
    val >>= 1;
  }

  return (count & 0x01);
}
