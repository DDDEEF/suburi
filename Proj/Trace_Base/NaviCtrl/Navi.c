/*********************************************************
 * ファイル名 : Navi.c [nv]
 * 責務       : 走行をナビゲートする
 * 作成日     : 2020.03.03
 * 作成者     : System-san
 *********************************************************/
/*** 利用ファイルのヘッダ ***/
#include "../InputCtrl/Course.h"
#include "../OutputCtrl/Drive.h"
/*** 自ファイルのヘッダ ***/
#include "Navi.h"

/*** 公開関数 ********************************************/
/*********************************************************
 * 関数名 : nv_init
 * 機能   : 初期化処理
 * 引数   : なし
 * 戻値   : なし
 * 備考   :
 *********************************************************/
void nv_init(void){
  /* 何もしない */
  return;
}

/**********************************************************
 * 関数名 : nv_term
 * 機能   : 終了処理
 * 引数   : なし
 * 戻値   : なし
 * 備考   :
 *********************************************************/
void nv_term{
  /* 何もしない */
  return;
}

/**********************************************************
 * 関数名 : nv_naviCource
 * 機能   : コースをナビゲートする
 * 引数   : ラインズレ
 * 戻値   : 方向指示
 * 備考   :
 *********************************************************/
directionVector_t nv_naviCourse(diffCourse_t diff){
  directionVector_t navi;

  /* 前後方向は常に「前進」 */
  navi.forward = eMoveForward;

  /* 左右のブレの補正 */
  switch(diff){
    case eNoDiff:
      navi.turn = eStraight;
      break;
    case eDiffRight:
      navi.turn = eTurnLeft;
      break;
    case eDiffLeft:
      navi.turn = eTurnRight;
      break;
    default:
      navi.turn = eStraight;
      break;
  }

  return navi;
}
