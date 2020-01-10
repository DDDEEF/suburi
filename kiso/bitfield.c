#include <stdio.h>
#include <math.h>

int main(){
  float f;
  union{
    float f;
    struct{
      short b16:1;
      short b15:1;
      short b14:1;
      short b13:1;
      short b12:1;
      short b11:1;
      short b10:1;
      short  b9:1;
      short  b8:1;
      short  b7:1;
      short  b6:1;
      short  b5:1;
      short  b4:1;
      short  b3:1;
      short  b2:1;
      short  b1:1;
    }b;
  }f_b;

  while(1){
    scanf("%g", &f);
    f_b.f = f;
    printf("%d", f_b.b.b16&0x01);
    printf("%d", f_b.b.b15&0x01);
    printf("%d", f_b.b.b14&0x01);
    printf("%d", f_b.b.b13&0x01);
    printf("%d", f_b.b.b12&0x01);
    printf("%d", f_b.b.b11&0x01);
    printf("%d", f_b.b.b9&0x01);
    printf("%d", f_b.b.b8&0x01);
    printf("%d", f_b.b.b7&0x01);
    printf("%d", f_b.b.b6&0x01);
    printf("%d", f_b.b.b5&0x01);
    printf("%d", f_b.b.b4&0x01);
    printf("%d", f_b.b.b3&0x01);
    printf("%d", f_b.b.b2&0x01);
    printf("%d", f_b.b.b1&0x01);
  }

  return(0);
}
