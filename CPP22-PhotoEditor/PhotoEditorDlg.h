
// PhotoEditorDlg.h : header file
//

#pragma once


// CPhotoEditorDlg dialog
class CPhotoEditorDlg : public CDialogEx
{
// Construction
public:
	CPhotoEditorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHOTOEDITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CImage img_work, img_org;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedGray();
	afx_msg void OnBnClickedGray2();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedNegative();
	afx_msg void OnBnClickedRemoveRed();
	afx_msg void OnBnClickedBright();
};
