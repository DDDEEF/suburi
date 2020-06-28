#include "image.h"

void main(int ac, char *av[]){
  ImageData *image;
  int x;
  int y;
  int width;
  int height;
  Pixel pixel1;
  Pixel pixel2;

  // 画像データの作成(ファイルから読み込む場合などもあり)
  image = createImage(100, 100, 24);

  // 画像処理プログラムの基本形
  width = image->width;
  height = image->height;
  for(y = 0; y < height; y++){
    for(x = 0; x < width; x++){
      // 画像処理を行うコード

    }
  }
  // 画像処理プログラムの基本形(ここまで)
  disposeImage(image);
}
