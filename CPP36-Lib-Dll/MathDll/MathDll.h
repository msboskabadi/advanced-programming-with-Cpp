#pragma once


#define CALL_CNV	__stdcall
#define DllExport   __declspec( dllexport )


/*#ifdef __cplusplus
extern "C" {
#endif 
	DllExport float CALL_CNV mean(float* data, int N);
#ifdef __cplusplus
}
#endif*/


extern "C" {
	DllExport float CALL_CNV maxVal(float x, float y);
	DllExport float CALL_CNV mean(float* data, int N);
	DllExport unsigned char* CALL_CNV load_image(wchar_t* filename, int* W, int* H, int* step);
}