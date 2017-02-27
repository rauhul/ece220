#include "lodepng.h"
#include "imageData.h"
#include "functions.h"
#include "solution.h"

//defining all the filters
const double medianBlur[25]=
{
  0,0,1/13.0,0,0,
  0,1/13.0,1/13.0,1/13.0,0,
  1/13.0,1/13.0,1/13.0,1/13.0,1/13.0,
  0,1/13.0,1/13.0,1/13.0,0,
  0,0,1/13.0,0,0
};

const double motionBlur[81]=
{
  1/9.0,0,0,0,0,0,0,0,0,
  0,1/9.0,0,0,0,0,0,0,0,
  0,0,1/9.0,0,0,0,0,0,0,
  0,0,0,1/9.0,0,0,0,0,0,
  0,0,0,0,1/9.0,0,0,0,0,
  0,0,0,0,0,1/9.0,0,0,0,
  0,0,0,0,0,0,1/9.0,0,0,
  0,0,0,0,0,0,0,1/9.0,0,
  0,0,0,0,0,0,0,0,1/9.0
};

const double sharpenLess[25]=
{
  -1/8.0,-1/8.0,-1/8.0,-1/8.0,-1/8.0,
  -1/8.0,2/8.0,2/8.0,2/8.0,-1/8.0,
  -1/8.0,2/8.0,1,2/8.0,-1/8.0,
  -1/8.0,2/8.0,2/8.0,2/8.0,-1/8.0,
  -1/8.0,-1/8.0,-1/8.0,-1/8.0,-1/8.0,
};

const double sharpenMore[9]=
{
  -1,-1,-1,
  -1,9,-1,
  -1,-1,-1
};

const double edgeDetect[9]=
{
  -1,-1,-1,
  -1,8,-1,
  -1,-1,-1
};

const double emboss[9]=
{
  -2,-1,0,
  -1,1,1,
  0,1,2,
};

//Function printPixel prints the value of a specified pixel for you
//Can be used to print to the command line for debugging purposes
//Specified row and col must be valid (between 0 and height-1, 0 and width-1). 
void printPixel(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,int width,int height, int col, int row){
	if(row<0 || row>(height-1) || col<0 || col>(width-1)){
		printf("Invalid Pixel Col:%d Row:%d\n",col,row);
	}else{
		int index = row*width+col;	
		printf("Pixel Values of Col:%d Row:%d\n",col,row);
		printf("Red:%d Blue:%d Green:%d Alpha:%d\n",inRed[index],inBlue[index],inGreen[index],inAlpha[index]);
	}	
}

//function for encoding a PNG
void encode(const char *filename,Image *encodeImage)
{
  int width=encodeImage->width;
  int height=encodeImage->height;
  unsigned char *image=(unsigned char*)malloc(sizeof(unsigned char)*4*height*width);
  
  int row,col;
  int imageWidth=4*width;
  uint8_t *redChannel=encodeImage->redChannel;
  uint8_t *greenChannel=encodeImage->greenChannel;
  uint8_t *blueChannel=encodeImage->blueChannel;
  uint8_t *alphaChannel=encodeImage->alphaChannel;

  for(row=0;row<height;row++)
    for(col=0;col<width;col++)
    {
      image[imageWidth*row+4*col+0]=redChannel[row*width+col];
      image[imageWidth*row+4*col+1]=greenChannel[row*width+col];
      image[imageWidth*row+4*col+2]=blueChannel[row*width+col];
      image[imageWidth*row+4*col+3]=alphaChannel[row*width+col];
    }

  unsigned int error=lodepng_encode32_file(filename,image,width,height);
  if(error)
    printf("error %u:%s\n",error,lodepng_error_text(error));

  free(image);
}

//function for decoding a PNG
Image *decode(const char *filename)
{
  Image *inputImage=(Image*)malloc(sizeof(Image));
  unsigned int error;
  unsigned char *image;

  //FIX: fix this part here
  error=lodepng_decode32_file(&image,(unsigned int*)&(inputImage->width),(unsigned int*)&(inputImage->height),filename);
  if(error)
    printf("error %u: %s\n",error,lodepng_error_text(error));

  int width=inputImage->width;
  int height=inputImage->height;
  inputImage->redChannel=(uint8_t*)malloc(sizeof(uint8_t)*width*height);
  inputImage->greenChannel=(uint8_t*)malloc(sizeof(uint8_t)*width*height);
  inputImage->blueChannel=(uint8_t*)malloc(sizeof(uint8_t)*width*height);
  inputImage->alphaChannel=(uint8_t*)malloc(sizeof(uint8_t)*width*height);

  int row,col;
  int imageWidth=width*4;
  uint8_t *redChannel=inputImage->redChannel;
  uint8_t *greenChannel=inputImage->greenChannel;
  uint8_t *blueChannel=inputImage->blueChannel;
  uint8_t *alphaChannel=inputImage->alphaChannel;

  for(row=0;row<height;row++)
  {
    for(col=0;col<width;col++)
    {
      redChannel[row*width+col]=image[imageWidth*row+4*col+0];
      greenChannel[row*width+col]=image[imageWidth*row+4*col+1];
      blueChannel[row*width+col]=image[imageWidth*row+4*col+2];
      alphaChannel[row*width+col]=image[imageWidth*row+4*col+3];
    }
  }

  free(image);
  return inputImage;
}

Image *generateOutput(Image *inputImage)
{
  Image *outputImage=(Image*)malloc(sizeof(Image));
  int width=inputImage->width;
  int height=inputImage->height;
  outputImage->width=width;
  outputImage->height=height;
  outputImage->redChannel=(uint8_t*)malloc(sizeof(uint8_t)*width*height);
  outputImage->greenChannel=(uint8_t*)malloc(sizeof(uint8_t)*width*height);
  outputImage->blueChannel=(uint8_t*)malloc(sizeof(uint8_t)*width*height);
  outputImage->alphaChannel=(uint8_t*)malloc(sizeof(uint8_t)*width*height);
  return outputImage;
}

Filter *initializeFilters(int radius)
{
  int filterSize=(2*radius+1)*(2*radius+1);
  double *cosBlur=(double*)malloc(sizeof(double)*filterSize);
  calculateCosineFilter(cosBlur,radius);

  Filter *filters=(Filter*)malloc(sizeof(Filter)*NUM_FILTERS);

  filters[0].radius=radius;
  filters[0].filter=(const double*)cosBlur;

  filters[1].radius=2;
  filters[1].filter=medianBlur;

  filters[2].radius=4;
  filters[2].filter=motionBlur;

  filters[3].radius=2;
  filters[3].filter=sharpenLess;

  filters[4].radius=1;
  filters[4].filter=sharpenMore;

  filters[5].radius=1;
  filters[5].filter=edgeDetect;

  filters[6].radius=1;
  filters[6].filter=emboss;

  return filters;
}
void freeImage(Image *inputImage)
{
  free(inputImage->redChannel);
  free(inputImage->greenChannel);
  free(inputImage->blueChannel);
  free(inputImage->alphaChannel);
  free(inputImage);
}
