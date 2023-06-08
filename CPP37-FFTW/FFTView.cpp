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

// FFTView.cpp : implementation of the CFFTView class
//

#include "stdafx.h"
#include "FFT.h"

#include "FFTDoc.h"
#include "FFTView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFFTView

IMPLEMENT_DYNCREATE(CFFTView, CView)

BEGIN_MESSAGE_MAP(CFFTView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFFTView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CFFTView construction/destruction

CFFTView::CFFTView()
{
	// TODO: add construction code here

}

CFFTView::~CFFTView()
{
}

BOOL CFFTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CFFTView drawing

void CFFTView::OnDraw(CDC* pDC)
{
	CFFTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if(pDoc->data_len < 1)
		return;
	CRect rc;
	GetClientRect(&rc);
	//////////////////////////////////////////////////////////////////////////
	//Draw background rectangle for top graph (signal)
	RECT rcBack = {10, 10, rc.Width()-10, rc.Height()/2-10};
	CPen pen(PS_DOT, 1, RGB(127,127,127));
	pDC->SelectObject(&pen);
	pDC->Rectangle(&rcBack);
	CFont fnt;
	fnt.CreatePointFont(140, _T("Times New Roman"));
	pDC->SelectObject(&fnt);
	rcBack.top += 10;
	rcBack.left += 10;
	pDC->DrawText(_T("Audio Signal"), 12, &rcBack, 0);
	
	//////////////////////////////////////////////////////////////////////////
	//Draw background rectangle for bottom graph (FFT)
	rcBack.left -= 10;
	rcBack.top += rc.Height()/2-10;
	rcBack.bottom += rc.Height()/2-10;
	pDC->Rectangle(&rcBack);
	rcBack.top += 10;
	rcBack.left += 10;
	pDC->SetTextColor(RGB(200, 0, 0));
	pDC->DrawText(_T("Fourier Transform"), 17, &rcBack, 0);

	//////////////////////////////////////////////////////////////////////////
	//Draw top graph
	int x0 = 20;
	int y0 = rc.Height()/4;
	double norm = 1;
	if(pDoc->precision == 16)
		norm = 256*256*2;
	pDC->MoveTo(x0, y0-pDoc->pLeftCh[0]*rc.Height()/norm);
	int n = pDoc->data_len;
	double* p = pDoc->pLeftCh;
	int step = 1;
	if(n > 10000)
		step = n / 10000;

	CPen pen2(PS_SOLID, 1, RGB(0, 0, 150));
	pDC->SelectObject(&pen2);
	for (int i = 1; i < n; i += step){
		int x = i * (rc.Width()-2*x0) / n;
		int y = p[i]*rc.Height()/norm;
		pDC->LineTo(x0+x, y0-y);
		pDC->MoveTo(x0+x, y0-y);
	}

	//////////////////////////////////////////////////////////////////////////
	//Draw bottom graph
	CPen pen3(PS_SOLID, 1, RGB(150, 0, 0));
	pDC->SelectObject(&pen3);
	n = log((double)pDoc->data_len)/log(2.0)-1;
	n = pow(2.0,(double)n);
	//n = pDoc->data_len/2;
	p = pDoc->pLeftFFT;
	norm = pDoc->fftMaxAmp*2;


	y0 = rc.Height()-20;
	pDC->MoveTo(x0, y0-p[0]*rc.Height()/norm);
	for (int i = 1; i < n; i += step){
		int x = i * (rc.Width()-2*x0) / n;
		int y = p[i]/norm*rc.Height();
		pDC->LineTo(x0+x, y0-y);
		pDC->MoveTo(x0+x, y0-y);
	}

	/*for (int x = 1; x < rc.Width(); x++){
		int index = x * pDoc->data_len / rc.Width();
		int y = pDoc->pLeftCh[index]*rc.Height()/32000;
		pDC->LineTo(x0+x, y0-y);
		pDC->MoveTo(x0+x, y0-y);
	}*/
	
}


// CFFTView printing


void CFFTView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CFFTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFFTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFFTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFFTView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFFTView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CFFTView diagnostics

#ifdef _DEBUG
void CFFTView::AssertValid() const
{
	CView::AssertValid();
}

void CFFTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFFTDoc* CFFTView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFFTDoc)));
	return (CFFTDoc*)m_pDocument;
}
#endif //_DEBUG


// CFFTView message handlers
