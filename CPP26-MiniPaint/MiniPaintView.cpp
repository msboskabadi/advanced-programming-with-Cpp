
// MiniPaintView.cpp : implementation of the CMiniPaintView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MiniPaint.h"
#endif

#include "MiniPaintDoc.h"
#include "MiniPaintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMiniPaintView

IMPLEMENT_DYNCREATE(CMiniPaintView, CScrollView)

BEGIN_MESSAGE_MAP(CMiniPaintView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMiniPaintView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMiniPaintView construction/destruction

CMiniPaintView::CMiniPaintView() noexcept
{
	// TODO: add construction code here

}

CMiniPaintView::~CMiniPaintView()
{
}

BOOL CMiniPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CMiniPaintView drawing

void CMiniPaintView::OnDraw(CDC* pDC)
{
	CMiniPaintDoc* pDoc = GetDocument();	
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->img.IsNull())
	{
		CImage img;
		CRect rc;
		GetClientRect(&rc);
		img.Create(rc.Width(), rc.Height(), 24);
		//img.SetColorTable()
		for (size_t y = 0; y < img.GetHeight(); y++)
		{
			unsigned char* p = (unsigned char*) img.GetPixelAddress(0, y);
			for (size_t x = 0; x < img.GetWidth(); x++)
			{
				*p++ = 200;//B
				*p++ = 127 + y * 128 / img.GetHeight();//G
				*p++ = 100;//R
			}
		}

		img.Draw(pDC->GetSafeHdc(), 0, 0);
		pDC->SetBkMode(TRANSPARENT);
		CFont f;
		f.CreatePointFont(200, L"Times New Roman");
		pDC->SelectObject(&f);
		pDC->TextOutW(img.GetWidth() / 2 - 100, img.GetHeight() - 40, L"www.shahroodut.ac.ir");
		return;
	}

	pDoc->img.Draw(pDC->GetSafeHdc(), 0, 0);

	CSize sz;
	// TODO: calculate the total size of this view
	sz.cx = pDoc->img.GetWidth();
	sz.cy = pDoc->img.GetHeight();
	SetScrollSizes(MM_TEXT, sz);
}

void CMiniPaintView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 500;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMiniPaintView printing


void CMiniPaintView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMiniPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMiniPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMiniPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMiniPaintView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMiniPaintView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMiniPaintView diagnostics

#ifdef _DEBUG
void CMiniPaintView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMiniPaintView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMiniPaintDoc* CMiniPaintView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMiniPaintDoc)));
	return (CMiniPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CMiniPaintView message handlers


void CMiniPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (painting)
	{
		CDC *p = GetDC();		
		CMiniPaintDoc* pDoc = GetDocument();
		CPen pen(PS_SOLID, 2, pDoc->pen_clr);
		p->SelectObject(pen);
		p->MoveTo(p1);
		p->LineTo(point);
		p1 = point;
		ReleaseDC(p);
	}
	CScrollView::OnMouseMove(nFlags, point);
}


void CMiniPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	painting = true;
	p1 = point;
	CScrollView::OnLButtonDown(nFlags, point);
}


void CMiniPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	painting = false;
	CScrollView::OnLButtonUp(nFlags, point);
}


void CMiniPaintView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	// Invalidate();
}
