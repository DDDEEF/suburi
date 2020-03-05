/*********************************************************
 * ファイル名 : Trace.h
 * 責務       : コースを走行する
 * 作成日     : 2020.03.05
 * 作成者     : System-san
 *********************************************************/
#ifndef TRACE_H
#define TRACE_H

/*********************************************************
 * extern関数宣言
 *********************************************************/
extern void tr_init(void);
extern void tr_term(void);
extern void tr_cyclic(void);    /* ロボット駆動(20msec) */
extern void tr_start(void);     /* 走行開始の指示 */
extern void tr_stop(void);      /* 停止の指示 */
extern void tr_runnable(void);

#endif /* TRACE_H */
