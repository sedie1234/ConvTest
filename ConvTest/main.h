#pragma once

#define THRESHOLD	1000
#define FILTER		3
//for function TEST_8
//#define TESTIMG		"img.jpg"
//#define TESTIMG		"testimg.jfif"
#define TESTIMG		"rena.jfif"
#define TESTIMG8	"8_test1.bmp"
#define FILTER8		"8_filter.bmp"

//for funtion FilterSplit
#define SFILTER1	"8_filter_1.png"
#define SFILTER2	"8_filter_2.png"
#define SFILTER3	"8_filter_3.png"
#define SFILTER4	"8_filter_4.png"

enum Conv_type {
	Conv_type_unknown,
	Conv_type_2D,
	Conv_type_3D,
	Conv_type_darknet,
};

typedef struct options_Conv {
	enum Conv_type type;
	size_t h;
	size_t w;
	size_t c;
	size_t size;
	size_t stride_x;
	size_t stride_y;
	size_t n;
	size_t padding;
	size_t iterations;
}options_Conv;