int get_parity(unsigned int val){
  val ^= >> 16;
  val ^= >> 8;
  val ^= >> 4;
  val ^= >> 2;
  val ^= >> 1;

  return (val & 0x01);
}
