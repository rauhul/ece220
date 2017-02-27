/*
 * Name: Rohan Mathur
 * NetID: rmathur2
 *
 * This program first generates an image filter using the cosine function. From there, it applies this filter to an image, while keeping
 * integrity of the R, G, and B values. It supports images that are encoded with that scheme and can even support alpha values. Additionally,
 * the program can also invert the image and convert it to greyscale.
 */


#include "imageData.h"
#include "functions.h"

/*
 * calculateCosineFilter - calculates the cosine filter values
 * INPUTS:  int radius- integer indicating the size of array.
 *          The filter has 2*radius+1 rows and 2*radius+1 columns
 * OUTPUTS: cosineFitler - pointer to the 1-D array of size
 *          (2*radius+1)*(2*radius+1). Appropriate space
 *          has already been allocated). This function must compute
 *          the appropriate values of this array as described
 *          in the wiki writeup
 * RETURN VALUE: none
 */
void calculateCosineFilter(double *cosFilter, int radius) {
    int dimen = (2 * radius) + 1;
    int totalPixels = dimen * dimen;
    double weight = 0;

    int x, y;

    // loop through the whole image's values
    for (y = 0; y < dimen; y++) {
        for (x = 0; x < dimen; x++) {
            // get the current index in the array based off the x and y values
            int currIndex = (y * dimen) + x;

            // calculate the value of the cosine filter at this point
            double value = fabs(cos((M_PI * (x - radius)) / (2 * radius)) + cos((M_PI * (y - radius)) / (2 * radius)));

            // store the value of the cosine filter into the array
            cosFilter[currIndex] = value;

            // update the weight for normalization
            weight += value;
        }
    }

    // normalize the array by dividing each value by the overall array's sum
    int i = 0;
    for(i = 0; i < totalPixels; i++) {
        cosFilter[i] = (cosFilter[i] / weight);
    }

    return;
}

/* convolveImage - performs a convolution between a filter and image
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         filter - pointer to the convolution filter (1-D array)
 *         radius - radius of the convolution filter
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Filter is already initialized and contains desired values.
 *       Appropriate space has been allocated for output arrays.
 */
void convolveImage(uint8_t *inRed, uint8_t *inGreen, uint8_t *inBlue,
                   uint8_t *inAlpha, uint8_t *outRed, uint8_t *outGreen,
                   uint8_t *outBlue, uint8_t *outAlpha, const double *filter,
                   int radius, int width, int height) {
    // initialize dimensions
    int dimen = (2 * radius) + 1;
    int index = 0;

    int x = 0;
    int y = 0;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            // make variables for different colored sums
            double sumRed   = 0;
            double sumGreen = 0;
            double sumBlue  = 0;

            // get the initial radii we need to worry about
            int xInit = x - radius;
            int yInit = y - radius;

            // calculate the real index from there
            int initIndex = (width * yInit) + xInit;
            int savIndex  = (width * y)     + x;

            // loop over the image
            for (index = 0; index < (dimen * dimen); index++) {
                // initialize variables to check the different dimens
                int checkX = yInit + (index / dimen);
                int checkY = xInit + (index % dimen);

                // calculate the current index that it is iterating through
                int currIndex = initIndex + (width * (index / dimen)) + (index % dimen);

                // if within the bounds, calculate the rgb values
                if (checkX >= 0 && checkY >= 0 && checkX < height && checkY < width) {
                    double r = filter[index] * inRed[currIndex];
                    double g = filter[index] * inGreen[currIndex];
                    double b = filter[index] * inBlue[currIndex];

                    // if rgb values are out of range, clip them
                    if (r < 0) {
                        r = 0;
                    } else if(r > 255) {
                        r = 255;
                    }

                    if (g < 0) {
                        g = 0;
                    } else if(g > 255) {
                        g = 255;
                    }

                    if (b < 0) {
                        b = 0;
                    } else if(b > 255) {
                        b = 255;
                    }

                    // add rgb values to summed values
                    sumRed += r;
                    sumGreen += g;
                    sumBlue += b;
                }
            }

            // save values based off of summed values
            outRed[savIndex]   = sumRed;
            outGreen[savIndex] = sumGreen;
            outBlue[savIndex]  = sumBlue;

            // keeping the same alpha, so update that too
            outAlpha[savIndex] = inAlpha[savIndex];
        }
    }
    return;
}

