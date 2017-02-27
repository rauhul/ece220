#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)

void calculateCosineFilter(double *cosFilter, int radius);

void convolveImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                   uint8_t* outBlue,uint8_t* outAlpha,const double *filter,
                   int radius,int width,int height);

void convertToGray(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                   uint8_t *outBlue,uint8_t *outAlpha,
                   const double *gMonoMult,int width,int height);

void invertImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                 uint8_t *outBlue,uint8_t *outAlpha,int width,int height);

void colorThreshold(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                 uint8_t *outBlue,uint8_t *outAlpha,int width,int height,int redThreshold,int blueThreshold,int greenThreshold);

void detectImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,int* outPixelCol, int* outPixelRow, uint8_t *targetRed, uint8_t *targetBlue,
		   uint8_t *targetGreen, uint8_t *targetAlpha,int width,int height,int targetWidth, int targetHeight);

void transformImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,
              uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
              uint8_t *outAlpha,const double transform[2][2],int width,int height);
