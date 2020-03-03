/*********************************************************
 * ファイル名 : Sensor.h
 * 責務       : 光センサドライバ
 * 作成日     : 2020.03.02
 * 作成者     : System-san
 *********************************************************/
#ifndef SENSOR_H
#define SENSOR_H

/*********************************************************
 * 定数
 *********************************************************/
#define WHITE_THRESHOLD 580 /* 白の上限値 */
#define LIGHTGRAY_THRESHOLD 605 /* 淡い灰色の上限値 */
#define GRAY_THRESHOLD 645  /* 灰色の上限値 */
#define DARKGRAY_THRESHOLD 670 /* 濃い灰色の上限値 */

/*********************************************************
 * extern関数宣言
 *********************************************************/
extern void ss_init(void);
extern void ss_term(void);
unsigned int ss_getLightValue(void);

#endif /* SENSOR_H */
