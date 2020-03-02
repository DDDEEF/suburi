int on_bit_num(unsigned int data){
  static char table[16] = {
    0, 1, 1, 2,   /* 0000 0001 0010 0011 */
    1, 2, 2, 3,   /* 0100 0101 0110 0111 */
    1, 2, 2, 3,   /* 1000 1001 1010 1011 */
    2, 3, 3, 4    /* 1100 1101 1110 1111 */
  };

  int num = 0;
  int loop;

  for(loop = 0; loop < 8; loop++){
    num += table[data & 0x0f];
    data >>= 4;
  }

  return (num);
}
