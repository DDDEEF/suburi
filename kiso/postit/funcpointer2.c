void *bsearch(int (*compar)(const void *, const void *)){
  
}

int int_cmp(const int *a, const int *b){
  
}

int main(void){

  bsearch((int (*)(const void *, const void *))int_cmp);

}
