#include "image.h"

void initCoordinateData(ImageData *image, Coordinate *coordinate, int blocksize){
  coordinate->x = 0;
  coordinate->y = 0;

  coordinate->buffer1 = 0;
  coordinate->buffer2 = blocksize;
}

int getNextCoordinate(ImageData *image, Coordinate *coordinate){
  int next_x;
  int next_y;
  int blocksize;

  int width;
  int height;

  width = image->width;
  height = image->height;

  if(coordinate->buffer1 == 0){   // 最初の1回目だけ特別扱いで、何もしない
    coordinate->buffer1 = 1;
    return 1;
  }else{
    next_x = coordinate->x;
    next_y = coordinate->y;
    blocksize = coordinate->buffer2;
    next_x++;
    if(next_x % blocksize == 0 || next_x >= width){
      next_x = ((next_x - 1)/blocksize)*blocksize;
      next_y++;
      if(next_y % blocksize == 0 || next_y >= height){
        next_y = ((next_y - 1) / blocksize) * blocksize;
        next_x += blocksize;
        if(next_x >= width){
          next_x = 0;
          next_y += blocksize;
        }
      }
    }
    if(next_x >= width || next_y >= height){
      return 0;
    }

    coordinate->x = next_x;
    coordinate->y = next_y;
    return 1;
  }
}

void main(int ac, char *av[]){
  ImageData *image;
  Coordinate coordinate;
  int x, y;

  // 画像データの作成(ファイルから読み込む場合などもあり)
  image = createImage(6, 3, 24);

  // 本書でのプログラムの基本形

  // 座標データの初期化
  initCoordinateData(image, &coordinate, 1);

  // 処理対象画素がなくなるまでループする
  while(getNextCoordinate(image, &coordinate)){
    printf("[%d %d]\n", coordinate.x, coordinate.y);
  }

  // 本書でのプログラムの基本形(ここまで)
  disposeImage(image);
}
