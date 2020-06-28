#include "image.h"

void main(int ac, char *av[]){
  ImageData *image;
  Coordinate coordinate;
  int x;
  int y;

  // 画像データの作成(ファイルから読み込む場合などもあり)
  image = createImage(20, 10, 24);

  // 本書でのプログラムの基本形

  // 座標データの初期化
  initCoordinateData(image, &coordinate);
  // 処理対象画素がなくなるまでループする
  while(getNextCoordinate(image, &coordinate)){
    printf("[%d %d]\n", coordinate.x, coordinate.y);
  }
  // 本書でのプログラムの基本形(ここまで)
  disposeImage(image);
}
