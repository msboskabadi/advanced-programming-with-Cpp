
// VideoInThreadDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "VideoInThread.h"
#include "VideoInThreadDlg.h"
#include "afxdialogex.h"
#include "Mat-util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
#pragma comment (lib, "opencv_world470d.lib")
#else
#pragma comment (lib, "opencv_world470.lib")
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


// VideoDlg dialog



VideoDlg::VideoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CPP32SHOWVIDEOINTHREAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void VideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(VideoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_PLAY, &VideoDlg::OnBnClickedPlay)
	ON_BN_CLICKED(ID_INFO, &VideoDlg::OnBnClickedInfo)
	ON_BN_CLICKED(ID_PLAY_TRD, &VideoDlg::OnBnClickedPlayTrd)
END_MESSAGE_MAP()


// VideoDlg message handlers

BOOL VideoDlg::OnInitDialog()
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

void VideoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void VideoDlg::OnPaint()
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
HCURSOR VideoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void VideoDlg::OnBnClickedPlay()
{
	cap.open("D:\\Projects\\_OCV Samples\\768x576.avi");
	//cv::VideoCapture cap("http://192.168.43.1:8080/shot.jpg");
	if (!cap.isOpened())
	{
		MessageBox(L"video file can not be opened!\n");
		return;
	}
	cv::Mat frame;
	cap >> frame;
	//cv::cvtColor(rgb_frame, gray_frame, cv::COLOR_BGR2GRAY);
	CImage img;

	HDC dc = GetDlgItem(IDC_VIDEO)->GetDC()->GetSafeHdc();
	CRect rc;
	GetDlgItem(IDC_VIDEO)->GetClientRect(&rc);
	while (!frame.empty())
	{
		//cv::imshow("RGB", frame);		
		Mat2CImage(frame, img);
		img.Draw(dc, rc, Gdiplus::InterpolationModeBilinear);
		Sleep(30);
		//cv::waitKey(30);

		cap >> frame;
	}
}

void VideoDlg::OnBnClickedInfo()
{
	MessageBox(L"Salaam");
}

DWORD WINAPI TrdPlay(void* param)
{	
	VideoDlg* p = (VideoDlg*) param;

	p->cap.open("D:\\Projects\\_OCV Samples\\768x576.avi");
	//cv::VideoCapture cap("http://192.168.43.1:8080/shot.jpg");
	if (!p->cap.isOpened())
	{
		p->MessageBox(L"video file can not be opened!\n");
		return 0;
	}
	cv::Mat frame;
	p->cap >> frame;
	//cv::cvtColor(rgb_frame, gray_frame, cv::COLOR_BGR2GRAY);
	CImage img;

	HDC dc = p->GetDlgItem(IDC_VIDEO)->GetDC()->GetSafeHdc();
	CRect rc;
	p->GetDlgItem(IDC_VIDEO)->GetClientRect(&rc);
	while (!frame.empty())
	{
		//cv::imshow("RGB", frame);

		Mat2CImage(frame, img);
		img.Draw(dc, rc, Gdiplus::InterpolationModeBilinear);
		Sleep(30);
		//cv::waitKey(30);

		p->cap >> frame;
	}

}

void VideoDlg::OnBnClickedPlayTrd()
{
	trd = std::thread(TrdPlay, this);
	
	//HANDLE h = CreateThread(0, 0, TrdPlay, this, 0, 0);
	//WaitForSingleObject(h, 2000);
	
	//Join or detach?
	// When you do File / New you create a new thread and you detach it : 
	// the thread will be closed when the user closes the document 
	// Here you don't need to join the threads
	// 
	// When you do a Monte Carlo simulation, some distributed computing, 
	// or any Divide And Conquer type algorithms, you launch all the threads 
	// and you need to wait for all the results so that you can combine them.
	// Here you explicitly need to join the thread before combining the results
	
	trd.detach();//Detaches the thread represented by the object from the calling thread, allowing them to execute independently from each other.
}
