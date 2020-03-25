#include "image.h"

void initCoordinateData(ImageData *image, Coordinate *coordinate){
  coordinate->x = 0;
  coordinate->y = 0;

  // buffer1を方向として利用する(0:初期状態 1:左下へ進む 2:右上に進む)
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

  if(coordinate->buffer1 == 0){   // 最初の1回だけ特別扱いで、何もしない
    coordinate->buffer1 = 1;
    return 1;
  }else{
    next_x = coordinate->x;
    next_y = coordinate->y;
    direction = coordinate->buffer1;
    switch(direction){
      case 1: //左下へ
        next_x--;
        next_y++;
        break;
      case 2: //右上へ
        next_x++;
        next_y--;
        break;
    }
    if(next_y >= height){
      next_y = height - 1;
      next_x += 2;
      direction = 3 - direction;    //方向転換
    }
    if(next_x >= width){
      next_x = width - 1;
      next_y += 2;
      direction = 3 - direction;    //方向転換
    }
    if(next_x < 0){
      next_x = 0;
      direction = 3 - direction;    //方向転換
    }
    if(next_y < 0){
      next_y = 0;
      direction = 3 - direction;    //方向転換
    }
    if(next_x >= width || next_y >= height){
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
  int x;
  int y;

  image = createImage(4, 6, 24);

  initCoordinateData(image, &coordinate);

  while(getNextCoordinate(image, &coordinate)){
    printf("[%d %d]\n", coordinate.x, coordinate.y);
  }

  disposeImage(image);
}
