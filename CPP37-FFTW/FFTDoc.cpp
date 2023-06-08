// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// FFTDoc.cpp : implementation of the CFFTDoc class
//

#include "stdafx.h"
#include "FFT.h"
#include "FFTDoc.h"
#include <math.h>
//#include "utility.h"

#include "fftw3.h"
#pragma comment(lib, "libfftw3-3.lib")

struct Scplx{
	double real;
	double imag;
};

inline double sqr(double x){ return x*x; }
inline double absx2(Scplx x){ return sqrt( sqr(x.real) + sqr(x.imag) ); }

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFFTDoc

IMPLEMENT_DYNCREATE(CFFTDoc, CDocument)

BEGIN_MESSAGE_MAP(CFFTDoc, CDocument)
END_MESSAGE_MAP()


// CFFTDoc construction/destruction

CFFTDoc::CFFTDoc()
{
	pLeftCh = pRightCh = NULL;
	precision = 8;
	num_channel = 1;
	byte_len = 0;
	data_len = 0;
}

CFFTDoc::~CFFTDoc()
{
}

BOOL CFFTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CFFTDoc serialization

void CFFTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

BOOL CFFTDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	//CFile file(lpszPathName, CFile::modeRead|CFile::typeBinary);
	FILE* fp = _tfopen(lpszPathName, _T("rb"));
	
	//file.Seek(22, 0);
	//file.Read(&num_channel, 2);
	fseek(fp, 22, 0);
	fread(&num_channel, 2, 1, fp);

	//file.Seek(34, 0);
	//file.Read(&precision, 2);//8 or 16 bits?
	fseek(fp, 34, 0);
	fread(&precision, 2, 1, fp);//8 or 16 bits?

	//file.Seek(40, 0);
	//file.Read(&byte_len, 4);
	fseek(fp, 40, 0);
	fread(&byte_len, 4, 1, fp);

	//file.Seek(44, 0);//44 = header bytes
	fseek(fp, 44, 0);

	data_len = byte_len*8/precision/num_channel;
	if(!pLeftCh) 
		delete pLeftCh;
	if(!pRightCh) 
		delete pRightCh;

	pLeftCh = new double[data_len];
	if(num_channel == 2)
		pRightCh = new double[data_len];	
	
	if(precision == 8){
		char* pSample = new char[data_len*num_channel];
		//file.Read(pSample, data_len*num_channel);
		fread(pSample, 1, data_len*num_channel, fp);
		if(num_channel == 1)
			for(int i = 0; i < data_len; i++)
				pLeftCh[i] = pSample[i];
		else
			for(int i = 0; i < 2* data_len; i += 2){
				pLeftCh[i/2] = pSample[i];
				pRightCh[i/2] = pSample[i+1];
			}
		delete pSample;

	}
	else{
		__int16* pSample = new __int16[data_len*num_channel];
		//file.Read(pSample, 2*data_len*num_channel);
		size_t sz = fread(pSample, 2, data_len*num_channel, fp);
		if(num_channel == 1)
			for(int i = 0; i < data_len; i++)
				pLeftCh[i] = pSample[i];
		else
			for(int i = 0; i < 2*data_len; i += 2){
				pLeftCh[i/2] = pSample[i];
				pRightCh[i/2] = pSample[i+1];
			}

		delete pSample;
	}

	//NormalizeVector(pLeftCh, data_len, 5);
	/*FILE *fp2 = fopen("d:\\1.txt", "wt");
	for (int i = 0; i < data_len; i++){
		fprintf(fp2, "%.8g,", pLeftCh[i]);
	}*/
	int n = log((double)data_len)/log(2.0);
	n = pow(2.0,(double)n);
	//int n = data_len;
	Scplx* pFFT = new Scplx[n];
	fftw_plan fftp = fftw_plan_dft_r2c_1d(n, pLeftCh, (fftw_complex*)pFFT, FFTW_FORWARD);
	fftw_execute(fftp);
	
	pLeftFFT = new double[n/2];//Since amplitude of fft is symmetric, only 1+n/2 are unique (1 for DC)
	fftMaxAmp = 0;
	for (int i = 0; i < n/2; i++){
		pLeftFFT[i] = absx2(pFFT[i]);
		if(pLeftFFT[i] > fftMaxAmp)
			fftMaxAmp = pLeftFFT[i];
	}
	//NormalizeVector(pLeftFFT, n/2, 5);
	delete [] pFFT;
	fclose(fp);
	//fclose(fp2);

	UpdateAllViews(0);
	return TRUE;
}


// CFFTDoc diagnostics

#ifdef _DEBUG
void CFFTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFFTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CFFTDoc commands
