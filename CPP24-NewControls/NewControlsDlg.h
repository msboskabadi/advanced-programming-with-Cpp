
// NewControlsDlg.h : header file
//

#pragma once


// CNewControlsDlg dialog
class CNewControlsDlg : public CDialogEx
{
// Construction
public:
	CNewControlsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWCONTROLS_DIALOG };
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
	CAnimateCtrl anim;
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnEnChangeMfceditbrowse1();
	CMFCEditBrowseCtrl browse_dlg;
	CProgressCtrl progress;
	CSliderCtrl slider;
	afx_msg void OnBnClickedBtnProcess();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CComboBox combo;
	afx_msg void OnBnClickedBtnShow();
};
