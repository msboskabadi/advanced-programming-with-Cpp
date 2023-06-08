
// MFC-BasicsDlg.h : header file
//

#pragma once


// CMFCBasicsDlg dialog
class CMFCBasicsDlg : public CDialogEx
{
// Construction
public:
	CMFCBasicsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASICS_DIALOG };
#endif

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
	afx_msg void OnBnClickedBtnMsg();
	afx_msg void OnBnClickedBtnRect();
	afx_msg void OnBnClickedBtnCompute();
	afx_msg void OnEnChangeEdit1();
	float num1, num2, num3;
};
