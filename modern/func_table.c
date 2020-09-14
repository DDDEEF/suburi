typedef struct FooVtbl{
  void (* const func0)(struct Foo *pThis);
  void (* const func1)(struct Foo *pThis);
  void (* const func2)(struct Foo *pThis);
}FooVtbl;

static FooVtbl foo_vtbl = {func0_impl, func1_impl, func2_impl};

typedef struct Foo{
  const int count;
  const FooVtbl * const pVtbl;
}Foo;

Foo foo0 = {0, &foo_vtbl};
Foo foo1 = {1, &foo_vtbl};
Foo foo2 = {2, &foo_vtbl};
