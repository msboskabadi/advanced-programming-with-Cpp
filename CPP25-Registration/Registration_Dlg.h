
// Registration_Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// CRegistration_Dlg dialog
class CRegistration_Dlg : public CDialog
{
// Construction
public:
	CRegistration_Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_REG };

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
	// Student Course
	CComboBox m_cmbCourse;
	CString m_strName;
	CString m_strDate;
	int m_nCertificateID;
	CString m_strCourse;
	int m_nID;
	BOOL m_bAnjoman;
	BOOL m_bResearch;
	BOOL m_bQuran;
	BOOL m_bBasij;
	int m_nGender;
	afx_msg void OnBnClickedOk();
	int gender;
	float temp_var;
	afx_msg void OnEnChangeEdtBirth2();
};
