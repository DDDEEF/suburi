int get_no(unsigned int val){
  int no = 0;

  while(val){
    if(val & 0x01){
      return (no);
    }
    no++;
    val >>= 1;
  }

  return (-1);
}
