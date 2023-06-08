
// PhotoEditorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PhotoEditor.h"
#include "PhotoEditorDlg.h"
#include "afxdialogex.h"
#include<chrono>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std::chrono;
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


// CPhotoEditorDlg dialog



CPhotoEditorDlg::CPhotoEditorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PHOTOEDITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhotoEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPhotoEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_OPEN, &CPhotoEditorDlg::OnBnClickedOpen)
	ON_BN_CLICKED(ID_GRAY, &CPhotoEditorDlg::OnBnClickedGray)
	ON_BN_CLICKED(ID_GRAY2, &CPhotoEditorDlg::OnBnClickedGray2)
	ON_BN_CLICKED(IDC_BTN_RESET, &CPhotoEditorDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(ID_NEGATIVE, &CPhotoEditorDlg::OnBnClickedNegative)
	ON_BN_CLICKED(ID_REMOVE_RED, &CPhotoEditorDlg::OnBnClickedRemoveRed)
	ON_BN_CLICKED(ID_BRIGHT, &CPhotoEditorDlg::OnBnClickedBright)
END_MESSAGE_MAP()


// CPhotoEditorDlg message handlers

BOOL CPhotoEditorDlg::OnInitDialog()
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

void CPhotoEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPhotoEditorDlg::OnPaint()
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
		CDC* p = GetDlgItem(IDC_PHOTO)->GetDC();
		CRect rc;
		GetDlgItem(IDC_PHOTO)->GetClientRect(&rc);
		img_work.Draw(p->GetSafeHdc(), rc, Gdiplus::InterpolationModeBilinear);
		ReleaseDC(p);
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPhotoEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPhotoEditorDlg::OnBnClickedOpen()
{
	CFileDialog fdlg(true, L"*.jpg", 0, 6UL, L"JPG Files(*.jpg)|*.jpg|All Files|*.*||");
	fdlg.DoModal();
	if (!img_work.IsNull())
		img_work.Detach();
	
	img_work.Load(fdlg.GetPathName());
	img_org.Load(fdlg.GetPathName());
	
	OnPaint();
}


void CPhotoEditorDlg::OnBnClickedGray()
{
	if (img_work.IsNull())
		return;

	auto start = system_clock::now();

	for (auto y = 0; y < img_work.GetHeight(); y++)
	{
		for (auto x = 0; x < img_work.GetWidth(); x++)
		{
			COLORREF c = img_work.GetPixel(x, y);
			int m = (GetRValue(c) + GetGValue(c) + GetBValue(c))/3;
			img_work.SetPixel(x, y, RGB(m, m, m));
		}
	}

	duration<double> elapsed_seconds = system_clock::now() - start;
	double elapsed_time = elapsed_seconds.count();

	CString str;
	str.Format(L"Time = %f s", elapsed_time);
	AfxMessageBox(str);
	OnPaint();
}


void CPhotoEditorDlg::OnBnClickedGray2()
{
	if (img_work.IsNull())
		return;

	auto start = system_clock::now();

	for (auto y = 0; y < img_work.GetHeight(); y++)
	{
		unsigned char* p = (unsigned char*)img_work.GetPixelAddress(0, y);
		for (auto x = 0; x < img_work.GetWidth(); x++)
		{
			auto r = p[0];
			auto g = p[1];
			auto b = p[2];
			int m = (r + g + b) / 3;
			//img_work.SetPixel(x, y, RGB(m, m, m));
			p[0] = p[1] = p[2] = m;
			p += 3;//point to the next pixel
		}
	}

	duration<double> elapsed_seconds = system_clock::now() - start;
	double elapsed_time = elapsed_seconds.count();

	CString str;
	str.Format(L"Time = %f s", elapsed_time);
	AfxMessageBox(str);
	OnPaint();
}


void CPhotoEditorDlg::OnBnClickedBtnReset()
{
	//img_work = img_org.clone();
	for (auto y = 0; y < img_work.GetHeight(); y++)
	{
		unsigned char* psrc = (unsigned char*)img_org.GetPixelAddress(0, y);
		unsigned char* pdst = (unsigned char*)img_work.GetPixelAddress(0, y);
		memcpy(pdst, psrc, img_work.GetWidth() * 3);
	}

	OnPaint();
}


void CPhotoEditorDlg::OnBnClickedNegative()
{
	if (img_work.IsNull())
		return;

	auto start = system_clock::now();

	for (auto y = 0; y < img_work.GetHeight(); y++)
	{
		unsigned char* p = (unsigned char*)img_work.GetPixelAddress(0, y);
		for (auto x = 0; x < img_work.GetWidth(); x++)
		{
			p[0] = 255 - p[0];
			p[1] = 255 - p[1];
			p[2] = 255 - p[2];
			p += 3;//point to the next pixel
		}
	}

	duration<double> elapsed_seconds = system_clock::now() - start;
	double elapsed_time = elapsed_seconds.count();

	CString str;
	str.Format(L"Time = %f s", elapsed_time);
	AfxMessageBox(str);
	OnPaint();
}


void CPhotoEditorDlg::OnBnClickedRemoveRed()
{
	if (img_work.IsNull())
		return;

	auto start = system_clock::now();

	for (auto y = 0; y < img_work.GetHeight(); y++)
	{
		unsigned char* p = (unsigned char*)img_work.GetPixelAddress(0, y);
		for (auto x = 0; x < img_work.GetWidth(); x++)
		{
			p[2] = 0;//Red = 0
			p += 3;//point to the next pixel
		}
	}

	duration<double> elapsed_seconds = system_clock::now() - start;
	double elapsed_time = elapsed_seconds.count();

	CString str;
	str.Format(L"Time = %f s", elapsed_time);
	AfxMessageBox(str);
	OnPaint();
}


void CPhotoEditorDlg::OnBnClickedBright()
{
	if (img_work.IsNull())
		return;

	auto start = system_clock::now();

	for (auto y = 0; y < img_work.GetHeight(); y++)
	{
		unsigned char* p = (unsigned char*)img_work.GetPixelAddress(0, y);
		for (auto x = 0; x < img_work.GetWidth(); x++)
		{
			p[0] = min(p[0] + 20, 255);//250 + 20 = 270 -> 15
			p[1] = min(p[1] + 20, 255);
			p[2] = min(p[2] + 20, 255);
			p += 3;//point to the next pixel
		}
	}

	duration<double> elapsed_seconds = system_clock::now() - start;
	double elapsed_time = elapsed_seconds.count();

	CString str;
	str.Format(L"Time = %f s", elapsed_time);
	AfxMessageBox(str);
	OnPaint();
}
