/*********************************************************
 * ファイル名 : Road.c[rd]
 * 責務       : 路面の色を確定する
 * 作成日     : 2020.03.03
 * 作成者     : System-san
 *********************************************************/
/*** 利用ファイルのヘッダ ***/
#include "../DrvApi/Sensor.h"

/*** 自ファイルのヘッダ ***/
#include "Road.h"

/*** 公開関数 ********************************************/
/*********************************************************
 * 関数名 : rd_init
 * 機能   : 初期化処理
 * 引数   : なし
 * 戻値   : なし
 * 備考   :
 *********************************************************/
void rd_init(void){
  /* 何もしない */
  return;
}

/*********************************************************
 * 関数名 : rd_term
 * 機能   : 終了処理
 * 引数   : なし
 * 戻値   : なし
 * 備考   :
 *********************************************************/
void rd_term(void){
  /* 何もしない */
  return;
}

/*********************************************************
 * 関数名 : rd_getRoadColor
 * 機能   : 路面の色を返す
 * 引数   : なし
 * 戻値   : 路面の色
 * 備考   :
 *********************************************************/
roadColor_t rd_getRoadColor(void){
  unsigned int light;
  roadColor_t roadColor;

  light = ss_getLightValue();
  if(light < WHITE_THRESHOLD){
    roadColor = eWhite;
  }else if(light < LIGHTGRAY_THRESHOLD){
    roadColor = eLightGray;
  }else if(light < GRAY_THRESHOLD){
    roadColor = eGray;
  }else if(light < DARKGRAY_THRESHOLD){
    roadColor = eDarkGray;
  }else{
    roadColor = eBlack;
  }

  return roadColor;
}
