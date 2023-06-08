#pragma once

#include "CommonDefs.h"
#include <cassert>
#include <typeinfo>
#include <Math.h>
//#include <omp.h>
#include <atlstr.h>
#include <windows.h>
#include <WinDef.h>


#define USE_MALLOC_MX

//How we must care of invalid arguments like invalid indices or data
#define MX_SAFETY_LEVEL  0//@ introduced @ 940211

//#define max(a,b) ((a)>(b)?(a):(b))
//#define min(a,b) ((a)<(b)?(a):(b))

extern FILE* _fp_log;
static bool save_image_for_analysis_and_exit = false;
#define VISUALC
#ifdef VISUALC
#include <atlimage.h>
#endif

typedef unsigned char byte;

#ifndef _WIN32
#define MessageBoxA(wnd, msg, cap, icon) std::cout << cap << ": " << msg
typedef char TCHAR;
#endif

#ifdef USE_MALLOC_MX
#define MEM_ALLOC_MX(len) (_T*)malloc(len*sizeof(_T))
#define MEM_FREE_MX(p) {if(p) free(p); p = 0;}
#else
#define MEM_ALLOC_MX(len) new _T[len]
#define MEM_FREE_MX(p) {if(p) delete [] p; p = 0;}
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#define CHECK_SHARE(dst) if(!dst){\
	assert(!shared);\
	if(shared) return false;\
}
//#define Matrix_TRACE
inline void ShowMsg(char* Msg = "An Error occurred", int Code = 0, char* Caption = "Error")
{
	char str[260] = "";
	if(Code != 0)
		sprintf_s(str, 260, "%s", Msg);
	else
		sprintf_s(str, 260, "%s - Code: %d", Msg, Code);

	MessageBoxA(NULL, str, Caption, MB_ICONERROR);
}

//utility class to provide [][] operator
template <typename _T>
class CMatrixVec
{
public:
	CMatrixVec(){W = 0; data = 0; dedicated_data = false;}
	void init(int width, _T* ptr) {W = width; data = ptr;}

	~CMatrixVec()
	{
		if(dedicated_data && data)
		{
			SAFE_DEL(data, W);
		}
	}
	_T* data;

	inline operator _T*()
	{
		return data;
	}

	inline _T& operator[](int x)
	{
		assert((x < W) && (x > -1) && data);
#if (MX_SAFETY_LEVEL > 1)
		if(x >= W || x < 0 || !data)
		{
			//char temp[100] = {0};
			//sprintf(temp, "y = %d (H = %d) (data = %d)", y, H, data);
			//MessageBoxA(NULL, temp, "", 0);
			fprintf(_fp_log, "** CMatrixVec[x]: x = %d (W = %d) (data = %d)\n", x, W, data);
			fflush(_fp_log);
			save_image_for_analysis_and_exit = true;
			static _T fake = 0;
			return fake;
		}
#endif
		return data[x];
	}
	int W;
	bool dedicated_data;
};


enum MatrixType{mtGeneral=-1, mtBinary=0, mtGray=1};
template <typename _T>
class CMatrix
{
public:
	//friend double* WINAPI GetFeatures(byte* Mx, WORD W, WORD H, int &FeaLen);
	void MakeEmptyMatrix()
	{
		_vector = 0;
		data = NULL; shared = shared_vec = false; 
		this->W = 0; this->H = 0;//Don't remove this line, see init definition
		/*id = ++Counter;*/
		std::string str = typeid(_T).raw_name();
		bClassType = (str[0] == '.' && str[1] == '?');
		mxType = mtGeneral;
	}
	CMatrix(){
		MakeEmptyMatrix();
		SetId();
	}
	CMatrix(CMatrix &copy) {
		MakeEmptyMatrix();
		Copy(&copy);
		SetId();
	}
	CMatrix(CMatrix* src, bool shared_data = false) {
		MakeEmptyMatrix();
		Copy(src, shared_data);
		SetId();
	}
	~CMatrix()
	{
		//MessageBox(NULL, label, "", 0);
		Clear();
		ShowId();
	}
	CMatrix(int H, int W, bool bFill = true, byte Fill = 0, MatrixType type = mtGeneral){
		MakeEmptyMatrix();
		mxType = type;
		init(H, W, bFill, Fill);
		SetId();
	}


