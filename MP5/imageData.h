#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lodepng.h"

#define NUM_FILTERS 8

typedef struct
{
  int radius;
  const double *filter;
} Filter;

typedef struct
{
  int width;
  int height;
  uint8_t *redChannel;
  uint8_t *blueChannel;
  uint8_t *greenChannel;
  uint8_t *alphaChannel;
} Image;

void printPixel(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,int width,int height, int row, int col);
void encode(const char *filename,Image *encodeImage);
Image *decode(const char *filename);
Filter *initializeFilters(int radius);
Image *generateOutput(Image *inputImage);
void freeImage(Image *inputImage);
