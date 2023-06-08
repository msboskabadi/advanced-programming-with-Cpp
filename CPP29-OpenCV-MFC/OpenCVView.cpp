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

// OpenCVView.cpp : implementation of the OpenCVView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenCV-MFC.h"
#endif

#include "OpenCVDoc.h"
#include "OpenCVView.h"
#include "Mat-util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// OpenCVView

IMPLEMENT_DYNCREATE(OpenCVView, CScrollView)

BEGIN_MESSAGE_MAP(OpenCVView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &OpenCVView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// OpenCVView construction/destruction

OpenCVView::OpenCVView() noexcept
{
	// TODO: add construction code here

}

OpenCVView::~OpenCVView()
{
}

BOOL OpenCVView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// OpenCVView drawing

void OpenCVView::OnDraw(CDC* pDC)
{
	OpenCVDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	if (pDoc->img.empty())
		return;
	CImage cim;
	Mat2CImage(pDoc->img, cim);
	cim.Draw(pDC->GetSafeHdc(), 0, 0);
}

void OpenCVView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// OpenCVView printing


void OpenCVView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL OpenCVView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void OpenCVView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void OpenCVView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void OpenCVView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void OpenCVView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// OpenCVView diagnostics

#ifdef _DEBUG
void OpenCVView::AssertValid() const
{
	CScrollView::AssertValid();
}

void OpenCVView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

OpenCVDoc* OpenCVView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(OpenCVDoc)));
	return (OpenCVDoc*)m_pDocument;
}
#endif //_DEBUG


// OpenCVView message handlers
