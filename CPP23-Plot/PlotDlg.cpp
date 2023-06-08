
// PlotDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Plot.h"
#include "PlotDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPlotDlg dialog



CPlotDlg::CPlotDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPlotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPlotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_LINE, &CPlotDlg::OnBnClickedLine)
	ON_BN_CLICKED(ID_GRID, &CPlotDlg::OnBnClickedGrid)
	ON_BN_CLICKED(ID_SIN, &CPlotDlg::OnBnClickedSin)
	ON_BN_CLICKED(ID_FREEHAND, &CPlotDlg::OnBnClickedFreehand)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPlotDlg message handlers

BOOL CPlotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPlotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPlotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (draw_type == DRAW_LINE)
		{
			draw_line();
		}
		else if (draw_type == DRAW_GRID)
		{
			draw_grid();
		}
		else if (draw_type == DRAW_SIN)
		{
			draw_sin();
		}
		CDialogEx::OnPaint();
	}
}

void CPlotDlg::draw_line()
{
	CDC* p = GetDlgItem(IDC_GRAPH)->GetDC();
	
	CPen pen(PS_SOLID, 3, RGB(0, 200, 0));
	p->SelectObject(&pen);
	p->MoveTo(10, 10);
	p->LineTo(200, 200);

	CPen pen2(PS_SOLID, 3, RGB(0, 0, 200));
	p->SelectObject(&pen2);
	p->LineTo(400, 200);

	CPen pen3(PS_SOLID, 3, RGB(200, 0, 0));
	p->SelectObject(&pen3);
	p->LineTo(600, 400);
	
	ReleaseDC(p);
}

void CPlotDlg::draw_grid()
{
	CDC* p = GetDlgItem(IDC_GRAPH)->GetDC();
	CRect rc;
	GetDlgItem(IDC_GRAPH)->GetClientRect(&rc);
	CBrush br(RGB(250, 250, 220));
	p->FillRect(&rc, &br);
	CPen pen(PS_DOT, 1, RGB(150, 150, 250));
	p->SelectObject(&pen);

	for (auto y = 0; y < rc.Height(); y += 20)
	{
		p->MoveTo(0, y);
		p->LineTo(rc.Width(), y);
	}
	for (auto x = 0; x < rc.Width(); x += 20)
	{
		p->MoveTo(x, 0);
		p->LineTo(x, rc.Height());
	}
	//p->LineTo(200, 200);

	ReleaseDC(p);
}

void CPlotDlg::draw_sin()
{
	CDC* p = GetDlgItem(IDC_GRAPH)->GetDC();
	CRect rc;
	GetDlgItem(IDC_GRAPH)->GetClientRect(&rc);
	CPen pen(PS_SOLID, 2, RGB(150, 150, 250));
	p->SelectObject(&pen);

	auto h = rc.Height();
	auto x0 = 0;
	auto y0 = h / 2;
	p->MoveTo(x0, y0);//sin(0) = 0
	auto yf = h * 0.4;
	for (auto x = 0; x < rc.Width(); x++)
	{
		double xnew = x * 3.14 / 100;//every 100 pixels = pi radian
		double y = yf * sin((double)xnew);
		y = -y;
		p->LineTo(x + x0, y + y0);
	}
	
	CFont f;
	f.CreatePointFont(200, L"Times New Roman");
	p->SelectObject(&f);
	p->SetBkMode(TRANSPARENT);
	p->TextOutW(10, 10, L"Sin(x)");
	ReleaseDC(p);
}
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPlotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPlotDlg::OnBnClickedLine()
{
	draw_type = DRAW_LINE;
	OnPaint();
}


void CPlotDlg::OnBnClickedGrid()
{
	draw_type = DRAW_GRID;
	OnPaint();
}


void CPlotDlg::OnBnClickedSin()
{
	draw_type = DRAW_SIN;
	//Invalidate(1);
	draw_sin();
	//OnPaint();
}


void CPlotDlg::OnBnClickedFreehand()
{
	draw_type = DRAW_FREE;
}


void CPlotDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	painting = true;
	old_pt = point;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPlotDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	painting = false;
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CPlotDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (painting && (draw_type == DRAW_FREE))
	{
		CDC* p = GetDC();
		p->MoveTo(old_pt);
		p->LineTo(point);
		old_pt = point;
		ReleaseDC(p);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}