	CMatrix(int H, int W, _T *pData, bool sharedData = false, MatrixType type = mtGeneral){
		MakeEmptyMatrix();
		mxType = type;
		init2(H, W, pData, sharedData);
		SetId();
	}
	bool init(int H, int W, bool bFill = true, byte Fill = 0)
	{
		if((this->H == H) && (this->W == W)){
			if(bFill && (!bClassType)){
				memset(data, Fill, W*H*sizeof(_T));
			}
			return true;
		}
		try{
			Clear();
			if(W*H <= 0) return true;
			this->W = W;
			this->H = H;
			data = MEM_ALLOC_MX(W*H);
			if(! data){
				this->W = 0;
				this->H = 0;
				ShowMsg("Memory allocation failure!");
				return false;
			}
			_vector = new CMatrixVec<_T>[H];
			for (int y = 0; y < H; y++){
				_vector[y].init(W, data + y*W);
			}

			if(bFill && (!bClassType)){
				memset(data, Fill, W*H*sizeof(_T));
			}
		}catch (...) {
#ifdef Matrix_TRACE
			char str[512] = {0};
			sprintf(str, "Error in initializing CMatrix (H: %d, W: %d, bFill: %d, Fill: %d)", H, W, bFill, Fill);
			ShowError(str);
#endif
			static FILE* fpMx = NULL;
			if(!fpMx){
				//ShowError("Matrix init first time failure!");
				//fpMx = fopen("Matrix.log", "wt");
			}
			if(fpMx){
				//fprintf(fpMx, "Error (H: %d, W: %d, bFill: %d, Fill: %d, this->H: %d, this->W: %d, data: %d)\n", H, W, bFill, Fill, this->H, this->W, data);
				//fflush(fpMx);
			}

			if(this->W == 0 && this->H == 0);//Clear succeeded
			else{//continue without clearing
				this->W = W;
				this->H = H;
				data = MEM_ALLOC_MX(W*H);
				if(! data){
					this->W = 0;
					this->H = 0;
					ShowMsg("Matrix.init: Memory allocation failed!");
					//fprintf(fpMx, "After Handling: Memory allocation failed\n");
					//fflush(fpMx);
					return false;
				}
				if(bFill && (!bClassType)){
					memset(data, Fill, W*H*sizeof(_T));
				}
			}
			if(fpMx){
				//fprintf(fpMx, "After Handling (this->H: %d, this->W: %d, data: %d)\n\n", this->H, this->W, data);
				//fflush(fpMx);
			}

			ShowMsg("Matrix.init Failed(may be due to Memory Allocation Failure!)");
			return false;
		}
		return true;
		//this->label = label;
	}

