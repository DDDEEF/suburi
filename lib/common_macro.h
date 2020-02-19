#ifndef _COMMON_MACRO_  /* 2重include防止用 */
#define _COMMON_MACRO_

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define howmany(a, b) (((a) + ((b) - 1)) / (b))
#define roundup(a, b) ((((a) + ((b) - 1)) / (b)) * (b))
#define rounddown(a, b) (((a) / (b)) * (b))

#endif /* 2重include防止用 */
