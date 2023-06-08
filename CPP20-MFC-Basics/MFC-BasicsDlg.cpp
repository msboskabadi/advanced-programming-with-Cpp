
// MFC-BasicsDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFC-Basics.h"
#include "MFC-BasicsDlg.h"
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


// CMFCBasicsDlg dialog



CMFCBasicsDlg::CMFCBasicsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASICS_DIALOG, pParent)
	, num1(0), num2(0), num3(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasicsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, num1);
	DDX_Text(pDX, IDC_EDIT2, num2);
	DDX_Text(pDX, IDC_EDIT3, num3);
}

BEGIN_MESSAGE_MAP(CMFCBasicsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_MSG, &CMFCBasicsDlg::OnBnClickedBtnMsg)
	ON_BN_CLICKED(IDC_BTN_RECT, &CMFCBasicsDlg::OnBnClickedBtnRect)
	ON_BN_CLICKED(ID_BTN_COMPUTE, &CMFCBasicsDlg::OnBnClickedBtnCompute)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCBasicsDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCBasicsDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CMFCBasicsDlg message handlers

BOOL CMFCBasicsDlg::OnInitDialog()
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

void CMFCBasicsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCBasicsDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasicsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasicsDlg::OnBnClickedBtnMsg()
{
	MessageBox(L"دانشگاه صنعتی شاهرود - درس برنامه نویسی پیشرفته", L"سلام", 
		MB_RTLREADING|MB_RIGHT|MB_ICONINFORMATION);
}


void CMFCBasicsDlg::OnBnClickedBtnRect()
{
	CDC* p = GetDC();
	p->Rectangle(400, 50, 520, 100);
}


void CMFCBasicsDlg::OnBnClickedBtnCompute()
{
	/*int n1 = GetDlgItemInt(IDC_EDIT1);
	int n2 = GetDlgItemInt(IDC_EDIT2);
	SetDlgItemInt(IDC_EDT_RESULT, n1 + n2);*/

	UpdateData(TRUE);//به روز رسانی متغیرها با استفاده از اطلاعات وارد شده توسط کاربر
	num3 = num1 + num2;
	UpdateData(FALSE);//به روز رسانی کنترلها با متغیرهای مربوطه
}


void CMFCBasicsDlg::OnEnChangeEdit1()
{
	OnBnClickedBtnCompute();
}