	//<sharedData> MUST BE FALSE IN ALMOST ALL CASES, only use it
	//after reading the comments on <shared> member
	bool init2(int H, int W, _T *pData, bool sharedData = false)
	{
		try{
			Clear();
			if(! W*H) return true;
			shared = sharedData;			
			std::string str = typeid(_T).raw_name();
			bClassType = (str.substr(0,2) == std::string(".?"));
			if(! pData)	return false;
			if(shared){
				data = pData;
				this->W = W;
				this->H = H;
			}
			else{
				init(H, W, false);
				if(! data) throw -1;
				if((H <= 0) || (W <= 0)) throw -2;
				if(! bClassType)
					memcpy(data, pData, W*H*sizeof(_T));
				else
					for (int i = 0; i < W*H; i++) data[i] = pData[i];
			}

			shared_vec = false;
			_vector = new CMatrixVec<_T>[H];
			for (int y = 0; y < H; y++)
				_vector[y].init(W, data + y*W);
			

		}catch (...){
			MessageBoxA(0,"ERROR IN CREATING Matrix", "CMatrix(int H, int W, _T *pData, bool shared = false)", 0);
			return false;
		}
		return true;
	}
	bool RemoveGrainNoise(CMatrix<_T> *dst = NULL, int Ksize = 3, int backGround = 0, bool KeepVerticalLines = true){//use only for binary images
		if((W < 12) || (H < 12))
			return true;
		CHECK_SHARE(dst);

		CMatrix<_T> *Result = NULL;
		if(!dst) Result = new CMatrix<_T>;
		else Result = dst;
		Result->Copy(this);

		int kmin = Ksize/2;
		int kmax = Ksize-kmin;
		int cnt, yStart, xStart, yEnd, xEnd;
		if(KeepVerticalLines){
			for (int y = 0; y < H; y++){
				for (int x = 0; x < W; x++){
					yStart = (y-kmin > -1) ? y-kmin : 0;
					yEnd = (y+kmax <= H) ? y+kmax : H;
					xStart = (x-kmin > -1) ? x-kmin : 0;
					xEnd = (x+kmax <= W) ? x+kmax : W;
					cnt = 0;
					//preserve vertical lines
					bool restor = true;
					for (int y0 = yStart; y0 < yEnd; y0++){
						if(Get(y0, x) == backGround)
							restor = false;
						for (int x0 = xStart; x0 < xEnd; x0++)
							if(Get(y0, x0) == backGround)
								cnt++;
					}
					//preserve vertical lines
					if (restor)
						for (int y0 = yStart; y0 < yEnd; y0++)
							Result->Set(y0, x, 1-backGround);
					else if(cnt > ((yEnd-yStart)*(xEnd-xStart)/2))
						Result->Set(y, x, backGround);
					//else
					//mx.Set(y, x, 1-backGround);
				}
			}
		}
		else{
			for (int y = 0; y < H; y++){
				for (int x = 0; x < W; x++){
					yStart = (y-kmin > -1) ? y-kmin : 0;
					yEnd = (y+kmax <= H) ? y+kmax : H;
					xStart = (x-kmin > -1) ? x-kmin : 0;
					xEnd = (x+kmax <= W) ? x+kmax : W;
					cnt = 0;
					for (int y0 = yStart; y0 < yEnd; y0++){
						for (int x0 = xStart; x0 < xEnd; x0++)
							if(Get(y0, x0) == backGround)
								cnt++;
					}
					if(cnt > ((yEnd-yStart)*(xEnd-xStart)/2))
						Result->Set(y, x, backGround);
				}
			}
		}
		if(! dst){
			Copy(Result);
			SAFE_DELETE(Result);
		}
	};
	static int CompareValues(const void *elem1, const void *elem2){
		_T v1 = *(_T*)elem1;
		_T v2 = *(_T*)elem2;
		return v1 - v2;
	};
	

