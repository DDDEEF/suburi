#ifndef _FASTSIN_CONFIGURE_H_INCLUDED_
#define _FASTSIN_CONFIGURE_H_INCLUDED_

#ifndef SHORT_INT_ARRAY
#define SHORT_INT_ARRAY
#endif

#ifndef QUADRANT_ARRAY
#define QUADRANT_ARRAY
#endif

/* 計算精度 */
#ifndef PRECISION
#define PRECISION 2
#endif

/* 1周を何分割するか */
#ifndef FINE_DEGREE
#define FINE_DEGREE (360*1)
#endif

/* FINE_DEGREE は4の倍数で指定しなければならない */
#if ((FINE_DEGREE / 4) * 4) != FINE_DEGREE
#error FINE_DEGREE must be set as multiple of 4.
#endif

/* sin の値を格納する配列の型 */
#ifdef SHORT_INT_ARRAY
typedef short int SinArrayType;
#define VALUE2ARRAY(v) ((v) * 10000.0)
#define ARRAY2VALUE(v) ((v) * (1.0 / 10000.0))
#else
typedef double SinArrayType;
#define VALUE2ARRAY(v) (v)
#define ARRAY2VALUE(v) (v)
#endif

#endif