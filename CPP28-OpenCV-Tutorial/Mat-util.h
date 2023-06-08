#pragma once
#include "opencv.hpp"
//#include "Matrix.h"
#include <gdiplusheaders.h>
using namespace Gdiplus;
using namespace cv;

#ifndef __MAT_UTILIS_H__
#define __MAT_UTILIS_H__

#ifndef PI
#define PI 3.1415926535897932384626433832795//Pi Number
#endif

int Mat2CImage(Mat &mat, CImage &img);
void imrotate(cv::Mat& src, double angle, cv::Mat& dst);
cv::Mat ReadImage(const wchar_t* filename);

#endif