// testDlg.h : header file
//

#pragma once


// CMultiCoreTestDlg dialog
class CMultiCoreTestDlg : public CDialog
{
// Construction
public:
	CMultiCoreTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClicked1thread();
	afx_msg void OnBnClicked2thread();
	afx_msg void OnBnClicked4thread();
	afx_msg void OnBnClickedNothread();
//	afx_msg void OnStnClickedHyperlink();
};
