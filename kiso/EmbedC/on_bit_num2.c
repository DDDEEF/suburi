int on_bit_num2(unsigned int data){
  int num;
  static char table[16] = {
    0, 1, 1, 2,   /* 0000 0001 0010 0011 */
    1, 2, 2, 3,   /* 0100 0101 0110 0111 */
    1, 2, 2, 3,   /* 1000 1001 1010 1011 */
    2, 3, 3, 4    /* 1100 1101 1110 1111 */
  };

  num = table[data & 0x0f];
  num += table[(data >> 4) & 0x0f];
  num += table[(data >> 8) & 0x0f];
  num += table[(data >> 12) & 0x0f];
  num += table[(data >> 16) & 0x0f];
  num += table[(data >> 20) & 0x0f];
  num += table[(data >> 24) & 0x0f];
  num += table[(data >> 28) & 0x0f];

  return (num);
}
