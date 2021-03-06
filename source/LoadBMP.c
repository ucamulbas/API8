#include "../include/LoadBMP.h"

int ImageLoad(char *filename, Image *image)
{
    FILE *file;
    unsigned long size;  
    unsigned long i, j;     
    unsigned short int planes;
    unsigned short int bpp;   
    GLubyte temp;
	char inversionx = 0, inversiony = 0;

    struct {
      unsigned short int type;                 /* Magic identifier            */
      unsigned int size;                       /* File size in bytes          */
      unsigned short int reserved1, reserved2;
      unsigned int offset;                     /* Offset to image data, bytes */
    } header;

    struct {
      unsigned int size;               /* Header size in bytes      */
      int width,height;                /* Width and height of image */
      unsigned short int planes;       /* Number of colour planes   */
      unsigned short int bits;         /* Bits per pixel            */
      unsigned int compression;        /* Compression type          */
      unsigned int imagesize;          /* Image size in bytes       */
      int xresolution,yresolution;     /* Pixels per meter          */
      unsigned int ncolours;           /* Number of colours         */
      unsigned int importantcolours;   /* Important colours         */
    } infoheader;



    if ((file = fopen(filename, "rb"))==NULL) {
      printf("File Not Found : %s\n",filename);
      return -1;
    }

    fread(&header, 14, 1, file);
    fread(&infoheader, 40, 1, file);

    /*    
    printf("%x %x %x %x %x\n", header.type, header.size, header.reserved1, header.reserved2, header.offset);
    printf("%x %x %x %x %x %x %x %x %x %x %x\n", infoheader.size, infoheader.width, infoheader.height,
	   infoheader.planes, infoheader.bits, infoheader.compression, infoheader.imagesize, 
	   infoheader.xresolution, infoheader.yresolution, infoheader.ncolours, infoheader.importantcolours);
    */

    fseek(file, 18, SEEK_SET);

    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
      printf("Error reading width from %s.\n", filename);
      return -1;
    }

    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
      printf("Error reading height from %s.\n", filename);
      return -1;
    }

#ifdef __OSX2__
	printf("C est un OSX2\n");
  image->sizeX = (((image->sizeX)>>24)&0xff) | ((((image->sizeX)>>16)&0x00ff)<<8) | ((((image->sizeX)>>8)&0x0000ff)<<16) | ((((image->sizeX)>>0)&0x000000ff)<<24);
  image->sizeY = (((image->sizeY)>>24)&0xff) | ((((image->sizeY)>>16)&0x00ff)<<8) | ((((image->sizeY)>>8)&0x0000ff)<<16) | ((((image->sizeY)>>0)&0x000000ff)<<24);
  
#endif

  if (image->sizeX < 0) {
	printf("taille negative X ?\n");
	image->sizeX = 0 - image->sizeX;
	inversionx = !inversionx;
  }
  if (image->sizeY < 0) {
	printf("taille negative Y ?\n");
	image->sizeY = 0 - image->sizeY;
	inversiony = ! inversiony;
  }
    size = image->sizeX * image->sizeY * 3;
	printf("Load %d\t %d %d soit %d \n",__LINE__, (int) image->sizeX, (int) image->sizeY, (int) size);

    if ((fread(&planes, 2, 1, file)) != 1) {
      printf("Error reading planes from %s.\n", filename);
      return -1;
    }

#ifdef __OSX2__
  if (planes != 256)
    {
      printf("Planes from %s is not 1 (mac): %u\n", filename, planes);
      return -1;
    }
#else
    if (planes != 1) {
      printf("Planes from %s is not 1: %u\n", filename, planes);
      return -1;
    }
#endif
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
      printf("Error reading bpp from %s.\n", filename);
      return -1;
    }
#ifdef __OSX2__
  if (bpp != 0x1800)
    {
      printf("Bpp from %s is not 24 (mac): %u\n", filename, bpp);
      return -1;
    }
#else
    if (bpp != 24) {
      printf("Bpp from %s is not 24: %u\n", filename, bpp);
      return -1;
    }
#endif
    fseek(file, 57, SEEK_SET);
	/*    fseek(file, 24, SEEK_CUR);*/
    image->data = (GLubyte *)malloc((size_t)(size));
    if (image->data == NULL) {
      printf("Houston we have a problem\n");
      printf("Error allocating memory for color-corrected image data\n");
      return -1;	
    }
	
	/*    if ((i = fread(image->data, (size_t) size, (size_t) 1, file)) != 1) {
      printf("Problem reading image data from %s.\n Data read %d\n", filename, (int) i);
	        return -1;
    }
    */
	
    i = fread(image->data, (size_t) size, (size_t) 1, file);

    if (inversionx == 1 && inversiony == 1) {
      for (i=0;i<size/2;i++) {
        temp = image->data[(int)size - 1 - i];
        image->data[(int)size - 1 - i] = image->data[i];
        image->data[i] = temp;
      }
    }  else if (inversionx == 1) {
      for (i=0; i<size; i+=image->sizeX * 3) {
        for (j=0; (int)j<image->sizeX * 3 / 2; j++) {
          temp = image->data[i + (image->sizeX * 3 - 1 - j)];
          image->data[i + (image->sizeX * 3 - 1 - j)] = image->data[i + j];
          image->data[i + j] = temp;
        }
      }
    } else {
      for (i=0;i<size;i+=3) {
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;
      }
    }
    if (inversiony == 1 && inversionx == 0) {
      GLubyte * buffer = (GLubyte *)malloc((int)(image->sizeX * 3));
      for (i=0; i<size/2;i+=image->sizeX * 3) {
        memcpy(buffer, &image->data[i], image->sizeX * 3);
        memcpy(&image->data[i], &image->data[size - image->sizeX * 3 - i], image->sizeX * 3);
        memcpy(&image->data[size - image->sizeX * 3 - i], buffer, image->sizeX * 3);
      }
      free(buffer);
    }

	/*	printf("Load %d\n",__LINE__);*/
	/*    for (i=0;i<(int)size;i+=3) { 
      temp = image->data[i];
      image->data[i] = image->data[i+2];
      image->data[i+2] = temp;
	  }*/
    fclose(file);
    return 0;
}
