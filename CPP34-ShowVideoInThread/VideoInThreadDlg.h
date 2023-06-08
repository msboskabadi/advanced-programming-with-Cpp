
// VideoInThreadDlg.h : header file
//

#pragma once

#include <opencv.hpp>
// VideoDlg dialog
class VideoDlg : public CDialogEx
{
// Construction
public:
	VideoDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPP32SHOWVIDEOINTHREAD_DIALOG };
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
	cv::VideoCapture cap;
	std::thread trd;
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedInfo();
	afx_msg void OnBnClickedPlayTrd();
};
