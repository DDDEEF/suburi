int get_parity(unsigned int val){
  val = (val & 0x0000FFFF) ^ (val >> 16);
  val = (val & 0x000000FF) ^ (val >> 8);
  val = (val & 0x0000000F) ^ (val >> 4);
  val = (val & 0x00000003) ^ (val >> 2);
  val = (val & 0x00000001) ^ (val >> 1);

  return (val);
}
