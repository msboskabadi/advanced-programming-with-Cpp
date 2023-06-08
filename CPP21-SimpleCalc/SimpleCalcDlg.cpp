
// SimpleCalcDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SimpleCalc.h"
#include "SimpleCalcDlg.h"
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


// CSimpleCalcDlg dialog



CSimpleCalcDlg::CSimpleCalcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIMPLECALC_DIALOG, pParent)
	, num1(0), num2(0), num3(0)
	, operation(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT1, num1);
	DDX_Text(pDX, IDC_EDIT2, num2);
	DDX_Text(pDX, IDC_EDIT3, num3);
	DDX_Radio(pDX, IDC_RD_ADD, operation);
}

BEGIN_MESSAGE_MAP(CSimpleCalcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, &CSimpleCalcDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_SUB, &CSimpleCalcDlg::OnBnClickedBtnSub)
	ON_BN_CLICKED(IDC_BTN_MUL, &CSimpleCalcDlg::OnBnClickedBtnMul)
	ON_BN_CLICKED(IDC_BTN_DIV, &CSimpleCalcDlg::OnBnClickedBtnDiv)
	ON_BN_CLICKED(IDC_RD_ADD, &CSimpleCalcDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_RD_SUB, &CSimpleCalcDlg::OnBnClickedBtnSub)
	ON_BN_CLICKED(IDC_RD_MUL, &CSimpleCalcDlg::OnBnClickedBtnMul)
	ON_BN_CLICKED(IDC_RD_DIV, &CSimpleCalcDlg::OnBnClickedBtnDiv)
	ON_EN_CHANGE(IDC_EDIT1, &CSimpleCalcDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CSimpleCalcDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CSimpleCalcDlg message handlers

BOOL CSimpleCalcDlg::OnInitDialog()
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

void CSimpleCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSimpleCalcDlg::OnPaint()
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
		CPaintDC dc(this); // device context for painting
		CRect rect;
		GetClientRect(&rect);
		CBrush br;
		br.CreateSolidBrush(RGB(255, 255, 220));
		dc.FillRect(&rect, &br);
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSimpleCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSimpleCalcDlg::OnBnClickedBtnAdd()
{
	//static CFont fnt;
	//fnt.CreatePointFont(160, L"Tahoma");
	//m_edit1.SetFont(&fnt);

	UpdateData(TRUE);
	num3 = num1 + num2;
	UpdateData(FALSE);
}


void CSimpleCalcDlg::OnBnClickedBtnSub()
{
	UpdateData(TRUE);
	num3 = num1 - num2;
	UpdateData(FALSE);
}


void CSimpleCalcDlg::OnBnClickedBtnMul()
{
	UpdateData(TRUE);
	num3 = num1 * num2;
	UpdateData(FALSE);
}


void CSimpleCalcDlg::OnBnClickedBtnDiv()
{
	UpdateData(TRUE);
	if (num2)
		num3 = num1 / num2;
	else
		num3 = 0;
	UpdateData(FALSE);
}


void CSimpleCalcDlg::OnEnChangeEdit1()
{
	UpdateData(TRUE);
	switch (operation)
	{
	case 0:
		num3 = num1 + num2;
		break;
	case 1:
		num3 = num1 - num2;
		break;
	case 2:
		num3 = num1 * num2;
		break;
	case 3:
		OnBnClickedBtnDiv();
		break;
	}
	UpdateData(FALSE);
}
