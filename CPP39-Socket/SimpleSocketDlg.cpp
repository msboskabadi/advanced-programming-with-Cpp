// SimpleSocketDlg.cpp : implementation file
//

#using <mscorlib.dll>
#include "stdafx.h"
#include "SimpleSocket.h"
#include "SimpleSocketDlg.h"
#include "Socket1.h"
#include ".\SimpleSocketdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SimpleSocketDlg dialog

SimpleSocketDlg::SimpleSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(SimpleSocketDlg::IDD, pParent)
{
	app_type = -1;
	server_ip = _T("");
	port_num = 2000;
	message = _T("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void SimpleSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SimpleSocketDlg)
	DDX_Control(pDX, IDC_LRECVD, received_list);
	DDX_Control(pDX, IDC_LSENT, sent_list);
	DDX_Control(pDX, IDC_BCONNECT, btn_connect);
	DDX_Radio(pDX, IDC_RCLIENT, app_type);
	DDX_Text(pDX, IDC_ESERVNAME, server_ip);
	DDX_Text(pDX, IDC_ESERVPORT, port_num);
	DDX_Text(pDX, IDC_EMSG, message);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(SimpleSocketDlg, CDialog)
	//{{AFX_MSG_MAP(SimpleSocketDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BCONNECT, OnBconnect)
	ON_BN_CLICKED(IDC_RCLIENT, OnAppType)
	ON_BN_CLICKED(IDC_BSEND, OnSendMsg)
	ON_BN_CLICKED(IDC_RSERVER, OnAppType)
	ON_BN_CLICKED(IDC_BCLOSE, OnBclose)
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_REPLACE, OnBnClickedReplace)
	ON_BN_CLICKED(IDC_SEND_FREQ, OnBnClickedSendFreq)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAR_SENT, OnBnClickedClearSent)
	ON_BN_CLICKED(IDC_CLEAR_RCVD, OnBnClickedClearRcvd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SimpleSocketDlg message handlers

BOOL SimpleSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	//Mine
	AfxSocketInit();
	app_type = 0;
	server_ip = "loopback"; //127.1.1.1
	port_num = 2000;
	UpdateData(FALSE);
	
	connect_socket.SetParent(this);
	listen_socket.SetParent(this);
	
	//sent_list.AddString("Sent Messages will show here");
	//sent_list.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void SimpleSocketDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR SimpleSocketDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void SimpleSocketDlg::UpdateUI(bool enable)
{
	GetDlgItem(IDC_BCONNECT)->EnableWindow(enable);
	GetDlgItem(IDC_ESERVNAME)->EnableWindow(enable);
	GetDlgItem(IDC_ESERVPORT)->EnableWindow(enable);
	GetDlgItem(IDC_STATICNAME)->EnableWindow(enable);
	GetDlgItem(IDC_STATICPORT)->EnableWindow(enable);
	GetDlgItem(IDC_RCLIENT)->EnableWindow(enable);
	GetDlgItem(IDC_RSERVER)->EnableWindow(enable);
}

void SimpleSocketDlg::OnBconnect()
{
	UpdateData();
	//GetDlgItem(IDC_STATICTYPE)->EnableWindow(FALSE);

	UpdateUI(false);
	if(app_type == APP_CLINET)
	{
		if(!connect_socket.Create())
			MessageBox("Error Creating Connection Socket","Sorry!");
		if (!connect_socket.Connect(server_ip, port_num)) //Port numbers can run from 0 to 65353
		{
			//MessageBox("Error while connecting","Sorry!");
		}
		else
			MessageBox("Connected");
		/*int i = connect_socket.GetLastError();
		if (state) MessageBox("Connected!!!","OK!");
		else 
		{
			MessageBox("Error creating socket!!!","Sorry!");
			m_iPort = i;
			UpdateData(FALSE);
		}*/


	}
	else //SERVER
	{
		if (!listen_socket.Create(port_num))
			MessageBox("Error Creating Listening Socket!");
		if (!listen_socket.Listen())
			MessageBox("Error while listening!");
	}	

	UpdateData(FALSE);
}

void SimpleSocketDlg::OnAppType() 
{
	UpdateData(TRUE); 
	if (app_type == APP_CLINET)
		btn_connect.SetWindowText("C&onnect");
	else
		btn_connect.SetWindowText("&listen");
	UpdateData(FALSE);
}

//called in server app
void SimpleSocketDlg::OnAccept()
{
	listen_socket.Accept(connect_socket);
	GetDlgItem(IDC_EMSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BSEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATICMSG)->EnableWindow(TRUE);
}

//called in client app
void SimpleSocketDlg::OnConnect()
{
	GetDlgItem(IDC_EMSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BSEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATICMSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BCLOSE)->EnableWindow(TRUE);
}

void SimpleSocketDlg::OnReceive()
{
	char *pBuf = new char[1025];
	int iBufSize = 1024;
	int iRcvd;
	CString strRecvd;
	
	iRcvd = connect_socket.Receive(pBuf, iBufSize);
	if(iRcvd == SOCKET_ERROR)
	{
		//
	}
	else
	{
		pBuf[iRcvd] = NULL;
		strRecvd = pBuf;
		received_list.AddString(strRecvd);
		UpdateData(FALSE);
	}
}

void SimpleSocketDlg::OnSend()
{
}

void SimpleSocketDlg::OnClose()
{
	connect_socket.Close();
	GetDlgItem(IDC_EMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BSEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATICMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BCLOSE)->EnableWindow(FALSE);

	if(app_type == APP_CLINET)
	{
		GetDlgItem(IDC_BCONNECT)->EnableWindow(TRUE);
		GetDlgItem(IDC_ESERVNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_ESERVPORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATICNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATICPORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_RCLIENT)->EnableWindow(TRUE);
		GetDlgItem(IDC_RSERVER)->EnableWindow(TRUE);
		//GetDlgItem(IDC_STATICTYPE)->EnableWindow(TRUE);
	}
}

void SimpleSocketDlg::OnSendMsg() 
{
	int iLen,iSent;
	UpdateData(TRUE);
	if(message != "")
	{
		iLen = message.GetLength();
		iSent = connect_socket.Send(LPCTSTR(message), iLen);
		if(iSent == SOCKET_ERROR)
		{

		}

		else
		{
			sent_list.AddString(message);
			int N = sent_list.GetCount();
			sent_list.SetCurSel(N-1);
			UpdateData(FALSE);
		}

	}
}

void SimpleSocketDlg::OnBclose() 
{
	OnClose();	
}

void SimpleSocketDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
}

void SimpleSocketDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags, point);
}

void SimpleSocketDlg::OnBnClickedReplace()
{
	sent_list.GetText(sent_list.GetCurSel(),message);
	UpdateData(FALSE);
}

void SimpleSocketDlg::OnBnClickedSendFreq()
{
	static bool bSend = true;
	if(bSend)
	{
		SetDlgItemText(IDC_SEND_FREQ, "Stop Sending");
		SetTimer(SEND_FREQ, 100, 0);
	}
	else
	{
		SetDlgItemText(IDC_SEND_FREQ, "Send Frequently");
		KillTimer(SEND_FREQ);
	}
	bSend = !bSend;
}

void SimpleSocketDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == SEND_FREQ)
	{
		int iLen,iSent;
		UpdateData(TRUE);
		if(message != "")
		{
			iLen = message.GetLength();
			iSent = connect_socket.Send(LPCTSTR(message),iLen);
			if(iSent == SOCKET_ERROR)
			{
				TRACE("SOCKET_ERROR When Sending\n");
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void SimpleSocketDlg::OnBnClickedClearSent()
{
	sent_list.ResetContent();
}

void SimpleSocketDlg::OnBnClickedClearRcvd()
{
	received_list.ResetContent();
}
