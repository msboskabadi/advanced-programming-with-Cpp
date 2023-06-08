#pragma once

#ifndef SAFE_DELETE

#ifdef _DEBUG
#define SAFE_DELETE(p)  {if(p) {try{delete p; p = NULL;} catch(...){MessageBoxA(NULL,"Memory Can not be deleted.", "ERROR", 0);}}}
#define SAFE_DELETE_ARR(p)  {if(p) {try{delete [] p; p = NULL;} catch(...){MessageBoxA(NULL,"Array Memory Can not be deleted.", "ERROR", 0);}}}
#else
#define SAFE_DELETE(p)  {if(p) {try{delete p; p = NULL;} catch(...){;}}}
#define SAFE_DELETE_ARR(p)  {if(p) {try{delete [] p; p = NULL;} catch(...){;}}}
#endif

#endif

#define SAFE_DEL(data, len){if(len > 1) {SAFE_DELETE_ARR(data);} else {SAFE_DELETE(data)}};

enum EResampleMethod{rmNearest=0, rmBiLinear=1, rmBiCubic=2};//Resampling method (by now rmBicubic is not implemented)
enum EFilterType{FILTER_AVG=0, FILTER_UNSHARP=1};

struct SMatrix {
	SMatrix()
	{
		step = width = height = code = confidence = 0;
		pixel_count = 0; data = 0;
	}
	/*~SMatrix()
	{
	if(data)
	delete [] data;
	data = 0;
	}*/
	short step;
	short width;
	short height;
	short code;
	short confidence;
	union {
		int pixel_count; //number of black pixels (in the case of image sample)
		int byte_count; //size of the data buffer (in the case of raw sample (encoded))
	};
	unsigned char* data;
};


struct SRegion
{
	//@951009: int changed to short and two new params added
	short x0, y0, W, H;//start and end of area that must be recognized
	int nPxCount;//Number of dark pixels in this region
	int lbl;
	//@951009: int changed to short and two new params (tag1, tag2) added
	short code;
	union {
		short tag1;
		short row;
	};
	union {
		short tag2;
		short col;
	};
};

//Result of an input sample
struct SClassifierResult
{
	int winCode;//winner code
	double winVal;//winner value
	char* winString;//winner string(e.g. "A" for 10)
	double Certainty;//Certainty Confidence, max1*(max1-max2), the ideal value is 1;
	double* Confidences;//All output confidences including the winVal
};

struct SFeatureOptions
{
	int nCombinedFea;//number of combined features
	unsigned char SelectedFeatures[64];// Selected features
	int BackGround;//Back ground of input images. usually 0
	int ForeGround;//usually 1
	int PreProcess;//a combination of PRE_PROCESS using OR operator
	int width, height;//if PreProcessit includes Normalization, these are normal dimensions, else no means.
};
