#define DGBPRINT(n) {\
  printf("%s(%s:%d): n %d\n",\
    __func__,\
    __FILE__, __LINE__,\
    n);\
}
