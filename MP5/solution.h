#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)

int getRadiusSol(double sigma);

void calculateGausFilterSol(double *gausFilter,double sigma);

void calculateCosineFilterSol(double *cosFilter,int radius);

void convolveImageSol(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                   uint8_t* outBlue,uint8_t* outAlpha,const double *filter,
                   int radius,int width,int height);

void convertToGraySol(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                   uint8_t *outBlue,uint8_t *outAlpha,
                   const double *gMonoMult,int width,int height);

void invertImageSol(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                 uint8_t *outBlue,uint8_t *outAlpha,int width,int height);

void colorThresholdSol(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                 uint8_t *outBlue,uint8_t *outAlpha,int width,int height,int redThreshold,int blueThreshold,int greenThreshold);

void detectImageSol(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,int* outPixelCol, int* outPixelRow, uint8_t *targetRed, uint8_t *targetBlue,
		   uint8_t *targetGreen, uint8_t *targetAlpha,int width,int height,int targetWidth, int targetHeight);

void transformImageSol(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,
              uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
              uint8_t *outAlpha,const double transform[2][2],int width,int height);
