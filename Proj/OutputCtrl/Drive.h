/*********************************************************
 * ファイル名 : Drive.h
 * 責務       : ロボットを走行させる
 * 作成日     : 2020.03.03
 * 作成者     : System-san
 *********************************************************/
#ifndef DRIVE_H
#define DRIVE_H

/*********************************************************
 * 型
 *********************************************************/
/* 前後方向 */
typedef enum {
  eStopForward,   /* その場 */
  eMoveForward,   /* 前方向 */
} directForward_t;

/* 左右方向 */
typedef enum {
  eTurnLeft,      /* 左方向 */
  eStraight,      /* 直進方向 */
  eTurnRight,     /* 右方向 */
} directTurn_t;

typedef struct {
  directForward_t forward;
  directTurn_t  turn;
} directionVector_t;

/*********************************************************
 * extern関数宣言
 *********************************************************/
extern void dr_init(void);
extern void dr_term(void);
extern void dr_move(directionVector_t);

#endif /* DRIVE_H */
