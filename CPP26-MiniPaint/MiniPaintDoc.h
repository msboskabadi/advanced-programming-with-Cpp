
// MiniPaintDoc.h : interface of the CMiniPaintDoc class
//


#pragma once


class CMiniPaintDoc : public CDocument
{
protected: // create from serialization only
	CMiniPaintDoc() noexcept;
	DECLARE_DYNCREATE(CMiniPaintDoc)

// Attributes
public:
	CImage img;
	COLORREF pen_clr = RGB(0, 0, 0);
	int pen_idx = -1;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMiniPaintDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnProcessNegative();
	afx_msg void OnUpdateProcessNegative(CCmdUI* pCmdUI);
	afx_msg void OnToolsSettings();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
