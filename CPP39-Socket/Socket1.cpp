// Socket1.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleSocket.h"
#include "Socket1.h"
#include "SimpleSocketDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocket1

CSocket1::~CSocket1()
{
}

void CSocket1::SetParent(CDialogEx *pWnd)
{
	m_pWnd = pWnd;
}
void CSocket1::OnAccept(int nErrorCode)
{
	if (nErrorCode == 0)
		((SimpleSocketDlg*)m_pWnd)->OnAccept();
}

void CSocket1::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0)
		((SimpleSocketDlg*)m_pWnd)->OnConnect();
}

void CSocket1::OnClose(int nErrorCode)
{
	if (nErrorCode == 0)
		((SimpleSocketDlg*)m_pWnd)->OnClose();
}

void CSocket1::OnSend(int nErrorCode)
{
	if (nErrorCode == 0)
		((SimpleSocketDlg*)m_pWnd)->OnSend();
}

void CSocket1::OnReceive(int nErrorCode)
{
	if (nErrorCode == 0)
		((SimpleSocketDlg*)m_pWnd)->OnReceive();
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSocket1, CAsyncSocket)
	//{{AFX_MSG_MAP(CSocket1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSocket1 member functions
