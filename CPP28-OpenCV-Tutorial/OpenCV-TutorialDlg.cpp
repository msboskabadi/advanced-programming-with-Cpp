
// OpenCV-TutorialDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "OpenCV-Tutorial.h"
#include "OpenCV-TutorialDlg.h"
#include "afxdialogex.h"
#include <OpenCV.hpp>
#include "Mat-util.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#if _DEBUG
	#pragma comment(lib, "opencv_world470d.lib")
#else
	#pragma comment(lib, "opencv_world470.lib")
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


// OpenCVDlg dialog



OpenCVDlg::OpenCVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENCVTUTORIAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void OpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(OpenCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_OPENIMAGE, &OpenCVDlg::OnBnClickedOpenimage)
	ON_BN_CLICKED(ID_VIDEO, &OpenCVDlg::OnBnClickedVideo)
	ON_BN_CLICKED(ID_VIDEO2, &OpenCVDlg::OnBnClickedVideoInside)
END_MESSAGE_MAP()


// OpenCVDlg message handlers

BOOL OpenCVDlg::OnInitDialog()
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

void OpenCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void OpenCVDlg::OnPaint()
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
HCURSOR OpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void OpenCVDlg::OnBnClickedOpenimage()
{	
	cv::Mat im = cv::imread("D:\\1.jpg", cv::IMREAD_COLOR);
	if (im.empty())
		return;
	cv::Mat im2 = im + 2;
	cv::Mat dst;
	imrotate(im, 10, dst);

	cv::imwrite("D:\\gray.jpg", im);
	cv::imshow("Image", dst);
	cv::waitKey(0);
}


void OpenCVDlg::OnBnClickedVideo()
{
	cv::VideoCapture cap;
	cap.open(0);
	cv::Mat frame;
	cv::namedWindow("Camera 0");
	if (cap.isOpened())
	{
		cap >> frame;
		while (!frame.empty())
		{
			cv::imshow("Camera 0", frame);
			int key = cv::waitKey(33);
			if (key == 27)
				break;
			cap >> frame;
		}
	}

	cv::destroyWindow("Camera 0");
}


void OpenCVDlg::OnBnClickedVideoInside()
{
	cv::VideoCapture cap;
	cap.open("D:\\1.mp4");
	cv::Mat frame, edge;
	CImage img;
	CDC* dc = GetDlgItem(IDC_VIDEO)->GetDC();
	RECT rc;
	GetDlgItem(IDC_VIDEO)->GetClientRect(&rc);

	cv::namedWindow("Camera 0", cv::WINDOW_NORMAL);

	if (cap.isOpened())
	{
		cap >> frame;
		while (!frame.empty())
		{
			cv::imshow("Camera 0", frame);
			cv::Canny(frame, edge, 100, 30);
			Mat2CImage(edge, img);
			img.Draw(dc->GetSafeHdc(), rc, Gdiplus::InterpolationModeBilinear);
			int key = cv::waitKey(33);
			//if (key == 27)
				//break;
			cap >> frame;
		}
	}

	cv::destroyWindow("Camera 0");
	ReleaseDC(dc);
}
