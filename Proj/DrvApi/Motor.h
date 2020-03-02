/*********************************************************
 * ファイル : Motor.h
 * 責務     : 直立走行するドライバ
 * 作成日   : 2020.03.02
 * 作成者   : System-san
 *********************************************************/

#ifndef MOTOR_H
#define MOTOR_H

/*********************************************************
 * 型
 *********************************************************/
/* 前後方向 */
typedef enum {
  eSTOP,    /* その場 */
  eFRONT,   /* 前方向 */
  eBACK     /* 後方向 */
} FrontBack_t;

typedef enum {
  eNO_TURN,
  eLEFT_TURN,
  eRIGHT_TURN
} LeftRight_t;

typedef struct {
  FrontBack_t front_back;
  LeftRight_t left_right;
} mt_direction_t;

/*********************************************************
 * extern関数宣言
 *********************************************************/
extern void mt_init(void);
extern void mt_term(void);
extern void mt_running(void);
extern void mt_drvMotor(mt_direction_t);

#endif /* MOTOR_H */