	void SaveToCSV(TCHAR* fileName, TCHAR* format = NULL){
		FILE* fp = _tfopen(fileName, _T("wt"));
		if (!format)
			format = _T("%.3d,");
		for (int y = 0; y < H; y++){
			for (int x = 0; x < W; x++)
				_ftprintf(fp, format, Get(y,x));
			_ftprintf(fp, _T("\n"));
		}
		fclose(fp);
	}
#ifdef VISUALC
	void SaveToImage(TCHAR* fileName, int x0 = 0, int y0 = 0, int w = 0, int h = 0){
		CImage img;
		if(y0 < 0) y0 = 0;
		if(x0 < 0) x0 = 0;
		if((w > W) || (w == 0)) w = W - x0;
		if((h > H) || (h == 0)) h = H - y0;
		img.Create(w, h, 8);
		static RGBQUAD pRGB[256];
		for (int i = 0; i < 256; i++)
			pRGB[i].rgbBlue = pRGB[i].rgbGreen = pRGB[i].rgbRed = i;
		img.SetColorTable(0, 256, pRGB);
		if(mxType == mtBinary)
			for (int y = y0; y < y0+h; y++){
				byte* ptr = (byte*)img.GetPixelAddress(0, y-y0);
				for (int x = x0; x < x0+w; x++)
					*ptr++ = 255-Get(y, x)*255;
			}
		else if (mxType == mtGray)
			for (int y = y0; y < y0+h; y++){
				byte* ptr = (byte*)img.GetPixelAddress(0, y-y0);
				for (int x = x0; x < x0+w; x++)
					*ptr++ = (byte)Get(y, x);
			}
		else if(mxType == mtGeneral){
			_T m0 = minVal(); _T m1 = maxVal();
			if(m1 == m0) m1 = m0+1;
			else if((m1 == 1) && (m0 == 0)){//binary image
				m1 = 0; m0 = 1;
			}

			for (int y = y0; y < y0+h; y++){
				byte* ptr = (byte*)img.GetPixelAddress(0, y-y0);
				for (int x = x0; x < x0+w; x++)
					*ptr++ = 255*(Get(y, x)-m0)/(m1-m0);
			}
		}
		img.Save(fileName);
		img.Destroy();
	};
#else
	void SaveToImage(TCHAR* fileName, int x0 = 0, int y0 = 0, int w = 0, int h = 0){
		//printf("\nSave To Image Not Defined!\n");
		return;
	}
#endif
	
	bool Fill(_T val){
		for (int i = 0; i < W*H; i++)
			data[i] = val;
		return true;
	}
	void Clear(){
		//try{
		if(! shared) MEM_FREE_MX(data);//}
		/*
		catch(...){
		static FILE* fpDelete = fopen("Clear.log", "wt");
		fprintf(fpDelete ,"EXCEPTION\n");
		fflush(fpDelete);
		};*/
		if(!shared_vec && _vector){
			delete [] _vector;
			_vector = 0;
		}
		data = NULL;
		shared = false;
		W = 0;
		H = 0;
	}
	
	bool Copy(CMatrix<_T> *from, bool shared_data = false)
	{
		if(! from)
			return false;

		bClassType = from->bClassType;
		mxType = from->mxType; 

		if(shared_data)
		{
			Clear();
			H = from->H; W = from->W;
			if(! W*H) return true;
			shared = true;
			data = from->data;
			_vector = from->_vector;
			shared_vec = true;
		}		
		else
		{
			if(from->W*from->H != W*H){
				Clear();
				data = MEM_ALLOC_MX(from->W*from->H);
			}

			H = from->H; W = from->W;
			shared = shared_vec = false;
			_vector = new CMatrixVec<_T>[from->H];
			for (int y = 0; y < H; y++)
				_vector[y].init(W, data + y*from->W);

			if(!bClassType)
				CopyMemory(data, from->data, W*H*sizeof(_T));
			else
				for (int i = 0; i < W*H; i++)
					data[i] = from->data[i];
		}

		return true;
	}
	/************************************************************************/
	/************				   Data access functions		 ************/

	inline operator _T*(){
		return data;
	}

	inline CMatrixVec<_T>& operator[](int y)
	{
		assert((y < H) && (y > -1) && data);
#if (MX_SAFETY_LEVEL > 0)
		if(y >= H || y < 0 || !data)
		{
			//char temp[100] = {0};
			//sprintf(temp, "y = %d (H = %d) (data = %d)", y, H, data);
			//MessageBoxA(NULL, temp, "", 0);
			fprintf(_fp_log, "** y = %d (H = %d) (data = %d)\n", y, H, data);
			fflush(_fp_log);
			static CMatrixVec<_T> fake;
			if(!fake.data || fake.W != W)
			{
				MEM_FREE_MX(fake.data)
				fake.data = MEM_ALLOC_MX(W);
				fake.W = W;
				fake.dedicated_data = true;//to be freed later on destructor
			}
			return fake;
		}
#endif
		return _vector[y];/*&data[y*W];*/
	}

