/*********************************************************
 * ファイル名 : Drive.c[dr]
 * 責務       : ロボットを走行させる
 * 作成日     : 2020.03.03
 * 作成者     : System-san
 *********************************************************/
/*** 利用ファイルのヘッダ ***/
#include "../DrvApi/Motor.h"
/*** 自ファイルのヘッダ ***/
#include "Drive.h"

/*********************************************************
 * 変数
 *********************************************************/
/* 前回進行方向 */
static directionVector_t lastDirection;

/**********************************************************
 * 関数プロトタイプ宣言
 *********************************************************/
static FrontBack_t dr_cvtFrontBack(directForward_t);
static LeftRight dr_cvtLeftRight(directTurn_t);

/*** 公開関数 ********************************************/
/**********************************************************
 * 関数名     : dr_init
 * 機能       : 初期化処理
 * 引数       : なし
 * 戻値       : なし
 * 備考       : 
 *********************************************************/
void dr_init(void){
  lastDirection.forward = eStopForward;
  lastDirection.turn = eStraight;
  return;
}

/**********************************************************
 * 関数名     : dr_term
 * 機能       : 終了処理
 * 引数       : なし
 * 戻値       : なし
 * 備考       :
 *********************************************************/
void dr_term(void){
  /* 何もしない */
  return;
}

/**********************************************************
 * 関数名     : dr_move
 * 機能       : 前進/後進、旋回の方向を設定する
 * 引数       : 前進/後進の方向、先回の方向
 * 戻値       : なし
 * 備考       :
 *********************************************************/
void dr_move(directionVector_t direct){
  mt_direction_t motor; /* モータの駆動方向 */

  if((direct.forward != lastDirection.forward) || (direct.turn != lastDirection.turn)){
    /* 前後方向また左右方向が変化した時にモータを駆動 */

    /* 前後方向値を変換する */
    motor.front_back = dr_cvtFrontBack(direct.forward);

    /* 左右方向値を変換する */
    motor.left_right = dr_cvtLeftRight(direct.turn);

    lastDirection = direct;

    /* モータを駆動する */
    mt_drvMotor(motor);
  }

  return;
}

/*** 非公開関数 ******************************************/
/**********************************************************
 * 関数名     : dr_cvtFrontBack
 * 機能       : 前後方向値をモータAPI値に変換する
 * 引数       : 前進/後進の方向、旋回の方向
 * 戻値       : 前後方向
 * 備考       :
 *********************************************************/
static FrontBack_t dr_cvtFrontBack(directForward_t forward){
  FrontBack_t front_back; /* 前後方向 */

  switch(forward){
    case eStopForward:
      front_back = eSTOP;
      break;
    case eMoveForward:
      front_back = eFRONT;
      break;
    default:
      /* 停止させる */
      front_back = eSTOP;
      break;
  }
  return front_back;
}

/**********************************************************
 * 関数名     : dr_cvtLeftRight
 * 機能       : 左右方向値をモータAPI値に変換する
 * 引数       : 旋回の方向
 * 戻値       : 左右方向
 * 備考       :
 *********************************************************/
static LeftRight_t dr_cvtLeftRight(directTurn_t turn){
  LeftRight_t left_right;   /* 左右方向 */

  switch(turn){
    case eTurnLeft:
      left_right = eLEFT_TURN;
      break;
    case eStraight:
      left_right = eNO_TURN;
      break;
    case eTurnRight:
      left_right = eRIGHT_TURN;
      break;
    defaule:
      /* 左右方向なし */
      left_right = eNO_TURN;
      break;
  }
  return left_rigth;
}
