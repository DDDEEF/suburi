/*********************************************************
 * ファイル名 : Shopping.h [sh]
 * 責務       : 買い物をする(一定時間待ち)
 * 作成日     : 2020.03.06
 * 作成者     : System-san
 *********************************************************/
#ifndef SHOPPING_H
#define SHOPPING_H

/*********************************************************
 * 型
 *********************************************************/
typedef enum {
  eFALSE, /* 偽 */
  eTRUE   /* 真 */
} bool_t;

/*********************************************************
 * extern関数宣言
 *********************************************************/
extern void sh_init(void);
extern void sh_term(void);
extern void sh_entryShopping(void);
extern void bool_t sh_doneShopping(void);

#endif /* SHOPPING_H */
