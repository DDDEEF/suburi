typedef struct STRUCT_IMAGE{
  int widht;
  int height;
  void *pixels;
}ImageData;

/*
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
  if(depth != 8 && depth != 24){
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
  if(new_image->pixels == NULL){
    free(new_image);
    return NULL;
  }
  // 各プロパティ値を設定
  new_image->width = width;
  new_image->height = height;
  new_image->depth = depth;
  return new_image;
}

/*
  画像データの廃棄
*/
void disposeImage(ImageData *image){
  if(image->pixels != NULL){
    free(image->pixels);
  }
  free(image);
  return;
}
