typedef enum{
  eParamError, /* エラー発生 */
  eParamOK,    /* 正常終了 */
}

/**********************************************************
 * 関数名 : tr_traceCourse
 * 機能   : コースをトレースしながら走行する
 * 引数   : なし
 * 戻り値 : なし
 * 備考   :
 *********************************************************/
static void tr_traceCourse(void){
  error_t err;        /* nv_naviCourseの引数チェックの結果 */
  diffCourse_t;       /* コースとのズレ */
  directionVector_t;  /* 進行方向 */

  diff = cs_datectDifference();     /* ズレを検出する */
  err = nv_naviCource(diff, &drct); /* 進行方向を決める */
  if(err == eParamOK){
    dr_move(drct);                  /* 進行方向に進む */
  }else{
    /* エラー処理(省略) */
  }

  return;
}

/**********************************************************
 * 関数名 : nv_naviCourse
 * 機能   : コースをナビゲートする
 * 引数   : diff ラインズレ
 *          p    方向指示を格納する領域へのポインタ
 *               引数が正しいときは、*pに方向指示を格納する
 *               引数が正しくないときは、*pに何も格納しない
 * 戻り値 : eParamOK 引数が正しいとき / eParamError 引数が正しくないとき
 * 備考   :
 *********************************************************/
error_t nv_naviCourse(diffCourse_t diff, directionVector_t *p){
  directionVector_t navi;
  error_t           err;

  /* 前後方向は常に「前進」 */
  navi.forward = eMoveForward;
  /* 引数が正しいときの戻り値はeParamOK */
  err = eParamOK;

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
      /* 引数が正しくない */
      err = eParamError;
      break;
  }

  if(err == eParamOK){
    *p = navi;
  }

  return err;
}

