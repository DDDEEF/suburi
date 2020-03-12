/*********************************************************
 * 関数名 : resetElements
 * 機能   : 配列pのすべての要素にゼロを代入する
 * 引数   : p    配列の先頭アドレス
 *          size 配列のサイズ
 * 戻り値 : なし
 * 備考   : 
 *********************************************************/

/*** 予防的ではないresetElements関数 ***/
void resetElements(unsigned int p[], unsigned int size){
  unsigned int i;

  for(i = 0; i < size; i++){
    p[i] = 0;
  }

  return;
}

/*** 予防的な視点で書き直したresetElements関数 ***/
void resetElements(unsigned int p[], unsigned int size){
  if(p != NULL){
    unsigned int i;

    for(i = 0; i < size; i++){
      p[i] = 0;
    }
  }

  return;
}
