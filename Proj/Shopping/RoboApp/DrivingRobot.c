/*********************************************************
 * ファイル名 : DrivingRobot.c
 * 責務       : ドライブして買物に行く
 * 作成日     : 2020.03.05
 * 作成者     : System-san
 *********************************************************/
/*** 利用ファイルのヘッダ ***/
#include "Marker.h"
#include "../Middleware/Trace.h"
#include "Shopping.h"
/*** 自ファイルのヘッダ ***/
#include "DrivingRobot.h"

/*********************************************************
 * 型
 *********************************************************/
typedef enum{
  eDriving, /* 走行中 */
  eShopping /* 買物中 */
} CurrentState_t;

/*********************************************************
 * 変数
 *********************************************************/
static CurrentState_t current_status; /* 現在状態 */

/**********************************************************
 * 関数プロトタイプ宣言
 *********************************************************/
static void db_actDriving(Spot_t);
static void db_actShopping(Spot_t);

/*** 公開関数 ********************************************/
/**********************************************************
 * 関数名   : db_init
 * 機能     : 初期化処理
 * 引数     : なし
 * 戻値     : なし
 * 備考     :
 *********************************************************/
void db_init(void){
  current_status = eDriving;
  sh_init();
  return;
}

/**********************************************************
 * 関数名   : db_term
 * 機能     : 終了処理
 * 引数     : なし
 * 戻値     : なし
 * 備考     :
 *********************************************************/
void db_term(void){
  return;
}

/*********************************************************
 * 関数名   : db_goShopping
 * 機能     : コース上の店での買物を開始する
 * 引数     : なし
 * 戻値     : なし
 * 備考     :
 *********************************************************/
void db_goShopping(void){
  Spot_t spot; /* 現在スポット */

  /* コース状態から現在スポットを知る */
  spot = mk_presentSpot();

  switch(current_status){
    case eDriving:  /* 走行中 */
      /* 現在スポットと現在状態から、動作を決める */
      /* 決定表に従って実装する */
      db_actDriving(spot);
      break;
    case eShopping: /* 買物中 */
      /* 現在スポットと現在状態から、動作を決める */
      /* 決定表に従って実装する */
      db_actShopping(spot);
      /* 買物が終了したかを問い合わせる */
      if(sh_doneShopping() == eTRUE){
        current_status = eDriving;
      }
      break;
    default:
      /* 何もしない */
      break;
  }

  /* ロボットを動かす */
  tr_cyclic();
  return;
}

/*** 非公開関数 ******************************************/
/*********************************************************
 * 関数名   : db_actDriving
 * 機能     : 走行中の時に、現在スポットでの動作を決める
 * 引数     : 現在スポット
 * 戻値     : なし
 * 備考     :
 *********************************************************/
static void db_actDriving(Spot_t spot){
  switch(spot){
    case eSpotRoad:
      /* 現在状態は変わらずにライン走行開始 */
      tr_start();
      break;
    case eSpotShop:
      /* 現在状態を買物中 */
      current_status = eShoping;
      /* 停止指示 */
      tr_stop();
      /* 買物開始 */
      sh_entryShopping();
      break;
    case eSpotHome:
      /* 動作完了 */
      tr_stop();
      break;
  }
  return;
}

/*********************************************************
 * 関数名   : db_actShopping
 * 機能     : 買物中の時に、現在スポットでの動作を決める
 * 引数     : 現在スポット
 * 戻値     : なし
 * 備考     :
 *********************************************************/
static void db_actShopping(Spot_t spot){
  switch(spot){
    case eSpotRoad:
      /* 起こりえない */
      /* 何もしない */
      break;
    case eSpotShop:
      /* 現在状態は変わらずに */
      current_status = eShopping;
      /* 停止指示 */
      tr_stop();
      break;
    case eSpotHome:
      /* 動作完了 */
      tr_stop();
      break;
  }
  return;
}
