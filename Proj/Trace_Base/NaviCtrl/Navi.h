/*********************************************************
 * ファイル名 : Navi.h [nv]
 * 責務       : 走行をナビゲートする
 * 作成日     : 2020.03.03
 * 作成者     : System-san
 *********************************************************/
#ifndef NAVI_H
#define NAVI_H

/**********************************************************
 * extern関数宣言
 *********************************************************/
extern void nv_init(void);
extern void nv_term(void);
extern directionVector_t nv_naviCourse(diffCourse_t);

#endif /* NAVI_H */
