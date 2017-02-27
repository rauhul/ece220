#include "imageData.h"
#include "functions.h"

const double gMonoMult[3]={.299,.587,.114};

int main(int argc,char *argv[])
{
  //Handles user input
  if(argc<4 || argc>6)
  {
    printf("Incorrect number of arguments\n");
    printf("Number of arguments: %d\n",argc);
    exit(1);
  }

  const char *inputFilename=argv[1];
  printf("Inputfile: %s\n",inputFilename);
  const char *outputFilename=argv[2];
  printf("Outputfile: %s\n",outputFilename);
  char garbage[2];
  int command;
  int radius=3;

  double transform[2][2];

  if(1!=sscanf(argv[3],"%d%1s",&command,garbage) || command<0 || command>10)
  {
    printf("Incorrect command\n");
    exit(1);
  }

  if(((command==0) && argc==5 && 1!=sscanf(argv[4],"%d%1s",&radius,garbage)) || radius<1)
  {
    printf("Incorrect radius value\n");
    exit(1);
  }
  /*test for transform case, must include path to text file with transform matrix specified*/
  	
  if(command==9)
  {
	const char *transformFilename=argv[4];
  	printf("Transform file: %s\n",transformFilename);
	FILE *fp;

	if((fp = fopen(transformFilename,"r")))
	{
		int i = 0;
		size_t count=0;
		char *linestring = NULL;
		for(i=0;i<2;i++){
			getline(&linestring,&count,fp);
			sscanf(linestring,"%lf %lf", &transform[i][0],&transform[i][1]);
		}
		free(linestring);
		fclose(fp);
	}
	else
	{
		printf("No transform matrix file. \n");
		exit(1);
	}
	
  }
  
  Filter *filters=initializeFilters(radius);
  Image *inputImage=decode(inputFilename);
  printf("Width: %d, height: %d\n",inputImage->width,inputImage->height);
  Image *outputImage=generateOutput(inputImage);

  uint8_t *inRed=inputImage->redChannel;
  uint8_t *inBlue=inputImage->blueChannel;
  uint8_t *inGreen=inputImage->greenChannel;
  uint8_t *inAlpha=inputImage->alphaChannel;
  uint8_t *outRed=outputImage->redChannel;
  uint8_t *outBlue=outputImage->blueChannel;
  uint8_t *outGreen=outputImage->greenChannel;
  uint8_t *outAlpha=outputImage->alphaChannel;
  int height=inputImage->height;
  int width=inputImage->width;


  switch(command)
  {
    case(0):
    {
      convolveImage(inRed,inGreen,inBlue,inAlpha,outRed,outGreen,outBlue,
                    outAlpha,filters[0].filter,filters[0].radius,width,height);
      encode(outputFilename,outputImage);
      break;
    }
    case(1):
    {
      convolveImage(inRed,inGreen,inBlue,inAlpha,outRed,outGreen,outBlue,
                    outAlpha,filters[1].filter,filters[1].radius,width,height);
      encode(outputFilename,outputImage);
      break;
    }
    case(2):
    {
      convolveImage(inRed,inGreen,inBlue,inAlpha,outRed,outGreen,outBlue,
                    outAlpha,filters[2].filter,filters[2].radius,width,height);
      encode(outputFilename,outputImage);
      break;
    }
    case(3):
    {
      convolveImage(inRed,inGreen,inBlue,inAlpha,outRed,outGreen,outBlue,
                    outAlpha,filters[3].filter,filters[3].radius,width,height);
      encode(outputFilename,outputImage);
      break;
    }
    case(4):
    {
      convolveImage(inRed,inGreen,inBlue,inAlpha,outRed,outGreen,outBlue,
                    outAlpha,filters[4].filter,filters[4].radius,width,height);
      encode(outputFilename,outputImage);
      break;
    }
    case(5):
    {
      convolveImage(inRed,inGreen,inBlue,inAlpha,outRed,outGreen,outBlue,
                    outAlpha,filters[5].filter,filters[5].radius,width,height);
      encode(outputFilename,outputImage);
      break;
    }
    case(6):
    {
      convertToGray(inRed,inGreen,inBlue,inAlpha,outRed,outGreen,outBlue,
                    outAlpha,gMonoMult,width,height);
      encode(outputFilename,outputImage);
      break;
     }
    case(7):
    {
      invertImage(inRed,inGreen,inBlue,inAlpha,outRed,outGreen,outBlue,
                  outAlpha,width,height);
      encode(outputFilename,outputImage);
      break;
    }
    case(8):
    {
      colorThreshold(inRed,inGreen,inBlue,inAlpha,outRed,outGreen,outBlue,
                  outAlpha,width,height,10,150,10);
      encode(outputFilename,outputImage);
      break;
    }
    case(9):
    {
      printf("Image Transformation\n");
      transformImage(inRed,inGreen,inBlue,inAlpha,outRed,outGreen,outBlue,outAlpha,transform,width,height);
      encode(outputFilename,outputImage);
      break;
    }
    case(10):
    {
      int row,col;
      const char *filterFilename=argv[4];
      printf("Target Image file: %s\n",filterFilename);
      Image *target=decode(filterFilename);
      detectImage(inRed,inGreen,inBlue,
                   inAlpha,&col,&row,target->redChannel,target->blueChannel,target->greenChannel,target->alphaChannel,
                   width,height,target->width,target->height);
      printf("Image Found at Row: %d Col: %d\n",row,col);
      freeImage(target);
      break;
    }
    default:
      exit(1);
  }

 
  free((double*)filters[0].filter);
  free(filters);
  freeImage(inputImage);
  freeImage(outputImage);
  return 0;
}