	//unsafe but fast
	inline _T Get(int y, int x){
#ifdef Matrix_TRACE
		return get(y,x);
#endif
#ifdef DEBUG
		return get(y,x);
#endif
		return data[y*W + x];
	}
	//unsafe but fast
	inline void Set(int y, int x, _T val){
#ifdef Matrix_TRACE
		return set(y,x,val);
#endif
#ifdef DEBUG
		return set(y,x,val);
#endif		
		data[y*W + x] = val;
	}

	//safe functions
	inline _T get(int y, int x)
	{
		assert((y < H) && (x < W) && (y > -1) && (x > -1));
		if((x >= W) || (y >= H) || (x < 0) || (y < 0)){
			_T v;
			memset(&v, 0, sizeof(v));
#ifdef Matrix_TRACE
			if(fpTrace) fprintf(fpTrace, "mxId: %d, get(%d, %d), H: %d, W: %d\n", id, y, x, H, W);
			if(fpTrace) fflush(fpTrace);
#endif
			return v;
		}
		return data[y*W + x];
	}

	inline void set(int y, int x, _T val)
	{
		assert((y < H) && (x < W) && (y > -1) && (x > -1));
		if((x >= W) || (y >= H) || (x < 0) || (y < 0)){
#ifdef Matrix_TRACE
			if(fpTrace) fprintf(fpTrace, "mxId: %d, set(%d, %d, ?), H: %d, W: %d\n", id, y, x, H, W);
			if(fpTrace) fflush(fpTrace);
#endif
			return;
		}
		data[y*W + x] = val;
	}

	inline _T* ScanLine(int row) {if(data) return &data[row*W]; else return NULL;}
	inline bool isEmpty(){return (data == NULL);}

	/************				Image Processing Functions			    ************/

	void Negative(_T maxVal){
		assert(! shared);
		for(int i = 0; i < H*W; i++)
			data[i] = maxVal - data[i];
	}

	_T maxVal(){
		_T m = data[0];
		for (int i = 1;i < W*H; i++)
			if(data[i] > m)
				m = data[i];
		return m;
	}
	_T minVal(){
		_T m = data[0];
		for (int i = 1;i < W*H; i++)
			if(data[i] < m)
				m = data[i];
		return m;
	}

	/************************************************************************/
	/* newX, newY: New Dimensions for output Matrix                         */
	/* Method: Resample Method
	/* ReserveXYRatio: if true, the aspect ratio of input image will be reserved 
	/* and output will be centered
	/* grayFactor: if greater than 1, output will multiplied with this factor
	/************************************************************************/
	bool Resample(double rf, CMatrix<_T> *dst = NULL, byte back = 0, 
		EResampleMethod Method = rmBiLinear, bool ReserveXYRatio = false, byte grayFactor = 0)
	{
		return Resample((float)W*rf+0.5, (float)H*rf+0.5, dst, back, Method, ReserveXYRatio, grayFactor);
	}

