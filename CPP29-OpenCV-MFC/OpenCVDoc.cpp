// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// OpenCVDoc.cpp : implementation of the OpenCVDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenCV-MFC.h"
#endif

#include "OpenCVDoc.h"
#include <propkey.h>
#include "Mat-util.h"

#if _DEBUG
	#pragma comment(lib, "opencv_world470d.lib")
	#define new DEBUG_NEW
#else
	#pragma comment(lib, "opencv_world470.lib")
#endif


// OpenCVDoc

IMPLEMENT_DYNCREATE(OpenCVDoc, CDocument)

BEGIN_MESSAGE_MAP(OpenCVDoc, CDocument)
	ON_COMMAND(ID_BTN_FILTER, &OpenCVDoc::OnBtnFilter)
	ON_COMMAND(ID_BTN_EDGE, &OpenCVDoc::OnBtnEdge)
	ON_COMMAND(ID_BTN_RESET, &OpenCVDoc::OnBtnReset)
END_MESSAGE_MAP()


// OpenCVDoc construction/destruction

OpenCVDoc::OpenCVDoc() noexcept
{
	// TODO: add one-time construction code here

}

OpenCVDoc::~OpenCVDoc()
{
}

BOOL OpenCVDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// OpenCVDoc serialization

void OpenCVDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void OpenCVDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void OpenCVDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void OpenCVDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// OpenCVDoc diagnostics

#ifdef _DEBUG
void OpenCVDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void OpenCVDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// OpenCVDoc commands


BOOL OpenCVDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	img = ReadImage(lpszPathName);
	org = img.clone();
	UpdateAllViews(0);

	return TRUE;
}


void OpenCVDoc::OnBtnFilter()
{
	const int ND = 3;
	//float filter[3][3] = { 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9, 1.0 / 9 };
	//float filter[3][3] = { 1, 2, 1, 0, 0, 0, -1, -2, -1 };
	float filter[3][3] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	cv::Mat gray;
	if (img.channels() == 3) {
		cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
		img = gray.clone();
	}
#if 1
	//Mat kernel = Mat::ones(ND, ND, CV_32F) / (float)(ND*ND);
	Mat kernel(3, 3, CV_32F, filter);

	cv::filter2D(img, img, CV_8UC3, kernel);
#else

	for (int y = ND / 2; y < org.rows - ND / 2; y++)
	{
		for (int x = ND / 2; x < org.cols - ND / 2; x++)
		{
			double sum = { 0 };
			for (int j = -ND / 2; j <= ND / 2; j++)
			{
				for (int i = -ND / 2; i <= ND / 2; i++)
				{
					sum += gray.at<uchar>(y + j, x + i) * filter[j + ND / 2][i + ND / 2];
				}
			}

			img.at<uchar>(y, x) = abs(sum);// MAX(MIN(sum, 255), 0);// / (ND*ND);
		}
	}
#endif
	//input_img = work_img.clone();
	UpdateAllViews(0);
}


void OpenCVDoc::OnBtnEdge()
{
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	//cv::Sobel(img, img, CV_8UC1, 1, 1);
	//img = img > 70;
	cv::Canny(img, img, 150, 120);
	UpdateAllViews(0);	
}


void OpenCVDoc::OnBtnReset()
{
	img = org.clone();
	UpdateAllViews(0);
}
