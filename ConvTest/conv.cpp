#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
//#include <arm_neon.h>
#include <stdint.h>
#include "conv.h"
#include "main.h"

bool Conv2D_int64(int8_t* input, int8_t* filter, uint64_t* output, int h, int w, /*int c,*/ int size, int stride_x, int stride_y, int padding/*, int n*/) {

	int8_t* inputArr;
	int inputSize = 0; //just the number of data
	int outputSize = 0; //just the number of data
	int8_t* prein;
	int8_t* pin;
	int8_t* pfilter;
	uint64_t* pout;
	int8_t* ppos;
	int8_t* pSpos;
	int8_t* pfilterS;

	int i, j, p, q;

	//stride check with padding (valid?)
	if (0) {
		return false;
	}

	//make inputarr include padding

	inputSize = (h + padding * 2) * (w + padding * 2)/* * c*/;
	inputArr = (int8_t*)malloc(sizeof(int8_t) * inputSize);
	//memset(inputArr, 0, sizeof(int8_t) * inputSize);

	pin = input;
	prein = inputArr;

	//	outputSize = (h + padding * 2 - size / 2 - size % 2) / stride_y * (w + padding * 2 - size / 2 - size % 2) / stride_x;
	//	output = (int8_t*)malloc(sizeof(int8_t) * outputSize);

		//reform// input -> input + padding = inputArr 
		//for (i = 0; i < c; i++) {
	for (j = 0; j < h + padding * 2; j++) {
		for (p = 0; p < w + padding * 2; p++) {
			if (p<padding | p>w + padding - 1 | j<padding | j>h + padding - 1) {
				*prein = 0;
			}
			else {
				*prein = *pin;
				pin++;
			}
			prein++;
		}
	}
	//}

	//print(inputArr, 100, 10);

	for (q = 0; q < size; q++) {
		pfilterS = filter + q * size * sizeof(int8_t);
		pSpos = inputArr + q * (h + padding * 2) * sizeof(int8_t);
		pout = output;
		for (i = q; i < q + (h + padding * 2 - size) / stride_y + 1; i++) {
			for (j = 0; j < (w + padding * 2 - size) / stride_x + 1; j++) {
				pfilter = pfilterS;
				ppos = pSpos;
				for (p = 0; p < size; p++) {
					*pout = *pout + *pfilter * (*ppos);
					ppos++;
					pfilter++;
				}
				pSpos += stride_x * sizeof(int8_t);
				pout++;
			}
			pSpos = inputArr + (i + 1) * stride_y * (w + padding * 2) * sizeof(int8_t);
		}
	}
	free(inputArr);

	return 0;
}

bool Conv2D_32(int8_t* input, int8_t* filter, uint32_t* output, int h, int w, /*int c,*/ int size, int stride_x, int stride_y, int padding/*, int n*/) {

	int8_t* inputArr;
	int inputSize = 0; //just the number of data
	int outputSize = 0; //just the number of data
	int8_t* prein;
	int8_t* pin;
	int8_t* pfilter;
	uint32_t* pout;
	int8_t* ppos;
	int8_t* pSpos;
	int8_t* pfilterS;

	int i, j, p, q;

	//stride check with padding (valid?)
	if (0) {
		return false;
	}

	//make inputarr include padding

	inputSize = (h + padding * 2) * (w + padding * 2)/* * c*/;
	inputArr = (int8_t*)malloc(sizeof(int8_t) * inputSize);
	//memset(inputArr, 0, sizeof(int8_t) * inputSize);

	pin = input;
	prein = inputArr;

	//	outputSize = (h + padding * 2 - size / 2 - size % 2) / stride_y * (w + padding * 2 - size / 2 - size % 2) / stride_x;
	//	output = (int8_t*)malloc(sizeof(int8_t) * outputSize);

		//reform// input -> input + padding = inputArr 
		//for (i = 0; i < c; i++) {
	for (j = 0; j < h + padding * 2; j++) {
		for (p = 0; p < w + padding * 2; p++) {
			if (p<padding | p>w + padding - 1 | j<padding | j>h + padding - 1) {
				*prein = 0;
			}
			else {
				*prein = *pin;
				pin++;
			}
			prein++;
		}
	}
	//}

	//print(inputArr, 100, 10);

	for (q = 0; q < size; q++) {
		pfilterS = filter + q * size * sizeof(int8_t);
		pSpos = inputArr + q * (h + padding * 2) * sizeof(int8_t);
		pout = output;
		for (i = q; i < q + (h + padding * 2 - size) / stride_y + 1; i++) {
			for (j = 0; j < (w + padding * 2 - size) / stride_x + 1; j++) {
				pfilter = pfilterS;
				ppos = pSpos;
				for (p = 0; p < size; p++) {
					*pout = *pout + *pfilter * (*ppos);
					ppos++;
					pfilter++;
				}
				pSpos += stride_x * sizeof(int8_t);
				pout++;
			}
			pSpos = inputArr + (i + 1) * stride_y * (w + padding * 2) * sizeof(int8_t);
		}
	}
	free(inputArr);

	return 0;
}


