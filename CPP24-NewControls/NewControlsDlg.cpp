
// NewControlsDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "NewControls.h"
#include "NewControlsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_PROCESS 100
#define TIMER_CLOCK	  101
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


// CNewControlsDlg dialog



CNewControlsDlg::CNewControlsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWCONTROLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNewControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANIMATE1, anim);
	DDX_Control(pDX, IDC_BROWSE, browse_dlg);
	DDX_Control(pDX, IDC_PROGRESS1, progress);
	DDX_Control(pDX, IDC_SLIDER1, slider);
	DDX_Control(pDX, IDC_COMBO1, combo);
}

BEGIN_MESSAGE_MAP(CNewControlsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PLAY, &CNewControlsDlg::OnBnClickedBtnPlay)
	ON_EN_CHANGE(IDC_BROWSE, &CNewControlsDlg::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CNewControlsDlg::OnBnClickedBtnProcess)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SHOW, &CNewControlsDlg::OnBnClickedBtnShow)
END_MESSAGE_MAP()


// CNewControlsDlg message handlers

BOOL CNewControlsDlg::OnInitDialog()
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

	progress.SetRange(0, 100);
	slider.SetRange(-50, 50);
	progress.SetPos(0);
	slider.SetPos(0);
	slider.UpdateWindow();

	SetTimer(TIMER_CLOCK, 500, 0);

	static CFont f;
	f.CreatePointFont(200, L"Times New Roman");
	GetDlgItem(IDC_CLOCK)->SetFont(&f);	

	combo.AddString(L"مشهد");
	combo.AddString(L"تهران");
	combo.AddString(L"شیراز");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNewControlsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNewControlsDlg::OnPaint()
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
HCURSOR CNewControlsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNewControlsDlg::OnBnClickedBtnPlay()
{	
	if (anim.IsPlaying())
	{
		anim.Stop();
		SetDlgItemTextW(IDC_BTN_PLAY, L"Play");
	}
	else
	{
		anim.Play(0, -1, 3);
		SetDlgItemTextW(IDC_BTN_PLAY, L"Stop");
	}
}


void CNewControlsDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString path;
	GetDlgItemText(IDC_BROWSE, path);
	anim.Open(path);
}


void CNewControlsDlg::OnBnClickedBtnProcess()
{
	CString s;
	GetDlgItemText(IDC_BTN_PROCESS, s);
	if (s == "Start Process")
	{
		SetTimer(TIMER_PROCESS, 50, 0);
		SetDlgItemText(IDC_BTN_PROCESS, L"Stop");
	}
	else 
	{
		KillTimer(TIMER_PROCESS);
		SetDlgItemText(IDC_BTN_PROCESS, L"Start Process");
	}
}

void CNewControlsDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_PROCESS)
	{
		int p = progress.GetPos();
		if (p >= 100)
			p = -1;
		progress.SetPos(p + 1);

		p = slider.GetPos();
		if (p >= 50)
			p = -51;
		slider.SetPos(p + 1);
	}
	else if (nIDEvent == TIMER_CLOCK)
	{
		SYSTEMTIME t;
		GetLocalTime(&t);
		CString s;
		s.Format(L"%02d:%02d:%02d", t.wHour, t.wMinute, t.wSecond);
		SetDlgItemText(IDC_CLOCK, s);
	}

	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CNewControlsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_CLOCK)
	{
		pDC->SetTextColor(RGB(0, 0, 200));
		pDC->SetBkMode(TRANSPARENT);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CNewControlsDlg::OnBnClickedBtnShow()
{
	int sel = combo.GetCurSel();
	CString str;
	combo.GetWindowTextW(str);

	str.AppendFormat(L" (idx = %d)", sel);

	MessageBox(str);
}