	bool Resample(int newX, int newY, CMatrix<_T> *dst = NULL, byte back = 0, 
		EResampleMethod Method = rmBiLinear, bool ReserveXYRatio = false, byte grayFactor = 0)
	{
		assert((newX > 1) && (newY > 1));
		CHECK_SHARE(dst);
		CMatrix<_T> *Result = NULL;		
		if(!dst) Result = new CMatrix<_T>;
		else Result = dst;
		Result->init(newY, newX, true, back);
		Result->mxType = mxType;
		if((newX < 3) || (newY < 3))
			return false;

		if(grayFactor < 1)
			grayFactor = 1;
		float xScale = (float)newX/(float)W;
		float yScale = (float)newY/(float)H;

		if((grayFactor < 2) && (abs(xScale - 1.0) < 0.01) && (abs(yScale - 1.0) < 0.01) ){
			if(dst) dst->Copy(this);
			return true;
		}

		int ifX, ifY, ifX1, ifY1, xMax, yMax;
		float dy, dx, fx, fy;
		int x, y, ox = 0, oy = 0;
		byte v1, v2, v3, v4;
		float vx1, vx2;

		float scale = xScale;
		if(yScale < xScale)
			scale = yScale;
		if(ReserveXYRatio){
			xScale = yScale = scale;
			ox = (int)((newX - scale*W)/2);
			oy = (int)((newY - scale*H)/2);
		}

		switch (Method)
		{
		case rmNearest:
			//omp_set_num_threads(1);
			//#pragma omp parallel for private(x)
			for (y = 0; y < (int)(H*yScale); y++)
				for (x = 0; x < (int)(W*xScale); x++)
					Result->Set(y+oy, x+ox, Get( (int) (y/yScale), (int) (x/xScale) ));
			break;
		case rmBiLinear:
			xMax = W-1;
			yMax = H-1;			
			//omp_set_num_threads(1);
			//#pragma omp parallel for private(x)
			for (y = 0; y < (int)(H*yScale+0.5); y++)
			{
				fy = y / yScale;
				ifY = (int)fy;
				ifY1 = min(yMax, ifY+1);
				dy = fy - ifY;
				for (x = 0; x < (int)(W*xScale+0.5); x++)
				{
					fx = x / xScale;
					ifX = (int)fx;
					ifX1 = min(xMax, ifX+1);
					dx = fx - ifX;
					// Interpolate using the four nearest pixels in the source
					v1 = Get(ifY, ifX);
					v2 = Get(ifY, ifX1);
					v3 = Get(ifY1, ifX);
					v4 = Get(ifY1, ifX1);
					// Interpolate in x direction
					vx1 = v1 * (1 - dy) + v3 * dy;
					vx2 = v2 * (1 - dy) + v4 * dy;
					//set output values
					Result->Set( y+oy, x+ox, (_T) (grayFactor*(vx1*(1-dx)+vx2*dx) + 0.5) );
				};//for x
			};
			break;
		case rmBiCubic:
			break;
		};
		if(! dst){
			Copy(Result);
			SAFE_DELETE(Result);
		}
		return true;
	}


	bool SaveToFile(char * FileName){
		FILE* fp = fopen(FileName, "wb");
		if(SaveToFile(fp))
			fclose(fp);
		else
			return false;
		return true;
	}
	//file will not be closed
	bool SaveToFile (FILE* fp)
	{
		if(! fp)	return false;
		fwrite(&H, sizeof(int), 1, fp);
		fwrite(&W, sizeof(int), 1, fp);
		fwrite(data, sizeof(_T), W*H, fp);
		return true;
	}

	bool LoadFromFile(char * FileName){
		FILE* fp = fopen(FileName, "rb");
		if(LoadFromFile(fp))
			fclose(fp);
		else
			return false;
		return true;
	}
	bool LoadFromFile(FILE* fp){
		if(! fp)	return false;
		Clear();
		int height = 0, width = 0; // do not  use this->W & this->H because init() will fail
		fread(&height, sizeof(int), 1, fp);
		fread(&width, sizeof(int), 1, fp);
		init(height, width, false);
		fread(data, sizeof(_T), W*H, fp);
		return true;
	}

	bool ZeroPad(CMatrix<_T> *dst = NULL, byte Zero = 0,  int LPad = 1, int RPad = 1, int TPad = 1, int BPad = 1){
		assert((LPad >= 0) && (TPad >= 0) && (RPad >= 0) && (BPad >= 0) && (W > 0) && (H > 0));
		CHECK_SHARE(dst);
		CMatrix<_T> *Result = NULL;
		if(!dst) Result = new CMatrix<_T>;
		else Result = dst;

		Result->init(H+TPad+BPad, W+LPad+RPad, 1, Zero);
		for (int y = 0; y < H; y++)
			memcpy(Result->ScanLine(y+TPad)+LPad, ScanLine(y), W);
		if(! dst){
			Copy(Result);
			SAFE_DELETE(Result);
		}
		return true;
	}