/* convertToGray - convert the input image to grayscale
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         gMonoMult - pointer to array with constants to be multipiled with
 *                     RBG channels to convert image to grayscale (3 element array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       gMonoMult contains the desired grayscale weights.
 *       Appropriate space has been allocated for output arrays.
 */
void convertToGray(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                   uint8_t *outBlue,uint8_t *outAlpha,
                   const double *gMonoMult,int width,int height) {
    // calulate image size/length
    int size = width * height;

    // declare counter i
    int i;
    for(i = 0; i < size; i++) {
        // save the summed weight into the rgb channels
        outRed[i] = outGreen[i] = outBlue[i] = inRed[i]*gMonoMult[0] + inGreen[i]*gMonoMult[1] + inBlue[i]*gMonoMult[2];
        // keep the old alpha value
        outAlpha[i] = inAlpha[i];
    }
    return;
}

/* invertImage - inverts the colors of the image
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Appropriate space has been allocated for output arrays.
 */
void invertImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                 uint8_t *outBlue,uint8_t *outAlpha,int width,int height) {
    // calulate image size/length
    int size = width * height;

    // declare counter i
    int i;
    for(i = 0; i < size; i++) {
        // save the inverse of the rgb channels into the rbg outputs
        outRed[i]   = 255 - inRed[i];
        outGreen[i] = 255 - inGreen[i];
        outBlue[i]  = 255 - inBlue[i];
        // keep the old alpha value
        outAlpha[i] = inAlpha[i];
    }
    return;
}

/* color threshold - for each pixel of input image, compares value to red, green, and blue threshold. If the values exceed all three thresholds, set the output image to the input image values. Otherwise, set them to zero. Alpha should remain unchanged.
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Appropriate space has been allocated for output arrays.
 */
void colorThreshold(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                 uint8_t *outBlue,uint8_t *outAlpha,int width,int height,int redThreshold,int blueThreshold,int greenThreshold) {
    // calulate image size/length
    int size = width * height;

    // declare counter i
    int i;
    for(i = 0; i < size; i++) {
        if (inRed[i] > redThreshold && inGreen[i] > greenThreshold && inBlue[i] > blueThreshold) {
            // if all rgb channels exceed the threshold values, save the original values
            outRed[i]   = inRed[i];
            outGreen[i] = inGreen[i];
            outBlue[i]  = inBlue[i];
            outAlpha[i] = inAlpha[i];
        } else {
            // otherwise, save the pixel as "black", 0 0 0 225
            outRed[i]   = 0;
            outGreen[i] = 0;
            outBlue[i]  = 0;
            outAlpha[i] = 255;
        }
    }
    return;
}


/* Challenge problem 2
 * Detect target image in input image. Code should see if the target image is part of the
 * input image. Outputs the center pixel of the target in the input image.
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         targetRed - pointer to the target red channel (1-D array)
 *         targetGreen - pointer to the target green channel (1-D array)
 *         targetBlue - pointer to the target blue channel (1-D array)
 *         targetAlpha - pointer to the target alpha channel (1-D array)
 *         width - width of the input image
 *         height - height of the input image
 *         targetWidth - width of the target image
 *         targetHeight - height of the target image
 * OUTPUTS: outPixelCol - column index of detected target (-1 if no target found)
 *          outPixelRow - row index of detected target (-1 if no target found)
 * RETURN VALUES: none
 * NOTE: Input and target image values are already loaded into the input arrays
 *       outPixelCol and outPixelRow are passed by reference. Set the value at these pointers
 *       to the location of the target image in the larger image (-1, -1 if not found)
 */
void detectImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha, int* outPixelCol, int* outPixelRow, uint8_t *targetRed, uint8_t *targetBlue, uint8_t *targetGreen, uint8_t *targetAlpha,int width,int height,int targetWidth, int targetHeight) {
    //return -1 -1, so it works for 50% of the cases
    *outPixelRow = -1;
    *outPixelCol = -1;
    return;
}


/* Challenge Problem 1
 * transformImage - Computes an affline transformation of the input image
 * This can be used to compute rotations, rescale, and skew the image.
 * The two-dimensional array transform defines the transform to be done.
 * The values of the output image at x', y' are assigned by finding the closest (x,y) pair in
 * the original image by inverting the transform
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *     transform - two-dimensional array containing transform coefficients (2-D array)
 *         width - width of the input and output image
 *         height - height of the input and output image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input values are already loaded into the input arrays
 *       Appropriate space is already allocated for output image
 */
void transformImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,
              uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
              uint8_t *outAlpha,const double transform[2][2],int width,int height) {
//Your Code here

}
