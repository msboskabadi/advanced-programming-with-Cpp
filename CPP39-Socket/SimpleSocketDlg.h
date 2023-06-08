// SimpleSocketDlg.h : header file
//

#if !defined(AFX_SimpleSocketDLG_H__4CADC9CA_6763_11D7_ADFE_EC624CEC9037__INCLUDED_)
#define AFX_SimpleSocketDLG_H__4CADC9CA_6763_11D7_ADFE_EC624CEC9037__INCLUDED_

#include "Socket1.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SEND_FREQ 100
/////////////////////////////////////////////////////////////////////////////
// SimpleSocketDlg dialog

#define APP_CLINET 0
#define APP_SERVER 1
class SimpleSocketDlg : public CDialogEx
{
// Construction
public:
	//Mine
	CSocket1 listen_socket;
	CSocket1 connect_socket;
	void OnAccept();
	void OnConnect();
	void OnClose();
	void OnReceive();
	void OnSend();
	SimpleSocketDlg(CWnd* pParent = NULL);	// standard constructor
	enum { IDD = IDD_SimpleSocket_DIALOG };
	CListBox	received_list;
	CListBox	sent_list;
	CButton	btn_connect;
	int		app_type; //0 client, 1 server
	CString	server_ip;
	int		port_num;
	CString	message;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SimpleSocketDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(SimpleSocketDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void UpdateUI(bool enable);
	void OnBconnect();
	afx_msg void OnAppType();
	afx_msg void OnSendMsg();
	afx_msg void OnBclose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedReplace();
	afx_msg void OnBnClickedSendFreq();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedClearSent();
	afx_msg void OnBnClickedClearRcvd();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SimpleSocketDLG_H__4CADC9CA_6763_11D7_ADFE_EC624CEC9037__INCLUDED_)
