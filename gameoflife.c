/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				Phat Tran
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Color** color = image->image;
	uint32_t num_rows = image->rows;
    uint32_t num_cols = image->cols;

    int cell = find_position(row, col, num_rows, num_cols);
    int left, right, up, down, up_left, up_right, down_left, down_right;

    left = find_position(row, col-1, num_rows, num_cols);
    right = find_position(row, col+1, num_rows, num_cols);
    up_left = find_position(row-1, col-1, num_rows, num_cols);
    up = find_position(row-1, col, num_rows, num_cols);
    up_right = find_position(row-1, col+1, num_rows, num_cols);
    down_left = find_position(row+1, col-1, num_rows, num_cols);
    down = find_position(row+1, col, num_rows, num_cols);
    down_right = find_position(row+1, col+1, num_rows, num_cols);


    Color* next_life = (Color*) malloc(sizeof(Color));
    if(!next_life) {
        exit(-1);
    }


    Color* pixel = color[cell];
    Color* ul = color[up_left];
    Color* u = color[up];
    Color* ur = color[up_right];
    Color* l = color[left];
    Color* r = color[right];
    Color* dl = color[down_left];
    Color* d = color[down];
    Color* dr = color[down_right];

    for(int i=0; i<3; i++) {
        uint8_t my_color, new_color;

        if(i==0) {
            my_color = pixel->R;
            new_color = pixel->R;
            for(int j=0; j<8; j++) {
                int alive_neighbors = 0;

                uint8_t cur = 1<<j;

                int my_bit = my_color&cur;

                if ((ul->R)&cur) {
                    alive_neighbors++;
                }
                if ((u->R)&cur) {
                alive_neighbors++;
                }
                if ((ur->R)&cur) {
                alive_neighbors++;
                }
                if ((l->R)&cur) {
                alive_neighbors++;
                }
                if ((r->R)&cur) {
                alive_neighbors++;
                }
                if ((dl->R)&cur) {
                alive_neighbors++;
                }
                if ((d->R)&cur) {
                alive_neighbors++;
                }
                if ((dr->R)&cur) {
                alive_neighbors++;
                }

                if (my_bit==0) {
                    my_bit = rule&(1<<(alive_neighbors));

                    if(my_bit>0){
                        new_color = new_color|(1<<j);
                    }
                } else if (my_bit>0) {

                    my_bit = rule&(1<<(alive_neighbors+9));
                    if(my_bit==0) {
                        new_color = new_color&( ~(1<<j));
                    }
                }
            }
            next_life->R = new_color;
        }

        if(i==1) {
            my_color = pixel->G;
            new_color = pixel->G;
            for(int j=0; j<8; j++) {
                int alive_neighbors = 0;

                uint8_t cur = 1<<j;

                int my_bit = my_color&cur;

                if ((ul->G)&cur) {
                    alive_neighbors++;
                }
                if ((u->G)&cur) {
                alive_neighbors++;
                }
                if ((ur->G)&cur) {
                alive_neighbors++;
                }
                if ((l->G)&cur) {
                alive_neighbors++;
                }
                if ((r->G)&cur) {
                alive_neighbors++;
                }
                if ((dl->G)&cur) {
                alive_neighbors++;
                }
                if ((d->G)&cur) {
                alive_neighbors++;
                }
                if ((dr->G)&cur) {
                alive_neighbors++;
                }

                if (my_bit==0) {
                    my_bit = rule&(1<<(alive_neighbors));

                    if(my_bit>0){
                        new_color = new_color|(1<<j);
                    }
                } else if (my_bit>0) {

                    my_bit = rule&(1<<(alive_neighbors+9));
                    if(my_bit==0) {
                        new_color = new_color&( ~(1<<j));
                    }
                }

            }
            next_life->G = new_color;
        }

        if(i==2) {
            my_color = pixel->B;
            new_color = pixel->B;
            for(int j=0; j<8; j++) {
                int alive_neighbors = 0;

                uint8_t cur = 1<<j;

                int my_bit = my_color&cur;

                if ((ul->B)&cur) {
                    alive_neighbors++;
                }
                if ((u->B)&cur) {
                alive_neighbors++;
                }
                if ((ur->B)&cur) {
                alive_neighbors++;
                }
                if ((l->B)&cur) {
                alive_neighbors++;
                }
                if ((r->B)&cur) {
                alive_neighbors++;
                }
                if ((dl->B)&cur) {
                alive_neighbors++;
                }
                if ((d->B)&cur) {
                alive_neighbors++;
                }
                if ((dr->B)&cur) {
                alive_neighbors++;
                }

                if (my_bit==0) {
                    my_bit = rule&(1<<(alive_neighbors));

                    if(my_bit>0){
                        new_color = new_color|(1<<j);
                    }
                } else if (my_bit>0) {

                    my_bit = rule&(1<<(alive_neighbors+9));
                    if(my_bit==0) {
                        new_color = new_color&( ~(1<<j));
                    }
                }

            }
            next_life->B = new_color;
        }

        }

    return next_life;
}
//Find_position of a cell in **Color array by using its col and row.
int find_position(int row, int col, int num_rows, int num_cols) {

    if (row == num_rows+1) {
        row = 1;
    } else if (row == 0 ) {
        row = num_rows;
    }
    if (col == num_cols+1) {
        col = 1;
    } else if (col == 0) {
        col = num_cols;
    }
    return (row-1)*(num_cols) + col - 1;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	uint32_t num_rows = image->rows;
    uint32_t num_cols = image->cols;

    Image* new_image = (Image*) malloc(sizeof(Image));
    if (!new_image) {
        exit(-1);
    }
    Color** new_color = (Color**) malloc(num_rows*num_cols*sizeof(Color*));
    if(!new_color) {
        exit(-1);
    }


    for(int i=1; i<=num_rows; i++) {
        for(int j=1; j<=num_cols; j++) {
            int pos = find_position(i, j, num_rows, num_cols);
            new_color[pos] = evaluateOneCell(image, i, j, rule);
        }
    }

    new_image->image = new_color;
    new_image->rows = num_rows;
    new_image->cols = num_cols;

    return new_image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if(argc!=3) {
        //printf("./gameOfLife\n");
        printf("usage: ./gameOfLife filename rule\n");
        printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
        printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
	    exit(-1);
	}

	char *pt;
    uint32_t rule = (uint32_t) strtol(argv[2], &pt, 16);

	Image *old_image, *new_image;

	old_image = readData(argv[1]);
	new_image = life(old_image, rule);
	writeData(new_image);

	freeImage(old_image);
	freeImage(new_image);
    return 0;
}
