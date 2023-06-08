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

// FFTDoc.h : interface of the CFFTDoc class
//


#pragma once


class CFFTDoc : public CDocument
{
protected: // create from serialization only
	CFFTDoc();
	DECLARE_DYNCREATE(CFFTDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	double *pLeftCh, *pRightCh, *pLeftFFT;
	double fftMaxAmp;//Maximum Amplitude of fft. Used for normalization
	int data_len;
	DWORD byte_len;//wave file size - header size
	WORD num_channel, precision;

// Implementation
public:
	virtual ~CFFTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


