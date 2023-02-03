#include <iostream>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
//#include <arm_neon.h>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <stdint.h>
#include <string>

//#include "perf_counter.h"
#include "conv.h"
#include "main.h"

using namespace cv;
using namespace std;


void ShowTheImage(string filename);
void ShowTheGrayImage(string filename);
void CamOn();
void FindEdge(string filename);
void Test_8();
void FilterSplit8();

int main(void) {

	//const struct options_Conv
	struct options_Conv options = {
		Conv_type_unknown,	//conv calculate type
		32,					//height
		32,					//width
		3,					//channel
		3,					//filter size : 3x3
		1,					//stride x
		1,					//stride y
		8,					//num of filter
		1,					//zero padding thickness
		151					//iteration
	};

	
	//CamOn();
	//ShowTheImage(TESTIMG);
	//ShowTheGrayImage(TESTIMG);
	//FindEdge(TESTIMG);
	Test_8();
	//FilterSplit8();
}

void ShowTheImage(string filename) {

	Mat img = imread(filename, 1);

	imshow("img", img);
	waitKey(0);

}

void ShowTheGrayImage(string filename) {
	Mat colorimg = imread(filename);
	Mat grayimg;
	cvtColor(colorimg, grayimg, COLOR_BGR2GRAY);
	imshow("Gray img", grayimg);
	waitKey(0);
}

void CamOn() {
	Mat frame;
	VideoCapture cap;

	int deviceID = 0;
	int apiID = cv::CAP_ANY;
	cap.open(deviceID, apiID);

	if (!cap.isOpened()) {
		cerr << "ERROR\n";
		return;
	}

	for (;;) {
		cap.read(frame);
		if (frame.empty()) {
			break;
		}
		imshow("Live", frame);
		if (waitKey(5) >= 0)
			break;
	}
	return;
}

void FindEdge(string filename) {
	Mat colorimg = imread(filename);
	Mat grayimg;
	
	cvtColor(colorimg, grayimg, COLOR_BGR2GRAY);
	GaussianBlur(grayimg, grayimg, Size(3, 3), 0);
	Mat result(grayimg.rows, grayimg.cols, 0);
	Mat result1(grayimg.rows, grayimg.cols, 0);
	Mat filter(3, 3, 0);
	uchar* filter_data = filter.data;

#if (FILTER == 1)
#if 1 // (vetical and parallel) (1) vs  (vertial or parallel) (0)
#if 0 //vertical (1) vs parallel (0)
	for (int i = 0; i < 9; i++) {
		if (i < 3) {
			filter_data[i] = -1;
		}
		else if (i < 6) {
			filter_data[i] = 0;
		}
		else if (i < 9) {
			filter_data[i] = 1;
		}
	}

	Conv2D((int8_t*)grayimg.data, (int8_t*)filter.data, (int8_t*)result.data, grayimg.rows, grayimg.cols,
		3, 1, 1, 1);
#else
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0) {
			filter_data[i] = -1;
		}
		else if (i % 3 == 1) {
			filter_data[i] = 0;
		}
		else if (i % 3 == 2) {
			filter_data[i] = 1;
		}
	}
	Conv2D((int8_t*)grayimg.data, (int8_t*)filter.data, (int8_t*)result.data, grayimg.rows, grayimg.cols,
		3, 1, 1, 1);
#endif
#else
	for (int i = 0; i < 9; i++) {
		if (i < 3) {
			filter_data[i] = -1;
		}
		else if (i < 6) {
			filter_data[i] = 0;
		}
		else if (i < 9) {
			filter_data[i] = 1;
		}
}

	Conv2D((int8_t*)grayimg.data, (int8_t*)filter.data, (int8_t*)result.data, grayimg.rows, grayimg.cols,
		3, 1, 1, 1);
	//#else
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0) {
			filter_data[i] = -1;
		}
		else if (i % 3 == 1) {
			filter_data[i] = 0;
		}
		else if (i % 3 == 2) {
			filter_data[i] = 1;
		}
	}
	Conv2D((int8_t*)grayimg.data, (int8_t*)filter.data, (int8_t*)result1.data, grayimg.rows, grayimg.cols,
		3, 1, 1, 1);
	uchar* out_data = result.data;
	uchar* out2_data = result.data;
	for (int i = 0; i < grayimg.rows * grayimg.cols; i++) {
		out_data[i] = out_data[i] / 2 + out2_data[i] / 2;
	}
