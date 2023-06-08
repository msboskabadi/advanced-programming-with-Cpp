// testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultiCoreTest.h"
#include "MultiCoreTestDlg.h"
#include <math.h>
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMultiCoreTestDlg dialog




CMultiCoreTestDlg::CMultiCoreTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiCoreTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultiCoreTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMultiCoreTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_1Thread, &CMultiCoreTestDlg::OnBnClicked1thread)
	ON_BN_CLICKED(ID_2Thread, &CMultiCoreTestDlg::OnBnClicked2thread)
	ON_BN_CLICKED(ID_4Thread, &CMultiCoreTestDlg::OnBnClicked4thread)
	ON_BN_CLICKED(IDC_NoThread, &CMultiCoreTestDlg::OnBnClickedNothread)
//	ON_STN_CLICKED(IDC_HyperLink, &CMultiCoreTestDlg::OnStnClickedHyperlink)
END_MESSAGE_MAP()


// CMultiCoreTestDlg message handlers

BOOL CMultiCoreTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

void CMultiCoreTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMultiCoreTestDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

void CMultiCoreTestDlg::OnBnClicked1thread()
{
	OnOK();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMultiCoreTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

double StopWatch(int start0stop1 = 0, bool showMessage = false)
{
   static LARGE_INTEGER swFreq = {0, 0}, swStart, swStop; 
   static const double TwoPow32 = pow(2.0, 32.0);
   if(!swFreq.LowPart)
      QueryPerformanceFrequency(&swFreq);
   double result = -1;
   if (start0stop1==0)	QueryPerformanceCounter(&swStart);
   else {
      QueryPerformanceCounter(&swStop);
      if (swFreq.LowPart==0 && swFreq.HighPart==0) return -1;
      else {
         result = (double)((swStop.HighPart - swStart.HighPart)*TwoPow32 + swStop.LowPart - swStart.LowPart);
         if (result < 0) result += TwoPow32;
         result /= (swFreq.LowPart+ swFreq.HighPart*TwoPow32);
      }
      if(showMessage){
         CString s;
         s.Format(_T("Time (s): %.3f"),result);
         MessageBox(NULL, s, _T("Elapsed Time"), 0);
      }
   }
   return result;
};


const int SZ = 1024*1024*200;
float* x = new float[SZ];
int nTh = 1;

DWORD WINAPI Trd1(void* param)
{
	CMultiCoreTestDlg* p = (CMultiCoreTestDlg*)param;

	for (int i = 0; i < SZ/nTh; i++){
		x[i] = sin((double)i/360.0)*log((double)i)*atan2((double)i/360.0, -i);
	}

	//p->SetDlgItemTextW(IDC_TRD1, L"Thread 1 Finished!");
	//p->Invalidate();
	return 0;
}

DWORD WINAPI Trd2(void* param)
{	
	CMultiCoreTestDlg* p = (CMultiCoreTestDlg*)param;
	for (int i = SZ/nTh; i < 2*SZ/nTh; i++){
		x[i] = sin((double)i/360.0)*log((double)i)*atan2((double)i/360.0, -i);
	}

	//p->SetDlgItemTextW(IDC_TRD2, L"Thread 2 Finished!");
	//p->Invalidate();
	return 0;
}

DWORD WINAPI Trd3(LPVOID param)
{
	for (int i = 2*SZ/nTh; i < 3*SZ/nTh; i++){
		x[i] = sin((double)i/360.0)*log((double)i)*atan2((double)i/360.0, -i);
	}
	return 0;
}

DWORD WINAPI Trd4(LPVOID param)
{
	for (int i = 3*SZ/nTh; i < SZ; i++){
		x[i] = sin((double)i/360.0)*log((double)i)*atan2((double)i/360.0, -i);
	}
	return 0;
}


void CMultiCoreTestDlg::OnBnClicked2thread()
{
	StopWatch(0);
	
	nTh = 2;
	
	HANDLE h1 = CreateThread(0, 0, Trd1, this, 0, 0);
	HANDLE h2 = CreateThread(0, 0, Trd2, this, 0, 0);
	
	WaitForSingleObject(h1, 50000);
	WaitForSingleObject(h2, 50000);
	CloseHandle(h1);
	CloseHandle(h2);
	StopWatch(1, true);
}

void CMultiCoreTestDlg::OnBnClicked4thread()
{
	StopWatch(0);
	
	nTh = 4;

	HANDLE h[4] = {0};
	h[0] = CreateThread(0, 0, Trd1, 0, 0, 0);
	h[1] = CreateThread(0, 0, Trd2, 0, 0, 0);
	h[2] = CreateThread(0, 0, Trd3, 0, 0, 0);
	h[3] = CreateThread(0, 0, Trd4, 0, 0, 0);
	
	WaitForMultipleObjects(4, h, 1, 50000);

	for(int i = 0; i < 4; i++)
		CloseHandle(h[i]);
	
	/*std::thread trd[4];
	trd[0] = std::thread(Trd1, this);
	trd[1] = std::thread(Trd2, this);
	trd[2] = std::thread(Trd3, this);
	Trd4(this);

	for (int i = 0; i < 3; i++)
	{
		trd[i].join();
	}*/
	
	StopWatch(1, true);
}

void CMultiCoreTestDlg::OnBnClickedNothread()
{
	StopWatch(0);

	for (int i = 0; i < SZ; i++)
		x[i] = sin((double)i/360.0)*log((double)i)*atan2((double)i/360.0, -i);

	StopWatch(1, true);
}

