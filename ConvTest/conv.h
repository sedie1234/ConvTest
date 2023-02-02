#pragma once
#include <stdio.h>
#include <stdint.h>
#include "main.h"


/*my conv : like output stationary*/
bool Conv2D_int64(int8_t* input, int8_t* filter, uint64_t* output, int h, int w, /*int c,*/ int size, int stride_x, int stride_y, int padding/*, int n*/);
bool Conv2D_32(int8_t* input, int8_t* filter, uint32_t* output, int h, int w, /*int c,*/ int size, int stride_x, int stride_y, int padding/*, int n*/);
bool Conv2D(int8_t* input, int8_t* filter, int8_t* output, int h, int w, /*int c,*/ int size, int stride_x, int stride_y, int padding/*, int n*/);
bool Conv3D(int8_t* input, int8_t* filter, int8_t* output, int h, int w, int c, int size, int stride_x, int stride_y, int padding, int n);

/*darknet conv*/
int8_t im2col_get_pixel(int8_t* im, int height, int width, int channels, int row, int col, int channel, int pad);
void forward_convolutional_layer(int8_t* input, int8_t* filter, int8_t* output, options_Conv options);
void im2col(int8_t* input, int channels, int height, int width, int ksize, int stride_x, int stride_y, int pad, int8_t* input_col);
void gemm(int8_t* input, int8_t* filter, int8_t* output, int m, int n, int k);