#endif
#endif
#if (FILTER == 2)
	filter_data[0] = -3;
	filter_data[1] = -10;
	filter_data[2] = -3;
	filter_data[3] = 0;
	filter_data[4] = 0;
	filter_data[5] = 0;
	filter_data[6] = 3;
	filter_data[7] = 10;
	filter_data[8] = 3;

	Conv2D((int8_t*)grayimg.data, (int8_t*)filter.data, (int8_t*)result.data, grayimg.rows, grayimg.cols,
		3, 1, 1, 1);
#endif
#if (FILTER == 3)
	filter_data[0] = -1;
	filter_data[1] = -1;
	filter_data[2] = -1;
	filter_data[3] = -1;
	filter_data[4] = 8;
	filter_data[5] = -1;
	filter_data[6] = -1;
	filter_data[7] = -1;
	filter_data[8] = -1;

	Conv2D((int8_t*)grayimg.data, (int8_t*)filter.data, (int8_t*)result.data, grayimg.rows, grayimg.cols,
		3, 1, 1, 1);
#endif

	imshow("Find Edge", result);
	waitKey(0);

}

void Test_8() {

	
	Mat img = imread(TESTIMG8);
	Mat filter = imread(FILTER8);
	Mat grayimg;
	cvtColor(img, grayimg, COLOR_BGR2GRAY);
	cvtColor(filter, filter, COLOR_BGR2GRAY);
#if MULTIFIND
	Point coordinate[300];
	int coordinate_cnt=0;
#endif
	int pad = (filter.rows - filter.rows%2) / 2;
	int stridex = 1;
	int stridey = 1;
	int outsize_row = (grayimg.rows + pad * 2 - filter.rows + 1) / stridex ;
	int outsize_col = (grayimg.cols + pad * 2 - filter.cols + 1) / stridey ;
	int max=0, maxx, maxy;
	uint64_t* result = (uint64_t*)malloc(outsize_row * outsize_col * sizeof(uint64_t));
	memset(result, 0, outsize_row * outsize_col * sizeof(uint64_t));
	Mat outimg(outsize_row, outsize_col, 0);
	Mat outcolorimg(outsize_row, outsize_col, CV_8UC3);
	uchar* out_data = outimg.data;
	uchar* out_color_data = outcolorimg.data;

	Conv2D_int64((int8_t*)grayimg.data, (int8_t*)filter.data, (uint64_t*)result, grayimg.rows, grayimg.cols,
			filter.rows, stridex, stridey, pad);

	//Conv2D_32((int8_t*)grayimg.data, (int8_t*)filter.data, (uint32_t*)result, grayimg.rows, grayimg.cols,
	//	filter.rows, stridex, stridey, pad);


	/*#1 find score high*/
	for (int i = 0; i < outsize_row; i++) {
		for (int j = 0; j < outsize_col; j++) {
			/*#2 score view*/
			if (result[outsize_col * i + j] < 255*255*filter.rows*filter.rows && result[outsize_col * i + j] > THRESHOLD) {
#if MULTIFIND
				coordinate[coordinate_cnt] = Point(j, i);
				rectangle(img, Point(j - filter.rows / 2, i - filter.rows / 2), Point(j + filter.rows / 2 + filter.rows % 2, i + filter.rows / 2 + filter.rows % 2), Scalar(0, 255, 255), 1, 8, 0);
#endif
				out_data[outsize_col * i + j] = 255;
				out_color_data[3 * (outsize_col * i + j)] = 255;
				out_color_data[3 * (outsize_col * i + j) + 1] = 255;
				out_color_data[3 * (outsize_col * i + j) + 2] = 255;
				if (result[outsize_col * i + j] > max) {
					max = result[outsize_col * i + j];
					maxx = j;
					maxy = i;
				}
			}
		}
	}
	if (max > THRESHOLD) {
		cout << max << " (" << maxx << ", " << maxy << ")" << endl;
		
		rectangle(img, Point(maxx - filter.rows/2, maxy - filter.rows/2), Point(maxx + filter.rows/2 + filter.rows%2, maxy + filter.rows/2 + filter.rows%2), Scalar(255, 255, 0), 1, 8, 0);
		circle(outcolorimg, Point(maxx /* - filter.rows / 2*/, maxy /* - filter.rows / 2*/), 3, Scalar(255, 255, 0), -1);
	}
	else {
		cout << "not found" << endl;
	}
	
	circle(img, Point(outsize_row, outsize_col), 5, Scalar(255, 0, 0), -1);
	cout << outsize_row << " " << outsize_col << endl;

	imshow("test img 8", img);
	imshow("filter 8", filter);
	imshow("Conv result 8", outcolorimg);

	waitKey(0);
	free(result);
}