bool Conv2D(int8_t* input, int8_t* filter, int8_t* output, int h, int w, /*int c,*/ int size, int stride_x, int stride_y, int padding/*, int n*/) {

	int8_t* inputArr;
	int inputSize = 0; //just the number of data
	int outputSize = 0; //just the number of data
	int8_t* prein;
	int8_t* pin;
	int8_t* pfilter;
	int8_t* pout;
	int8_t* ppos;
	int8_t* pSpos;
	int8_t* pfilterS;

	int i, j, p, q;

	//stride check with padding (valid?)
	if (0) {
		return false;
	}

	//make inputarr include padding

	inputSize = (h + padding * 2) * (w + padding * 2)/* * c*/;
	inputArr = (int8_t*)malloc(sizeof(int8_t) * inputSize);
	//memset(inputArr, 0, sizeof(int8_t) * inputSize);

	pin = input;
	prein = inputArr;

	//	outputSize = (h + padding * 2 - size / 2 - size % 2) / stride_y * (w + padding * 2 - size / 2 - size % 2) / stride_x;
	//	output = (int8_t*)malloc(sizeof(int8_t) * outputSize);

		//reform// input -> input + padding = inputArr 
		//for (i = 0; i < c; i++) {
	for (j = 0; j < h + padding * 2; j++) {
		for (p = 0; p < w + padding * 2; p++) {
			if (p<padding | p>w + padding - 1 | j<padding | j>h + padding - 1) {
				*prein = 0;
			}
			else {
				*prein = *pin;
				pin++;
			}
			prein++;
		}
	}
	//}

	//print(inputArr, 100, 10);

	for (q = 0; q < size; q++) {
		pfilterS = filter + q * size * sizeof(int8_t);
		pSpos = inputArr + q * (h + padding * 2) * sizeof(int8_t);
		pout = output;
		for (i = q; i < q + (h + padding * 2 - size) / stride_y + 1; i++) {
			for (j = 0; j < (w + padding * 2 - size) / stride_x + 1; j++) {
				pfilter = pfilterS;
				ppos = pSpos;
				for (p = 0; p < size; p++) {
					*pout = *pout + *pfilter * (*ppos);
					ppos++;
					pfilter++;
				}
				pSpos += stride_x * sizeof(int8_t);
				pout++;
			}
			pSpos = inputArr + (i + 1) * stride_y * (w + padding * 2) * sizeof(int8_t);
		}
	}
	free(inputArr);

	return 0;
}

