/* ポインタへのconstの使い方 3パターン */

/* パターン1 アクセス先の値を変えられない */
int main(void){
  char num1 = 20;
  const char *pnum = &num1;
  
  *pnum = 50;   //NG
  pnum++;       //OK

  return 0;
}


/* パターン2 ポインタ変数の値を変えられない*/
int main(void){
  char num = 20;
  char *const pnum = &num1;

  *pnum = 50;   //OK
  pnum++;       //NG

  return 0;
}

/* パターン3 どっちも変えられない */
int main(void){
  char num = 20;
  const char *const pnum = &num1;

  *pnum = 50;   //NG
  pnum++;       //NG
}
