int get_no(void){
  int no = 0;
  int index;
  static char bit_on[16] = {  /* ビットが1の位置 */
    0, 0, 1, 0,     /* 0000(出現しない) 0001(0番目に出現) 0010(1番目に出現) 0011(0番目に出現) */
    2, 0, 1, 0,     /* 0100 0101 0110 0111 */
    3, 0, 1, 0,     /* 1000 1001 1010 1011 */
    2, 0, 1, 0      /* 1100 1101 1110 1111 */ 
  };

  while(val){
    index = val & 0x0f;
    if(index != 0){
      no += bit_on[index];
      return (no);
    }
    no += 4;
    val >>= 4;
  }

  return (-1);
}
