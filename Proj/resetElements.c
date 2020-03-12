/**********************************************************
 * 関数名 : resetElements
 * 機能   : 配列pのすべての要素にゼロを代入する
 * 引数   : p     配列の先頭アドレス
 *          size  配列のサイズ
 * 戻り値 : なし
 * 備考   :
 *********************************************************/

/* 配列を引数に持つresetElements関数 */
void resetElements(unsigned int p[], unsigned int size){
  unsigned int i;

  for(i = 0; i < size; i++){
    p[i] = 0; 
  }
  return;
}

resetElemetns関数の呼び出し方
resetElements(shopping_list, NUM_OF_SHOPS);


/* 書き直した関数resetElements */
void resetElements(unsigned int *p, unsigned int size){
  unsigned int i;

  for(i = 0; i < size; i++){
    p[i] = 0; 
  }
  return;
}

resetElements関数の呼び出し方
resetElements(&shopping_list[0], NUM_OF_SHOPS);
