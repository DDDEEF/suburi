#include <stdio.h>

#include "contents.h"

/* callback wrapper method. */
void call_back_wrapper(p_func ptr, char *s){
  ptr(s);
}

/* contents_run method. */
void contents_run(p_func func_ptr){
  p_func contents_ptr;

  // 関数ポインタにcallback対象の関数を設定.
  contents_ptr = func_ptr;

  // callcback関数をコールする
  call_back_wrapper(contents_ptr, "Updata by contents.\n");

  return;
}
