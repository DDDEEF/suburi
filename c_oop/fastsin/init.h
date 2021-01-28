#ifndef _FASTSIN_INIT_H_INCLUDED_
#define _FASTSIN_INIT_H_INCLUDED_

/* sin の値を格納する配列 */
extern SinArryaType fastsin_array[];

/* 初期化済みかどうかのフラグ */
extern int fastsin_initialized;

/*
 * 配列の初期化用関数 
 */
void fastsin_init();

#endif