/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				Phat Tran
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color** color = image->image;
	Color* new_pixel = (Color*) malloc(sizeof(Color));
	if (!new_pixel) {
            exit(-1);
        }
	int pos = (row-1)*(image->cols) + col - 1;
	Color* pixel = color[pos];
	uint8_t blue = pixel->B;
	int i = blue&1;
	if (i==0) {
        new_pixel->R = 0;
        new_pixel->G = 0;
        new_pixel->B = 0;
	} else if (i==1) {
        new_pixel->R = 255;
        new_pixel->G = 255;
        new_pixel->B = 255;
	}

	return new_pixel;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	uint32_t rows = image->rows;
	uint32_t cols = image->cols;
	int size = rows*cols;

	Color** bw = (Color**) malloc(size*sizeof(Color*));
	if (!bw) {
        exit(-1);
    }
	Image* new_image = (Image*) malloc(sizeof(Image));
	if (!new_image) {
        exit(-1);
    }

    for (int i=1; i<=rows; i++) {
        for (int j=1; j<=cols; j++) {
            int pos = (i-1)*(cols) + j - 1;
            bw[pos] = evaluateOnePixel(image, i, j);
        }
    }
    new_image->image= bw;
    new_image->rows = rows;
    new_image->cols = cols;

    return new_image;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/

int main(int argc, char **argv)
{
	Image *old_image;
	Image *new_image;

    if (argc != 2) {
		exit(-1);
	}
	old_image = readData(argv[1]);
	new_image = steganography(old_image);
	writeData(new_image);

	freeImage(old_image);
	freeImage(new_image);

	return 0;
}