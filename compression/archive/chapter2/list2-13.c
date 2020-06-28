#include "image.h"

void initCoordinateData(ImageData *image, Coordinate *coordinate){
  coordinate->x = 0;
  coordinate->y = 0;
  
  coordinate->buffer1 = 0;
}

int getNextCoordinate(ImageData *image, Coordinate *coordinate){
  int next_x;
  int next_y;
  int width;
  int height;

  width = image->width;
  height = image->height;

  if(coordinate->buffer1 == 0){ //最初の1回目だけ特別扱いで、何もしない
    coordinate->buffer1 = 1;
    return 1;
  }else{
    next_x = coordinate->x;
    next_y = coordinate->y;
    next_x++;
    if(next_x >= width){
      next_x = 0;
      next_y++;
    }
    if(next_y >= height){
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
  int x;
  int y;

  image = createImage(20, 10, 24);

  initCoordinateData(image, &coordinate);

  while(getNextCoordinate(image, &coordinate)){
    printf("[%d %d]\n", coordinate.x, coordinate.y);
  }

  disposeImage(image);
}
