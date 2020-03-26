#include "image.h"

void initCoordinateData(ImageData *image, Coordinate *coordinate){
  coordinate->x = 0;
  coordinate->y = 0;

  // buffer1を方向として利用する(0:初期状態,1:右へ進む,2:左へ進む)
  coordinate->buffer1 = 0;
}

int getNextCoordinate(ImageData *image, Coordinate *coordinate){
  int next_x;
  int next_y;
  int direction;
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
    direction = coordinate->buffer1;
    switch(direction){
      case 1: // 右へ進む
        next_x++;
        break;
      case 2: // 左へ進む
        next_x--;
        break;
    }
    if(next_x >= width){
      next_x = width - 1;
      next_y++;
      direction = 3 - direction;  //方向変換
    }
    if(next_x < 0){
      next_x = 0;
      next_y++;
      direction = 3 - direction;  //方向転換
    }
    if(next_y >= height){
      return 0;
    }

    coordinate->x = next_x;
    coordinate->y = next_y;
    coordinate->buffer1 = direction;
    return 1;
  }
}

void main(int ac, char *av[]){
  ImageData *image;
  Coordinate coordinate;
  int x, y;

  // 画像データの作成(ファイルから読み込む場合などもあり)
  image = createImage(4, 5, 24);

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
