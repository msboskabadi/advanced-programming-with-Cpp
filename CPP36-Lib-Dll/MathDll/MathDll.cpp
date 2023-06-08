// MathDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MathDll.h"
#include <opencv.hpp>

#include "Mat-util.h"
#ifdef _DEBUG
#pragma comment (lib, "opencv_world470d.lib")
#else
#pragma comment (lib, "opencv_world470.lib")
#endif

cv::Mat img;

DllExport uchar* CALL_CNV load_image(wchar_t* filename, int* W, int* H, int* step)
{
	img = ReadImage(filename);
	if (W)
		*W = img.cols;
	if (H)
		*H = img.rows;
	if (step)
		*step = img.step[0];
	return img.data;
}

DllExport float CALL_CNV maxVal(float x, float y)
{
	if (x > y)
		return x;
	else
		return y;
}

DllExport float CALL_CNV mean(float* data, int N)
{
	float m = 0;
	for (size_t i = 0; i < N; i++)
	{
		m += data[i];
	}

	if (N)
		return m / N;

	return 0;
}