	void StdMean(double* mean, double* std = 0){
		if((! mean) || (W*H < 1)) return;
		static float prob[256];//normalized histogram (hist/W*H)
		(*mean) = 0;
		int nLevel = (mxType == mtGray) ? 256 : 2;
		switch(mxType){
		case mtBinary:
		case mtGray:
			//the following idea is taken from "Character Recognition Systems" book page 10
			memset(prob, 0, sizeof(float)*nLevel);
			for(int i = 0; i < H*W; i++) ++prob[(int)data[i]];
			for (int i = 0; i < nLevel; i++){
				prob[i] /= H*W;
				(*mean) += i*prob[i];
			}
			if((! std) || (W*H < 2)) return;
			*std = 0;
			for (int i = 0; i < nLevel; i++)
				(*std) += sqr(i-(*mean))*prob[i];
			(*std) = sqrt(*std);
			break;
		default:
			//Traditional approach for computing std and mean
			for(int i = 0; i < H*W; i++) (*mean) += data[i];
			(*mean) /= H*W;
			if((! std) || (W*H < 2)) return;
			*std = 0;
			for(int i = 0; i < H*W; i++) (*std) += sqr(data[i] - (*mean));
			(*std) = sqrt((*std) / (H*W - 1));
			break;
		}
	}

	/************************************************************************/
	/* Binarization
	/* Here is the power of pointers (or one dimensional arrays)!!          
	/************************************************************************/
	void MakeBinary(byte Th, CMatrix<_T>* dst = NULL){ 
		assert(mxType != mtBinary);
		//omp_set_num_threads(1);//its very confusing knowing that this configuration gave the most efficient results through 1,2 and 4 threads testing on QuadCore CPU
		//#pragma omp parallel for
		_T* p = data;
		if(dst){
			dst->Copy(this, false);
			p = dst->data;
			dst->mxType = mtBinary;
		}
		else
			mxType = mtBinary;
		for(int i = 0; i < H*W; i++) (p[i] < Th) ? p[i] = 1 : p[i] = 0;
	}


#ifdef Matrix_TRACE
	void SetId(){
		id = ++Counter;
		if(fpTrace) fprintf(fpTrace, "**** CMatrix # %d ****\n", id);
		if(fpTrace) fflush(fpTrace);
	}
	void ShowId(){
		if(fpTrace) fprintf(fpTrace, "**** ~CMatrix # %d ****\n", id);
		if(fpTrace) fflush(fpTrace);
	}
	static int Counter;
	static FILE* fpTrace;
#else
	void SetId(){}
	void ShowId(){}
#endif

	inline int type(){return mxType;};
	inline void SetType(MatrixType type) {mxType = type;};
	SMatrix GetSMatrix(){SMatrix s; s.data = data; s.height = H; s.width = W; return s;}
	//should be private!
	union{
		int W; //Matrix width (number of columns)
		int width; //Matrix width (number of columns)
		int num_cols; //Matrix width (number of columns)
	};
	union{
		int H; //Matrix height (number of rows)
		int height; //Matrix height (number of rows)
		int num_rows; //Matrix height (number of rows)
	};
	bool shared;//if true: data is SHARED AND NON DELETABLE. Data doesn't belong to this instance.
	//Sometimes we need to do some operation on large images which is sent from other 
	//applications for example our OCR application, in such cases its not efficient 
	//to reallocate memory to a new Matrix, instead we set this flag to true
	//and we must be aware that the data MUST NOT BE DELETED
private:
	CMatrixVec<_T>* _vector;
	CMatrixVec<_T> _fake_vec;//in the case of invalid access to data, e.g. when data is empty, we return a fake data
	_T* data;
	bool shared_vec;// is _vector shared?
	bool bClassType;
	MatrixType mxType;

#ifdef Matrix_TRACE
	int id;
#endif
};

#ifdef Matrix_TRACE
template <typename _T>
int CMatrix<_T>::Counter = 0;
template <typename _T>
FILE* CMatrix<_T>::fpTrace = fopen("mxTrace.txt", "w+t");
#endif
typedef CMatrix<byte>* PMatrix;
