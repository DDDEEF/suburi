double power(double x, int n){
  double tmp = 1.0;
  for(int i = 1; i <= n; i++){
    tmp *= x;
  }
  return tmp;
}