bool Conv3D(int8_t* input, int8_t* filter, int8_t* output, int h, int w, int c, int size, int stride_x, int stride_y, int padding, int n) {

	int i, j, p;
	int tempOutSize = ((h + padding * 2 - size) / stride_y + 1) * ((w + padding * 2 - size) / stride_x + 1);
	int8_t* pout;
	int8_t* ptempOut;
	int8_t* tempOut;
	int8_t* tempIn;
	int8_t* tempFilter;
	int8_t* pfilter;
	tempOut = (int8_t*)malloc(sizeof(int8_t) * tempOutSize);
	//tempIn = (int8_t*)malloc(sizeof(int8_t) * h * w);


/*filter
* |1 2 3| |11 12 13|
* |4 5 6| |14 15 16|
* |7 8 9| |17 18 19| .....
*
* 1 2 3 / 4 5 6 / 7 8 9  || 11 12 13 / 14 15 16 / 17 18 19 || ....
* */
	for (p = 0; p < n; p++) {

		pout = output + p * tempOutSize * sizeof(int8_t);
		pfilter = filter + p * size * size * c * sizeof(int8_t);
		for (i = 0; i < c; i++) {
			ptempOut = tempOut;
			memset(tempOut, 0, sizeof(int8_t) * tempOutSize);
			tempIn = input + i * w * h * sizeof(int8_t);
			tempFilter = pfilter + i * size * size * sizeof(int8_t);
			Conv2D(tempIn, tempFilter, tempOut, h, w, size, stride_x, stride_y, padding);
			for (j = 0; j < tempOutSize; j++) {
				*pout = *pout + *ptempOut;
				ptempOut++;
				pout++;
			}
		}

	}

	free(tempOut);

	return 0;
}

int8_t im2col_get_pixel(int8_t* im, int height, int width, int channels, int row, int col, int channel, int pad)
{
	row -= pad;
	col -= pad;

	if (row < 0 || col < 0 ||
		row >= height || col >= width) return 0;
	return im[col + width * (row + height * channel)];
}

void im2col(int8_t* input, int channels, int height, int width, int ksize, int stride_x, int stride_y, int pad, int8_t* input_col) {

	int c, h, w;
	int height_col = (height + 2 * pad - ksize) / stride_y + 1;
	int width_col = (width + 2 * pad - ksize) / stride_x + 1;

	int channels_col = channels * ksize * ksize;
	for (c = 0; c < channels_col; ++c) {
		int w_offset = c % ksize;
		int h_offset = (c / ksize) % ksize;
		int c_im = c / ksize / ksize;
		for (h = 0; h < height_col; ++h) {
			for (w = 0; w < width_col; ++w) {
				int im_row = h_offset + h * stride_y;
				int im_col = w_offset + w * stride_x;
				int col_index = (c * height_col + h) * width_col + w;
				input_col[col_index] = im2col_get_pixel(input, height, width, channels,
					im_row, im_col, c_im, pad);
			}
		}
	}

}

void gemm(int8_t* input, int8_t* filter, int8_t* output, int m, int n, int k) {

	int8_t* pin;
	int8_t* pf;
	int8_t* pout;

	pin = input;
	pf = filter;
	pout = output;

	int i, j, p;

	for (i = 0; i < m; ++i) {
		for (p = 0; p < k; ++p) {
			/*PUT_IN_REGISTER*/ int8_t A_PART = input[i * k + p];
			for (j = 0; j < n; ++j) {
				output[i * n + j] += A_PART * filter[p * n + j];
			}
		}
	}

}


void forward_convolutional_layer(int8_t* input, int8_t* filter, int8_t* output, options_Conv options) {

	int out_h = (options.h + options.padding * 2 - options.size) / options.stride_y + 1;
	int out_w = (options.w + options.padding * 2 - options.size) / options.stride_x + 1;

	int m = options.n;
	int k = options.size * options.size * options.c;
	int n = out_h * out_w;

	int i, j, p, q;

	/*
	*a = l.weigths //filter
	*b = state.workspace //input
	*c = l.output //output
	*/

	int width_col = (options.w + 2 * options.padding - options.size) / options.stride_x + 1;
	int height_col = (options.h + 2 * options.padding - options.size) / options.stride_y + 1;
	int channels_col = options.c * options.size * options.size;

	int8_t* input_col;
	input_col = (int8_t*)malloc(sizeof(int8_t) * width_col * height_col * channels_col);
	memset(input_col, 0, sizeof(int8_t) * width_col * height_col * channels_col);

	im2col(input, options.c, options.h, options.w, options.n, options.stride_x, options.stride_y, options.padding, input_col);

	gemm(filter, input_col, output, m, n, k);

	free(input_col);


}
