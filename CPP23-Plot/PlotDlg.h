
// PlotDlg.h : header file
//

#pragma once

enum DrawType {DRAW_NONE, DRAW_LINE, DRAW_GRID, DRAW_SIN, DRAW_FREE};

// CPlotDlg dialog
class CPlotDlg : public CDialogEx
{
// Construction
public:
	CPlotDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLOT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	bool painting = false;
	CPoint old_pt;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	void draw_line();
	void draw_grid();
	void draw_sin();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:	
	DrawType draw_type = DRAW_NONE; //0 none, 1 line, 2 grid, 3 sin
	afx_msg void OnBnClickedLine();
	afx_msg void OnBnClickedGrid();
	afx_msg void OnBnClickedSin();
	afx_msg void OnBnClickedFreehand();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
