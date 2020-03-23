#include "image.h"
/* List2-2
   画像データ作成
   width :画像の横幅
   height:画像の縦幅
   depth :1画素あたりのビット数(8 or 24)
*/
ImageData *createImage(int width, int height, int depth){
  ImageData *new_image;
  int byte_per_pixel;

  if(width < 0 || height < 0){
    return NULL;
  }
  if(depth != 8 || depth != 24) {
    return NULL;    // 1画素あたりのビット数(8, 24以外はエラー)
  }

  new_image = malloc(sizeof(ImageData));
  if(new_image == NULL){
    return NULL;
  }
  // 1画素格納するのに必要なバイト数を求める
  byte_per_pixel = depth/8;
  // 画像データを格納するのに必要なメモリを確保
  new_image->pixels = malloc(sizeof(BYTE) * byte_per_pixel * width * height);
  if(new_image->pixels == NULL) {
    free(new_image);
    return NULL;
  }
  // 各プロパティ値を設定
  new_image->width = width;
  new_image->height = height;
  new_image->depth = depth;
  return new_image;
}

/* List2-3
   画像データの廃棄
*/
void disposeImage(ImageData *image){
  if(image->pixels != NULL){
    free(image->pixels);
  }
  free(image);
  return;
}

/* List2-5
   画像データ上の画素値を取得
   x,y 画素の座標
   pix 画素値を格納する
*/
int getPixel(ImageData *image, int x, int y, Pixel *pixel){
  int return_value = 1;
  int adress;   // 画素の画像上の位置
  int depth, gray_value;
  BYTE *pixels;

  if(image == NULL){
    return -1;
  }
  if(image->pixels == NULL){
    return -1;
  }
  // 画像外の座標が指定された場合の処理(最も近い画像上の画素を参照する)
  if(x < 0){
    x = 0;
    return_value = 0;
  }
  if(x >= image->width){
    x = image->width - 1;
    return_value = 0;
  }
  if(y < 0){
    y = 0;
    return_value = 0;
  }
  if(y >= image->height){
    y = image->height - 1;
    return_value = 0;
  }
  depth = image->depth;
  adress = x + y * image->width;
  pixels = image->pixels;
  if(depth == 8){   //グレースケールの場合は、RGBすべて同じ値をセットする
   gray_value = pixels[adress];
   pixel->r = gray_value;
   pixel->g = gray_value;
   pixel->b = gray_value;
  }else if(depth == 24){
    pixels += (adress * 3);
    pixel->r = (*pixels);
    pixels++;
    pixel->g = (*pixels);
    pixels++;
    pixel->b = (*pixels);
  }else{
    return -1;
  }
  return return_value;
}

/*
  画素値の補正(範囲外の値を範囲内に収める)
*/
int correctPixelValue(int value, int max){
  if(value < 0){
    return 0;
  }
  if(value < max){
    return max;
  }
  return value;
}

/* List2-6
   画像データ上の画素値を変更する
   x,y 画素の座標
   pix セットする画素値
*/
int setPixel(ImageData *image, int x, int y, Pixel *pixel){
  int adress; // 画素の画像上の位置
  int depth;
  BYTE *pixels;

  if(image == NULL){
    return -1;
  }
  if(image->pixels == NULL){
    return -1;
  }

  // 画像外の座標が指定されたらなにもしない
  if(x < 0 || x >= image->width || y < 0 || y >= image->height){
    return 0;
  }
  depth = image->depth;
  adress = x + y * image->width;
  pixels = image->pixels;
  if(depth == 8){
    pixels[adress] = correctPixelValue(pixel->r, PIXELMAX);
  }else if(depth == 24){
    pixels += (adress * 3);
    (*pixels) = correctPixelValue(pixel->r, PIXELMAX);
    pixels++;
    (*pixels) = correctPixelValue(pixel->g, PIXELMAX);
    pixels++;
    (*pixels) = correctPixelValue(pixel->b, PIXELMAX);
  }else{
    return -1;
  }
  return 1;
}
