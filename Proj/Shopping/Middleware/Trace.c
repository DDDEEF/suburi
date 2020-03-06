/*********************************************************
 * ファイル名 : Trace.c [tr]
 * 責務       : コースを走行する
 * 作成日     : 2020.03.05
 * 作成者     : System-san
 *********************************************************/
/*** 利用ファイルのヘッダ ***/
#include "../InputCtrl/Course.h"
#include "../OutputCtrl/Drive.h"
#include "../NaviCtrl/Navi.h"

/*** 自ファイルのヘッダ ***/
#include "Trace.h"

/*********************************************************
 * 型
 *********************************************************/
typedef enum{
  eDiagnosis, /* 自己診断中 */
  eStanding,  /* その場で倒立中 */_
  eRunning    /* 走行中 */_
} robotState_t;

/*********************************************************
 * 変数
 *********************************************************/
static robotState_t current_state;

/**********************************************************
 * 関数プロトタイプ宣言
 *********************************************************/
static void tr_traceCourse(void);
static void tr_stopCourse(void);

/*** 公開関数 ********************************************/
/**********************************************************
 * 関数名 : tr_init
 * 機能   : 初期化処理
 * 引数   : なし
 * 戻値   : なし
 * 備考   :
 *********************************************************/
void tr_init(void){
  cs_init();
  nv_init();
  dr_init();
  currnet_state = eDiagnosis;   /* 電源オン直後は自己診断 */

  return;
}

/**********************************************************
 * 関数名 : tr_term
 * 機能   : 終了処理
 * 引数   : なし
 * 戻値   : なし
 * 備考   :
 *********************************************************/
void tr_term(void){
  dr_term();
  nv_term();
  cs_term();
  return;
}

/*********************************************************
 * 関数名 : tr_cyclic
 * 機能   : ロボットを駆動する(自己診断後、コースを走行)
 * 引数   : なし
 * 戻値   : なし
 * 備考   : 20msec毎に起動される
 *********************************************************/
void tr_cyclic(void){
  switch(current_state){
    case eDiagnosis:  /* 自己診断中 */
      /* 何もしない */
      break;
    case eStanding:   /* その場で倒立中 */
      /* 停止する */
      tr_stopCourse();
    case eRunning:    /* 走行中 */
      /* 走行する */
      tr_traceCourse();
      break;
    default:
      /* 何もしない */
      break;
  }
  return;
}

/*********************************************************
 * 関数名 : tr_start
 * 機能   : 走行状態へ移行する
 * 引数   : なし
 * 戻値   : なし
 * 備考   :
 *********************************************************/
void tr_start(void){
  switch(current_state){
    case eDiagnosis:  /* 自己診断中 */
      /* 走行可能状態へ移行 */
      current_state = eRunning;
      break;
    case eStanding:   /* その場で倒立中 */
      /* 走行可能状態へ移行 */
      current_state = eRunning;
    case eRunning:   /* 走行中 */
      /* 何もしない */
      break;
    default:
      /* 何もしない */
      break;
  }
  return;
}

/*********************************************************
 * 関数名 : tr_stop
 * 機能   : その場で停止させる状態へ移行する
 * 引数   : なし
 * 戻値   : なし
 * 備考   :
 *********************************************************/
void tr_stop(void){
  switch(current_state){
    case eDiagnosis:  /* 自己診断中 */_
      /* 何もしない */
      break;
    case eStanding:   /* その場で倒立中 */
      /* 何もしない */
    case eRunning:    /* 走行中 */
      /* その場で停止へ移行 */ 
      current_state = eStanding;
      break;
    default:
      /* 何もしない */
      break;
  }
  return;
}

/**********************************************************
 * 関数名 : tr_runnable
 * 機能   : 自己診断の完了通知(走行可能になる)
 * 引数   : なし
 * 戻値   : なし
 * 備考   :
 *********************************************************/
void tr_runnable(void){
  switch(current_state){
    case eDiagnosis:  /* 自己診断中 */
      /* 走行可能状態へ移行 */
      current_state = eRunning;
      break;
    case eStanding:   /* その場で倒立中 */
      /* 何もしない */
      break;
    case eRunning:
      /* 何もしない */
      break;
    default:
      /* 何もしない */
      break;
  }
  return;
}

/*** 非公開関数 ******************************************/
/*********************************************************
 * 関数名 : tr_traceCourse
 * 機能   : コース上をトレースしながら走行する
 * 引数   : なし
 * 戻値   : なし
 * 備考   :
 *********************************************************/
static void tr_traceCourse(void){
  diffCourse_t diff; /* コースとのズレ */
  directionVector_t drct; /* 進行方向 */

  diff = cs_detectDifference();  /* ズレを検出する */
  drct = nv_naviCourse(diff);    /* 進行方向を決める */
  dr_move(drct);

  return;
}

/*********************************************************
 * 関数名 : tr_stopCourse
 * 機能   : コース上で停止する
 * 引数   : なし
 * 戻値   : なし
 * 備考   :
 *********************************************************/
static void tr_stopCourse(void){
  dr_stop();

  return;
}
