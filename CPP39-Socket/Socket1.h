#if !defined(AFX_SOCKET1_H__8CD6A7C1_67AD_11D7_ADFE_F8EEE081242A__INCLUDED_)
#define AFX_SOCKET1_H__8CD6A7C1_67AD_11D7_ADFE_F8EEE081242A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Socket1.h : header file
//
#include <afxsock.h>
/////////////////////////////////////////////////////////////////////////////
// CSocket1 command target

class CSocket1 : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	virtual ~CSocket1();
	CSocket1(){};

// Overrides
public:
	void SetParent(CDialogEx *pWnd);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocket1)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSocket1)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CDialogEx *m_pWnd;
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKET1_H__8CD6A7C1_67AD_11D7_ADFE_F8EEE081242A__INCLUDED_)
