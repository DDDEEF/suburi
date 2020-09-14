/* 仮想関数テーブル */
typedef struct Foo{
  int count;
  void (*func0)(struct Foo *pThis);
  void (*func1)(struct Foo *pThis);
  void (*func2)(struct Foo *pThis);
  void (*reset_counter)(struct Foo *pThis);
}Foo;

/* 非仮想関数テーブル */
typedef struct Foo{
  int count;
  void (*func0)(struct Foo *pThis);
  void (*func1)(struct Foo *pThis);
  void (*func2)(struct Foo *pThis);
}Foo;

void reset_foo_counter(Foo *pThis){
  pThis->count = 0;
}
