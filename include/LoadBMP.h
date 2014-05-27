#ifndef BMP
#define BMP
#include "main.h"
#include <stdlib.h>
#include <string.h>
//La fonction et la structure Image ont ete prise sur le site de M.Bourdin
struct Image {
    int sizeX;
    int  sizeY;
    GLubyte *data;
};
typedef struct Image Image;
typedef unsigned short utab [3][3][3];
Image *texture;
int ImageLoad(char*,Image*);
#endif
