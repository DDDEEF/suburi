#include <stdio.h>
#include <dlfcn.h>

int main(){
  void *handle;
  int (*sotest)(char *msg);
  char *err;

  if(!(handle = dlopen("./libsotest.so", RTLD_LAZY))){
    fprintf(stderr, "%s\n", dlerror());
    return(-1);
  }

  dlerror();

  sotest = (int (*)(char *))dlsym(handle, "sotest");
  if((err = dlerror()) != NULL){
    fprintf(stderr, "%s\n", err);
    dlclose(handle);
    return(-1);
  }

  (*sotest)("from main");

  dlclose(handle);

  return(0);
}
