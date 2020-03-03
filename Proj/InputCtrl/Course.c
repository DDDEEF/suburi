/*********************************************************
 * ファイル名 : Course.c[cs]
 * 責務       : コースの状態を確定する
 * 作成日     : 2020.03.03
 * 作成者     : System-san
 *********************************************************/
/*** 利用ファイルのヘッダ ***/
#include "Road.h"
/*** 自ファイルのヘッダ ***/
#include "Course.h"

/*** 公開関数 ********************************************/
/*********************************************************
 * 関数名     : cs_init
 * 機能       : 初期化処理
 * 引数       : なし
 * 戻値       : なし
 * 備考       :
 *********************************************************/
void cs_init(void){
  rd_init();
  return;
}

/*********************************************************
 * 関数名     : cs_term
 * 機能       : 終了処理
 * 引数       : なし
 * 戻値       : なし
 * 備考       : 
 *********************************************************/
void cs_term(void){
  rd_term();
  return;
}

/*********************************************************
 * 関数名     : cs_detectDifference()
 * 機能       : 走行すべき位置からのズレを返す
 * 引数       : なし
 * 戻値       : ズレ
 * 備考       :
 *********************************************************/
diffCourse_t cs_detectDifference(void){
  roadColor_t color;
  diffCourse_t diff;

  color = rd_getRoadColor();

  switch(color){
    case eWhite:
      diff = eDiffRight;
      break;
    case eLightGray:
      diff = eDiffRight;
      break;
    case eGray:
      diff = eNoDiff;
      break;
    case eDarkGray:
      diff = eDiffLeft;
      break;
    case eBlack:
      diff = eDiffLeft;
      break;
    default:    /* other */
      diff = eDiffLeft;
      break;
  }

  return diff;
}
