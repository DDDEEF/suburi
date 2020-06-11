/* case1 */
#define CASE1

#if CASE0   //CASE0は定義されていないので0と評価され、実行されない
#elif CASE1 //実行される
#endif

/* case2 */
#define CASE2

#if defined(CASE200)  //CASE200は定義されていないので0と評価され、実行されない
#endif

/* case3 */
#define CASE3 //定義
#undef  CASE3 //定義取り消し CASE3は0と評価される

/* case4 */
#ifdef CASE4 // == #if defined(CASE4) 定義されていれば実行
#endif

#ifndef CASE4 // == #if !defined(CASE4) 定義されていなければ実行
#endif

/* case5 */
#define CASE5

#if defined(CASE5) && defined(CASE500)
#endif