void FilterSplit8() {

	Mat img = imread(TESTIMG8);
	Mat filter1 = imread(SFILTER1);
	Mat filter2 = imread(SFILTER2);
	Mat filter3 = imread(SFILTER3);
	Mat filter4 = imread(SFILTER4);
	Mat grayimg, grayfilter1, grayfilter2, grayfilter3, grayfilter4 ;
	cvtColor(img, grayimg, COLOR_BGR2GRAY);
	cvtColor(filter1, grayfilter1, COLOR_BGR2GRAY);
	cvtColor(filter1, grayfilter2, COLOR_BGR2GRAY);
	cvtColor(filter1, grayfilter3, COLOR_BGR2GRAY);
	cvtColor(filter1, grayfilter4, COLOR_BGR2GRAY);

	int pad[4];
	int stridex[4] = { 1,1,1,1 };
	int stridey[4] = { 1,1,1,1 };
	int outsize_row[4];
	int outsize_col[4];
	int max[4] = { 0,0,0,0 };
	int maxx[4], maxy[4];

	pad[0] = (filter1.rows - filter1.rows % 2) / 2;
	pad[1] = (filter2.rows - filter2.rows % 2) / 2;
	pad[2] = (filter3.rows - filter3.rows % 2) / 2;
	pad[3] = (filter4.rows - filter4.rows % 2) / 2;

	outsize_row[0] = (grayimg.rows + pad[0] * 2 - filter1.rows + 1) / stridex[0];
	outsize_row[1] = (grayimg.rows + pad[1] * 2 - filter2.rows + 1) / stridex[1];
	outsize_row[2] = (grayimg.rows + pad[2] * 2 - filter3.rows + 1) / stridex[2];
	outsize_row[3] = (grayimg.rows + pad[3] * 2 - filter4.rows + 1) / stridex[3];

	outsize_col[0] = (grayimg.cols + pad[0] * 2 - filter1.cols + 1) / stridey[0];
	outsize_col[1] = (grayimg.cols + pad[1] * 2 - filter2.cols + 1) / stridey[1];
	outsize_col[2] = (grayimg.cols + pad[2] * 2 - filter3.cols + 1) / stridey[2];
	outsize_col[3] = (grayimg.cols + pad[3] * 2 - filter4.cols + 1) / stridey[3];

	uint32_t* result1 = (uint32_t*)malloc(outsize_row[0] * outsize_col[0] * sizeof(uint32_t));
	uint32_t* result2 = (uint32_t*)malloc(outsize_row[1] * outsize_col[1] * sizeof(uint32_t));
	uint32_t* result3 = (uint32_t*)malloc(outsize_row[2] * outsize_col[2] * sizeof(uint32_t));
	uint32_t* result4 = (uint32_t*)malloc(outsize_row[3] * outsize_col[3] * sizeof(uint32_t));

	memset(result1, 0, outsize_row[0] * outsize_col[0] * sizeof(uint32_t));
	memset(result2, 0, outsize_row[1] * outsize_col[1] * sizeof(uint32_t));
	memset(result3, 0, outsize_row[2] * outsize_col[2] * sizeof(uint32_t));
	memset(result4, 0, outsize_row[3] * outsize_col[3] * sizeof(uint32_t));

	Conv2D_32((int8_t*)grayimg.data, (int8_t*)filter1.data, (uint32_t*)result1, grayimg.rows, grayimg.cols,
		filter1.rows, stridex[0], stridey[0], pad[0]);
	Conv2D_32((int8_t*)grayimg.data, (int8_t*)filter2.data, (uint32_t*)result2, grayimg.rows, grayimg.cols,
		filter2.rows, stridex[1], stridey[1], pad[1]);
	Conv2D_32((int8_t*)grayimg.data, (int8_t*)filter3.data, (uint32_t*)result3, grayimg.rows, grayimg.cols,
		filter3.rows, stridex[2], stridey[2], pad[2]);
	Conv2D_32((int8_t*)grayimg.data, (int8_t*)filter4.data, (uint32_t*)result4, grayimg.rows, grayimg.cols,
		filter4.rows, stridex[3], stridey[3], pad[3]);

	for (int i = 0; i < outsize_row[0]; i++) {
		for (int j = 0; j < outsize_col[0]; j++) {
			/*#2 score view*/
			if (result1[outsize_col[0] * i + j] < 255 * 255 * filter1.rows * filter1.rows && result1[outsize_col[0] * i + j] > THRESHOLD) {
				if (result1[outsize_col[0] * i + j] > max[0]) {
					max[0] = result1[outsize_col[0] * i + j];
					maxx[0] = j;
					maxy[0] = i;
				}
			}
		}
	}

	for (int i = 0; i < outsize_row[1]; i++) {
		for (int j = 0; j < outsize_col[1]; j++) {
			/*#2 score view*/
			if (result2[outsize_col[1] * i + j] < 255 * 255 * filter2.rows * filter2.rows && result2[outsize_col[1] * i + j] > THRESHOLD) {
				if (result2[outsize_col[1] * i + j] > max[1]) {
					max[1] = result2[outsize_col[1] * i + j];
					maxx[1] = j;
					maxy[1] = i;
				}
			}
		}
	}

	for (int i = 0; i < outsize_row[2]; i++) {
		for (int j = 0; j < outsize_col[2]; j++) {
			/*#2 score view*/
			if (result3[outsize_col[2] * i + j] < 255 * 255 * filter3.rows * filter3.rows && result3[outsize_col[2] * i + j] > THRESHOLD) {
				if (result3[outsize_col[2] * i + j] > max[2]) {
					max[2] = result3[outsize_col[2] * i + j];
					maxx[2] = j;
					maxy[2] = i;
				}
			}
		}
	}

	for (int i = 0; i < outsize_row[3]; i++) {
		for (int j = 0; j < outsize_col[3]; j++) {
			/*#2 score view*/
			if (result4[outsize_col[3] * i + j] < 255 * 255 * filter4.rows * filter4.rows && result4[outsize_col[3] * i + j] > THRESHOLD) {
				if (result4[outsize_col[3] * i + j] > max[3]) {
					max[3] = result4[outsize_col[3] * i + j];
					maxx[3] = j;
					maxy[3] = i;
				}
			}
		}
	}

	if (max[0] > THRESHOLD) {
		rectangle(img, Point(maxx[0] - filter1.rows / 2, maxy[0] - filter1.rows / 2), 
			Point(maxx[0] + filter1.rows / 2 + filter1.rows % 2, maxy[0] + filter1.rows / 2 + filter1.rows % 2), 
			Scalar(255, 255, 0), 1, 8, 0);
	}
	else {
		cout << "filter1 : not found" << max[0] << endl;
	}

	if (max[1] > THRESHOLD) {
		rectangle(img, Point(maxx[1] - filter2.rows / 2, maxy[1] - filter2.rows / 2),
			Point(maxx[1] + filter2.rows / 2 + filter2.rows % 2, maxy[1] + filter2.rows / 2 + filter2.rows % 2),
			Scalar(255, 0, 255), 1, 8, 0);
	}
	else {
		cout << "filter2 : not found " << max[1] << endl;
	}
	
	if (max[2] > THRESHOLD) {
		rectangle(img, Point(maxx[2] - filter3.rows / 2, maxy[2] - filter3.rows / 2),
			Point(maxx[2] + filter3.rows / 2 + filter3.rows % 2, maxy[2] + filter3.rows / 2 + filter3.rows % 2),
			Scalar(0, 255, 255), 1, 8, 0);
	}
	else {
		cout << "filter3 : not found" << max[2] << endl;
	}

	if (max[3] > THRESHOLD) {
		rectangle(img, Point(maxx[3] - filter4.rows / 2, maxy[3] - filter4.rows / 2),
			Point(maxx[3] + filter4.rows / 2 + filter4.rows % 2, maxy[3] + filter4.rows / 2 + filter4.rows % 2),
			Scalar(255, 0, 0), 1, 8, 0);
	}
	else {
		cout << "filter4 : not found" << max[3] << endl;
	}


	imshow("IMG", img);
	imshow("filter 1", filter1);
	imshow("filter 2", filter2);
	imshow("filter 3", filter3);
	imshow("filter 4", filter4);

	resizeWindow("filter 1", 300, 200);
	resizeWindow("filter 2", 300, 200);
	resizeWindow("filter 3", 300, 200);
	resizeWindow("filter 4", 300, 200);

	waitKey(0);
	free(result1);
	free(result2);
	free(result3);
	free(result4);

}