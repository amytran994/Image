/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				Phat Tran
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object.
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename)
{
	//YOUR CODE HERE
FILE *fp = fopen(filename, "r");

uint32_t cols, rows;
fscanf(fp, "%*2s %u %u %*d", &cols, &rows);
uint32_t size = rows*cols;
Color** color = (Color**) malloc(size*sizeof(Color*));
if (!color) {
        exit(-1);
    }
Image* im = (Image*) malloc(sizeof(Image));
if (!im) {
        exit(-1);
    }

for (int i = 0; i < size; i++) {
    Color* pixel = (Color*) malloc(sizeof(Color));
    if (!pixel) {
            exit(-1);
        }

    uint8_t r;
    uint8_t g;
    uint8_t b;
    fscanf(fp, "%hhu %hhu %hhu", &r, &g, &b);
    pixel->R = r;
    pixel->G = g;
    pixel->B = b;
    color[i] = pixel;
    }
    im->image = color;
    im->cols = cols;
    im->rows = rows;

    return(im);
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	Color** color = image->image;
	uint32_t cols = image->cols;
    uint32_t rows = image->rows;
    printf("P3\n");
    printf("%u %u\n", cols, rows);
    printf("255\n");

    for (int i = 0; i < cols*rows; i++) {
        uint8_t c;
        for (int j=0; j<3; j++) {
            if (j==0) {
                c = color[i]->R;
            } else if (j==1) {
                c = color[i]->G;
            } else if (j==2) {
                c = color[i]->B;
            }
            if (j<2) {
                if (c<10) {
                    printf("  %hhu ", c);
                } else if (c>=10 && c<100) {
                    printf(" %hhu ", c);
                } else if (c>=100 && c<265) {
                    printf("%hhu ", c);
                }
            } else if (j==2) {
                if (c<10) {
                    printf("  %hhu", c);
                } else if (c>=10 && c<100) {
                    printf(" %hhu", c);
                } else if (c>=100 && c<265) {
                    printf("%hhu", c);
                }
                if ((i+1)%cols==0 && i>0) {
                    printf("\n");
                } else {
                    printf("   ");
                }
            }
        }
    }
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	Color** color = image->image;
	uint32_t cols = image->cols;
    uint32_t rows = image->rows;
    for (int i=0; i<rows*cols; i++) {
        free(color[i]);
    }
    free(color);
    free(image);

   color=NULL;
   cols=0;
   rows=0;
   image=NULL;
}

