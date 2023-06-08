
// MiniPaintDoc.cpp : implementation of the CMiniPaintDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MiniPaint.h"
#endif

#include "MiniPaintDoc.h"
#include "CSettingsDlg.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMiniPaintDoc

IMPLEMENT_DYNCREATE(CMiniPaintDoc, CDocument)

BEGIN_MESSAGE_MAP(CMiniPaintDoc, CDocument)
	ON_COMMAND(ID_PROCESS_NEGATIVE, &CMiniPaintDoc::OnProcessNegative)
	ON_UPDATE_COMMAND_UI(ID_PROCESS_NEGATIVE, &CMiniPaintDoc::OnUpdateProcessNegative)
	ON_COMMAND(ID_TOOLS_SETTINGS, &CMiniPaintDoc::OnToolsSettings)
END_MESSAGE_MAP()


// CMiniPaintDoc construction/destruction

CMiniPaintDoc::CMiniPaintDoc() noexcept
{
	// TODO: add one-time construction code here

}

CMiniPaintDoc::~CMiniPaintDoc()
{
}

BOOL CMiniPaintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


BOOL CMiniPaintDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!img.IsNull())
		img.Detach();
	img.Load(lpszPathName);

	UpdateAllViews(0);

	return 0;
}

// CMiniPaintDoc serialization

void CMiniPaintDoc::Serialize(CArchive& ar)
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
void CMiniPaintDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMiniPaintDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMiniPaintDoc::SetSearchContent(const CString& value)
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

// CMiniPaintDoc diagnostics

#ifdef _DEBUG
void CMiniPaintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMiniPaintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMiniPaintDoc commands


void CMiniPaintDoc::OnProcessNegative()
{
	unsigned char* ptr = (unsigned char*)img.GetBits();
	int step = img.GetPitch(); // typically it is equal to width*3; but may be different (multiple of 4)

	for (auto y = 0; y < img.GetHeight(); y++)
	{
		unsigned char* p = ptr + step * y;// (unsigned char*)img.GetPixelAddress(0, y);
		for (auto x = 0; x < img.GetWidth(); x++)
		{
			p[0] = 255 - p[0];
			p[1] = 255 - p[1];
			p[2] = 255 - p[2];

			p += 3; //point to the next pixel
		}
	}

	UpdateAllViews(0);
}


void CMiniPaintDoc::OnUpdateProcessNegative(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!img.IsNull());
}


void CMiniPaintDoc::OnToolsSettings()
{
	//CSettingsDlg* p = new CSettingsDlg(nullptr, pen_idx);
	CSettingsDlg p(nullptr, pen_idx);
	auto result = p.DoModal();
	if (result == IDOK)
	{
		pen_idx = p.selected_color;
		if (pen_idx == 0)
			pen_clr = RGB(0, 0, 255);
		else if (pen_idx == 1)
			pen_clr = RGB(0, 255, 0);
		else if (pen_idx == 2)
			pen_clr = RGB(255, 0, 0);
	}

	//delete p;
}


BOOL CMiniPaintDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class
	POSITION p = GetFirstViewPosition();
	CView * v = GetNextView(p);

	/// 
	CRect rc;
	v->GetClientRect(&rc);
	CDC* pDC = v->GetDC();
	CImage image;
	image.Create(rc.Width(), rc.Height(), 32);

	HDC imageHDC = image.GetDC();
	::BitBlt(imageHDC, 0, 0, rc.Width(), rc.Height(), pDC->GetSafeHdc(), 0, 0, SRCCOPY);
	image.Save(lpszPathName, GUID_NULL);
	image.ReleaseDC();
	v->ReleaseDC(pDC);
	/// 

	return 1;//CDocument::OnSaveDocument(lpszPathName);
}
