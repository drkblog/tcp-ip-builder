/***********************************************************************************

	TCP/IP Builder -- Windows Socket testing tool
	Copyright (C) 2002 - 2009 by DRK Open source software

	Visit http://www.drk.com.ar/builder.php

	Buenos Aires, Argentina


	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*************************************************************************************/

// SpooferDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Spoofer.h"
#include "SpooferDlg.h"
#include "ProtoInfoDlg.h"
#include "ResolverDlg.h"
#include "HelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern WSADATA wsaData;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnWeb();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_WEB, OnWeb)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpooferDlg dialog

CSpooferDlg::CSpooferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpooferDlg::IDD, pParent)
  , m_bBCast(false)
  , m_bReuse(FALSE)
{
	//{{AFX_DATA_INIT(CSpooferDlg)
	m_iPort = 0;
	m_strReceive = _T("");
	m_strSend = _T("");
	m_bNoRoute = FALSE;
	m_bOOB = FALSE;
	m_iRPort = 0;
	m_strPackets = _T("");
	m_strBytes = _T("");
	m_strLast = _T("");
	m_bKeepAlive = FALSE;
	m_bNoDelay = FALSE;
	m_bDebug = FALSE;
	m_bParse = FALSE;
  ip_count = sizeof(ip_address);
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	// Socket
	m_pSocket = new CMSocket(); 
	
}

void CSpooferDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CSpooferDlg)
  DDX_Control(pDX, IDC_SBUFFER, m_cSBuffer);
  DDX_Control(pDX, IDC_BIND, m_cBind);
  DDX_Control(pDX, IDC_RBUFFER, m_cRBuffer);
  DDX_Control(pDX, IDC_RIPADDR, m_cRIP);
  DDX_Control(pDX, IDC_CONNECT, m_cConnect);
  DDX_Control(pDX, IDC_SEND, m_cSend);
  DDX_Control(pDX, IDC_DESROY, m_cDestroy);
  DDX_Control(pDX, IDC_CREATE, m_cCreate);
  DDX_Control(pDX, IDC_IPADDR, m_cIP);
  DDX_Text(pDX, IDC_PORT, m_iPort);
  DDV_MinMaxUInt(pDX, m_iPort, 0, 65535);
  DDX_Text(pDX, IDC_RBUFFER, m_strReceive);
  DDX_Text(pDX, IDC_SBUFFER, m_strSend);
  DDX_Check(pDX, IDC_NOROUTE, m_bNoRoute);
  DDX_Check(pDX, IDC_OOB, m_bOOB);
  DDX_Text(pDX, IDC_RPORT, m_iRPort);
  DDV_MinMaxUInt(pDX, m_iRPort, 0, 65535);
  DDX_Text(pDX, IDC_PACKETS, m_strPackets);
  DDX_Text(pDX, IDC_BYTES, m_strBytes);
  DDX_Text(pDX, IDC_LAST, m_strLast);
  DDX_Check(pDX, IDC_KEEPALIVE, m_bKeepAlive);
  DDX_Check(pDX, IDC_NODELAY, m_bNoDelay);
  DDX_Check(pDX, IDC_DEBUG, m_bDebug);
  DDX_Check(pDX, IDC_PARSE, m_bParse);
  DDX_Check(pDX, IDC_BCAST, m_bBCast);
  //}}AFX_DATA_MAP
  DDX_Control(pDX, IDC_BCAST, m_cBCast);
}

BEGIN_MESSAGE_MAP(CSpooferDlg, CDialog)
	//{{AFX_MSG_MAP(CSpooferDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_DESROY, OnDesroy)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_EN_CHANGE(IDC_RBUFFER, OnChangeRbuffer)
	ON_BN_CLICKED(IDC_RCLR, OnRclr)
	ON_BN_CLICKED(IDC_SCLR, OnSclr)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_KEEPALIVE, OnKeepalive)
	ON_BN_CLICKED(IDC_NODELAY, OnNodelay)
	ON_BN_CLICKED(IDC_NETSTAT, OnNetstat)
	ON_BN_CLICKED(IDC_DNSRES, OnDnsres)
	ON_BN_CLICKED(IDC_RDETAIL, OnRdetail)
	ON_BN_CLICKED(IDC_HELPB, OnHelpb)
	ON_BN_CLICKED(IDC_BIND, OnBind)
	ON_BN_CLICKED(IDC_DEBUG, OnDebug)
	//}}AFX_MSG_MAP
  ON_BN_CLICKED(IDC_BCAST, &CSpooferDlg::OnBnBroadcase)
  ON_BN_CLICKED(IDC_REUSE, &CSpooferDlg::OnBnClickedReuse)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpooferDlg message handlers

BOOL CSpooferDlg::OnInitDialog()
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

			// No Size
			pSysMenu->EnableMenuItem(2, MF_GRAYED | MF_BYPOSITION);
			// No Maximize
			pSysMenu->EnableMenuItem(4, MF_GRAYED | MF_BYPOSITION);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Init
	LONG res;
	CRegKey registry;
	DWORD dwValue;

  // Get Info
  if (GetAdaptersAddresses(AF_INET, GAA_FLAG_SKIP_DNS_SERVER, 0, ip_address, &ip_count) != ERROR_SUCCESS) {
    MessageBox("Unable to get IP information from the operating system", "Error", MB_ICONWARNING|MB_OK);
  }

	// Default
	m_cIP.SetAddress(127,0,0,1);
	m_cRIP.SetAddress(0,0,0,0);
	m_dwRAddress = 0x00000000;
	CheckRadioButton(IDC_TCP, IDC_UDP, IDC_TCP);
	m_bNoRoute = FALSE;
	m_bOOB = FALSE;
	m_bParse = FALSE;

	// from registry
	res = registry.Open(HKEY_CURRENT_USER, "Software\\DRKLHF\\Builder", KEY_ALL_ACCESS);

	if (res == ERROR_SUCCESS) {

		// IP
		if (registry.QueryDWORDValue("LocalIP", dwValue) != ERROR_SUCCESS) {

			// Set default
			dwValue = 0x7F000001; // 127.0.0.1
		}
		m_cIP.SetAddress(dwValue);

		// Port
		if (registry.QueryDWORDValue("LocalPort", dwValue) != ERROR_SUCCESS) {
			dwValue = 0;
		}
		if (dwValue <= 1024) m_iPort = dwValue;
		

		// TCP/UDP
		if (registry.QueryDWORDValue("Protocol", dwValue) != ERROR_SUCCESS) {
			dwValue = IDC_TCP;
		}
		CheckRadioButton(IDC_TCP, IDC_UDP, dwValue);

		// RemoteIP
		if (registry.QueryDWORDValue("RemoteIP", m_dwRAddress) != ERROR_SUCCESS) {

			// Set default
			m_dwRAddress = 0x00000000; // 0.0.0.0
		}
		m_cRIP.SetAddress(m_dwRAddress);

		// RPort
		if (registry.QueryDWORDValue("RemotePort", dwValue) != ERROR_SUCCESS) {
			dwValue = 0;
		}
		m_iRPort = dwValue;

		// SendFlags
		if (registry.QueryDWORDValue("SFlags", dwValue) != ERROR_SUCCESS) {
			m_bNoRoute = FALSE;
			m_bOOB = FALSE;
			m_bParse = FALSE;
      m_bBCast = FALSE;
		}
		if (dwValue & 0x01) m_bNoRoute = TRUE;
		if (dwValue & 0x02) m_bOOB = TRUE;
		if (dwValue & 0x04) m_bParse = TRUE;
		if (dwValue & 0x08) m_bBCast = TRUE;

	}

	m_cCreate.EnableWindow(TRUE);
	m_cDestroy.EnableWindow(FALSE);
	m_cConnect.EnableWindow(FALSE);
	m_cSend.EnableWindow(FALSE);
	m_cBind.EnableWindow(FALSE);

	DWORD dwVal=1;
	m_pSocket->IOCtl(FIONBIO, &dwVal);

	m_pDetailDlg = NULL;

	m_dwPackets=0;
	m_dwBytes=0;
	m_strPackets.Format("%u", m_dwPackets);
	m_strBytes.Format("%u", m_dwBytes);
	m_strLast.Format("%u", 0);

	UpdateDataPatch(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSpooferDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSpooferDlg::OnPaint() 
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
HCURSOR CSpooferDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CSpooferDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	if (m_pDetailDlg) {
		// Destruyo la ventana
		m_pDetailDlg->DestroyWindow();
		delete m_pDetailDlg;
		m_pDetailDlg = NULL;
	}

	//Socket
	delete m_pSocket;
	
	return CDialog::DestroyWindow();
}

void CSpooferDlg::OnCreate() 
{
	char str[256]={"No more info."};

	//Update
	UpdateDataPatch(TRUE);
	
	//Create
	if (!m_pSocket->Create(m_iPort, m_iType, FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE, m_strIP)) { 

		SetErrorString(m_pSocket->GetLastError(), str, sizeof(str)-1);

		MessageBox(str, "Can't create socket", MB_ICONSTOP | MB_OK);
	}
	else {
		m_cCreate.EnableWindow(FALSE);
		m_cDestroy.EnableWindow(TRUE);
		if (m_iType == SOCK_STREAM) {
			m_cConnect.EnableWindow(TRUE);
			m_cBind.EnableWindow(TRUE);
		}
		else {
			m_cSend.EnableWindow(TRUE);
		}

		if (!m_iPort) {
			m_pSocket->GetSockName(m_strIP, m_iPort);
			UpdateDataPatch(FALSE);
		}
	}

}

void CSpooferDlg::UpdateDataPatch(BOOL bGetData)
{
	BYTE vip[4];
	UINT button;


	// El update normal
	UpdateData(bGetData);

	if (bGetData) {
		// Patch para el IP 
		m_cIP.GetAddress(vip[0], vip[1], vip[2], vip[3]);
		m_strIP.Format("%d.%d.%d.%d", vip[0], vip[1], vip[2], vip[3]);

		// Patch para el RIP 
		m_cRIP.GetAddress(vip[0], vip[1], vip[2], vip[3]);
		m_strRIP.Format("%d.%d.%d.%d", vip[0], vip[1], vip[2], vip[3]);
		m_cRIP.GetAddress(m_dwRAddress);

		// Patch para Protocolo
		button = GetCheckedRadioButton(IDC_TCP, IDC_UDP);
		if (button==IDC_TCP) m_iType = SOCK_STREAM;
		if (button==IDC_UDP) m_iType = SOCK_DGRAM;
	}
	else {
		m_cRBuffer.UpdatePos();

		// Patch para el RIP 
		m_cRIP.SetAddress(m_dwRAddress);
	}

}

void CSpooferDlg::SetErrorString(int error, char *str, int strsize)
{

	switch(error) {
		case WSANOTINITIALISED:strcpy_s(str, strsize, "Socket API not initialized.");
								break;
		case WSAENETDOWN:     strcpy_s(str, strsize, "Network subsystem failed.");
								break;
		case WSAEADDRINUSE:   strcpy_s(str, strsize, "The specified address is already in use.");
								break;
		case WSAEACCES:       strcpy_s(str, strsize, "The requested address is a broadcast address, but the appropriate flag was not set.");
								break;
		case WSAEAFNOSUPPORT:	strcpy_s(str, strsize, "Address family not supported.");
								break;
		case WSAECONNREFUSED:	strcpy_s(str, strsize, "The attempt to connect was rejected.");
								break;
		case WSAEDESTADDRREQ:	strcpy_s(str, strsize, "A destination address is required.");
								break;
		case WSAEINPROGRESS:	strcpy_s(str, strsize, "A blocking Windows Sockets operation is in progress.");
								break;
		case WSAEADDRNOTAVAIL:strcpy_s(str, strsize, "The specified address is not available from the local machine.");
								break;
		case WSAEFAULT:			  strcpy_s(str, strsize, "* The lpBuf argument is not in a valid part of the user address space.");
								break;
		case WSAEINVAL:			  strcpy_s(str, strsize, "Invalid host address / The socket has not been bound with Bind.");
								break;
		case WSAEISCONN:		  strcpy_s(str, strsize, "The socket is already connected.");
								break;
		case WSAEMFILE:			  strcpy_s(str, strsize, "No more file descriptors are available.");
								break;
		case WSAENETUNREACH:	strcpy_s(str, strsize, "The network cannot be reached from this host at this time.");
								break;
		case WSAENETRESET:		strcpy_s(str, strsize, "The connection must be reset because the Windows Sockets implementation dropped it.");
								break;
		case WSAENOBUFS:		  strcpy_s(str, strsize, "No buffer space is available.");
								break;
		case WSAENOTCONN:		  strcpy_s(str, strsize, "The socket is not connected.");
								break;
		case WSAENOTSOCK:		  strcpy_s(str, strsize, "The descriptor is not a socket.");
								break;
		case WSAETIMEDOUT:		strcpy_s(str, strsize, "Attempt to connect timed out without establishing a connection.");
								break;
		case WSAEPROTONOSUPPORT:strcpy_s(str, strsize, "The specified port is not supported.");
								break;
		case WSAEPROTOTYPE:		strcpy_s(str, strsize, "The specified port is the wrong type for this socket.");
								break;
		case WSAESOCKTNOSUPPORT:strcpy_s(str, strsize, "The specified socket type is not supported in this address family.");
								break;
		case WSAEOPNOTSUPP:		strcpy_s(str, strsize, "Out of band was specified, but the socket is not of type TCP.");
								break;
		case WSAESHUTDOWN:		strcpy_s(str, strsize, "The socket has been shut down.");
								break;
		case WSAEWOULDBLOCK:	strcpy_s(str, strsize, "The socket is marked as nonblocking and the requested operation would block.");
								break;
		case WSAEMSGSIZE:		  strcpy_s(str, strsize, "The socket is of type UDP, and the datagram is larger than the maximum supported by the Windows Sockets implementation.");
								break;
		case WSAECONNABORTED:	strcpy_s(str, strsize, "The virtual circuit was aborted due to timeout or other failure.");
								break;
		case WSAECONNRESET:		strcpy_s(str, strsize, "The virtual circuit was reset by the remote side.");
								break;
	}

}

void CSpooferDlg::OnDesroy() 
{
	// TODO: Add your control notification handler code here

	delete m_pSocket;
	m_pSocket = new CMSocket();

	m_strReceive.Empty();

	UpdateDataPatch(FALSE);

	m_cCreate.EnableWindow(TRUE);
	m_cDestroy.EnableWindow(FALSE);
	m_cConnect.EnableWindow(FALSE);
	m_cSend.EnableWindow(FALSE);
	m_cBind.EnableWindow(FALSE);
}

void CSpooferDlg::OnSend() 
{
	int Flags = 0;
	BOOL special;
	char str[256]={"No more info."};
	char stmp[16];
	char *Buffer, *stop;
	int BufferLength, i, j;

	// Leo datos
	UpdateDataPatch(TRUE);

	// Creo buffer binario, si m_bParse estoy alocando a lo sumo memoria de más...
	BufferLength = m_strSend.GetLength();
	Buffer = (char *)malloc(BufferLength); 

	if (Buffer) {
		if (m_bParse) {

			j=0;
			for(i=0; i < m_strSend.GetLength(); i++) {

				special = FALSE;
				if (m_strSend[i] == '0') {
					if ((i+3) < m_strSend.GetLength()) {
						if ((m_strSend[i+1] == 'x') && (isxdigit(m_strSend[i+2])) && (isxdigit(m_strSend[i+3]))) {

							strcpy_s(stmp, sizeof(stmp), m_strSend.Mid(i+2, 2));
							Buffer[j++] = (char)strtol(stmp, &stop, 16);
							i += 3;
							special = TRUE;
							
						}
					}
				}

				if (!special) {
					// Copio el siguiente caracter
					Buffer[j++] = m_strSend[i];
				}
			}

			BufferLength = j;
		}
		else {

			// Copio el contenido de control
			memcpy(Buffer, m_strSend.GetBuffer(m_strSend.GetLength()), BufferLength);
		}
		

		if (m_bNoRoute) Flags |= MSG_DONTROUTE;
		if (m_bOOB) Flags |= MSG_OOB;

		if (m_iType == SOCK_STREAM) {
			if (m_pSocket->Send(Buffer, BufferLength, Flags) == SOCKET_ERROR) {

				SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
				MessageBox(str, "Can't send to socket", MB_ICONSTOP | MB_OK);
			}
			else {
			}
		}
		else {
			if (m_strSend.GetLength()) {
				if (m_strSend.GetLength() < wsaData.iMaxUdpDg) {
					if (m_pSocket->SendTo(Buffer, BufferLength, m_iRPort, m_strRIP, Flags) == SOCKET_ERROR) {

						SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
						MessageBox(str, "Can't send to socket", MB_ICONSTOP | MB_OK);
					}
					else {
					}
				}
				else {
					CString strTmp;
					strTmp.Format("Microsoft's sockects API returned %d as the largest UDP packet possible.", wsaData.iMaxUdpDg);
					MessageBox(strTmp, "UDP Packet Limit", MB_ICONSTOP | MB_OK);
				}
			}
			else {
				MessageBox("Won't send empty UDP packet.", "UDP Protection", MB_ICONSTOP | MB_OK);
			}
		}

		// Libero el buffer
		free(Buffer);
	}
	else {
		MessageBox("Can't allocate memory for binary buffer", "Critical error", MB_ICONSTOP | MB_OK);
	}
}

void CSpooferDlg::OnConnect() 
{
	char str[256]={"No more info."};

	// Leo datos
	UpdateDataPatch(TRUE);

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	// Conecto
	if (!m_pSocket->Connect(m_strRIP, m_iRPort)) {

		if (m_pSocket->GetLastError() != WSAEWOULDBLOCK) {
			SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
			MessageBox(str, "Can't connect socket", MB_ICONSTOP | MB_OK);
		}
		else {
		}
	}
	else {
    SaveToRegistry();

		m_cSend.EnableWindow(TRUE);
	}

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

LRESULT CSpooferDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::WindowProc(message, wParam, lParam);

}

void CSpooferDlg::Receive(BOOL bOOB)
{
	CString tmp, ttmp, strAddress;
	int count, i;
	int flags = 0;
	UINT iPort;
	
  memset(str, 0, RCV_BUFFER_SIZE);

	// OOB
	if (bOOB) flags |= MSG_OOB;

	if (m_iType == SOCK_STREAM) {
		count = m_pSocket->Receive(str, RCV_BUFFER_SIZE-1, flags);
	}
	else {
		count = m_pSocket->ReceiveFrom(str, RCV_BUFFER_SIZE-1, strAddress, iPort, flags);
	}

	// Recibo
	if (!count) {

		if (m_pSocket->GetLastError() != WSAEWOULDBLOCK) {
			SetErrorString(m_pSocket->GetLastError(), estr, sizeof(estr));
			MessageBox(estr, "Can't receive from socket", MB_ICONSTOP | MB_OK);
		}
		else {
			
		}
	}
	else {

		// Details (RAW)
		if (m_pDetailDlg) {
			m_pDetailDlg->AddDetail(str, count);
		}

		// CEdit control...
		for(i=0; i < count; i++) {
			if (str[i]) 
				tmp += str[i];
			else
				tmp += "\\0";
		}


		tmp.Replace("\n\r","\r\n");

		// Patch for limit
		if ((UINT)(tmp.GetLength()+m_strReceive.GetLength()) >= m_cRBuffer.GetLimitText()) 
			m_strReceive.Delete(0, tmp.GetLength());

		if (bOOB) m_strReceive.Insert(m_strReceive.GetLength(), "[OOB >]");
		if ((m_iType != SOCK_STREAM) && (m_bDebug)) {
			ttmp.Format("[From: %s:%u >]", strAddress, iPort);
			m_strReceive.Insert(m_strReceive.GetLength(), ttmp);
		}
		m_strReceive.Insert(m_strReceive.GetLength(), tmp);
		if ((m_iType != SOCK_STREAM) && (m_bDebug)) m_strReceive.Insert(m_strReceive.GetLength(), "[< From]");
		if (bOOB) m_strReceive.Insert(m_strReceive.GetLength(), "[< OOB]");

		m_dwPackets++;
		m_strPackets.Format("%u", m_dwPackets);
		m_strLast.Format("%u", count);
		m_dwBytes += count;
		m_strBytes.Format("%u", m_dwBytes);
	}

	// Escribo datos
	UpdateDataPatch(FALSE);

}

void CSpooferDlg::Connected()
{

	m_cSend.EnableWindow(TRUE);

}

void CSpooferDlg::OnChangeRbuffer() 
{
}

void CSpooferDlg::OnRclr() 
{
	// TODO: Add your control notification handler code here

	UpdateDataPatch(TRUE);
	m_strReceive.Empty();
	m_dwPackets=0;
	m_dwBytes=0;
	m_strPackets.Format("%u", m_dwPackets);
	m_strBytes.Format("%u", m_dwBytes);
	m_strLast.Format("%u", 0);
	UpdateDataPatch(FALSE);

	// Details (RAW)
	if (m_pDetailDlg) {
		m_pDetailDlg->Clear();
	}

	
}

void CSpooferDlg::OnSclr() 
{
	// TODO: Add your control notification handler code here
	
	UpdateDataPatch(TRUE);
	m_strSend.Empty();
	UpdateDataPatch(FALSE);

}

void CAboutDlg::OnWeb() 
{
	CString str;

	str.LoadString(IDS_URL);
	ShellExecute(NULL , "open", str, NULL, NULL, SW_SHOWNORMAL);

}

void CSpooferDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CSpooferDlg::OnKeepalive() 
{
	char str[256]={"No more info."};

	UpdateDataPatch(TRUE);

	if (!m_pSocket->SetSockOpt(SO_KEEPALIVE, &m_bKeepAlive, sizeof(BOOL), SOL_SOCKET)) {
		SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
		MessageBox(str, "Can't modify socket option", MB_ICONSTOP | MB_OK);
	}
}

void CSpooferDlg::OnBnBroadcase()
{
	char str[256]={"Is this an UDP socket?"};

	UpdateDataPatch(TRUE);

	if (!m_pSocket->SetSockOpt(SO_BROADCAST, &m_bBCast, sizeof(BOOL), SOL_SOCKET)) {
		SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
		MessageBox(str, "Can't modify socket option", MB_ICONSTOP | MB_OK);
	}
}

void CSpooferDlg::OnNodelay() 
{
	char str[256]={"No more info."};

	UpdateDataPatch(TRUE);

	if (!m_pSocket->SetSockOpt(TCP_NODELAY, &m_bNoDelay, sizeof(BOOL), IPPROTO_TCP)) {
		SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
		MessageBox(str, "Can't modify socket option", MB_ICONSTOP | MB_OK);
	}
}

void CSpooferDlg::OnBnClickedReuse()
{
	char str[256]={"No more info."};

	UpdateDataPatch(TRUE);

  if (!m_pSocket->SetSockOpt(SO_REUSEADDR, &m_bReuse, sizeof(BOOL), SOL_SOCKET)) {
		SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
		MessageBox(str, "Can't modify socket option", MB_ICONSTOP | MB_OK);
	}
}

void CSpooferDlg::OnNetstat() 
{

	CProtoInfoDlg info;
	info.DoModal();
		
}

void CSpooferDlg::OnDnsres() 
{

	CResolverDlg resolver;
	resolver.DoModal();
}

void CSpooferDlg::OnRdetail() 
{

	if (m_pDetailDlg == NULL) {
		// Creo la ventana
		m_pDetailDlg = new CDetailDlg();

		m_pDetailDlg->Create(IDD_RDWINDOW, NULL);

		m_pDetailDlg->ShowWindow(SW_SHOW);

		SetFocus();
	}
	else {
		// Destruyo la ventana
		m_pDetailDlg->DestroyWindow();

		delete m_pDetailDlg;
		m_pDetailDlg = NULL;
	}

}

void CSpooferDlg::OnHelpb() 
{
	// TODO: Add your control notification handler code here
	
	CHelpDlg hlp;
	hlp.DoModal();
}

void CSpooferDlg::OnBind() 
{
	char str[256]={"No more info."};
	CString tmp;

	// Leo datos
	UpdateDataPatch(TRUE);

	SetCursor(LoadCursor(NULL, IDC_WAIT));


	if (m_pSocket->Listen(1)) {

	}
	else {
		SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
		MessageBox(str, "Can't set the socket to listen", MB_ICONSTOP | MB_OK);
	}

	// Patch for limit
	tmp.Format("Listening for connections...");
	if ((UINT)(tmp.GetLength()+m_strReceive.GetLength()) > m_cRBuffer.GetLimitText()) 
		m_strReceive.Delete(0, tmp.GetLength());

	m_strReceive.Insert(m_strReceive.GetLength(), tmp);

	m_dwRAddress = 0x00000000;
	m_iRPort = 0;

	UpdateDataPatch(FALSE);

	m_cConnect.EnableWindow(FALSE);
	m_cBind.EnableWindow(FALSE);

  SaveToRegistry();

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CSpooferDlg::Accept()
{
	char str[256]={"No more info."};
	CString tmp;
	SOCKADDR_IN SockAddr;
	int SockAddrLen = sizeof(SOCKADDR_IN);

	CMSocket *pTmpSock = new CMSocket();

	if (m_pSocket->Accept(*pTmpSock, (SOCKADDR *)&SockAddr, &SockAddrLen)) {

		// Kill old socket
		delete m_pSocket;

		// Still NASTY
		m_pSocket = pTmpSock;

		m_dwRAddress =	(SockAddr.sin_addr.S_un.S_un_b.s_b1 << 24) |
						(SockAddr.sin_addr.S_un.S_un_b.s_b2 << 16) | 
						(SockAddr.sin_addr.S_un.S_un_b.s_b3 << 8) | 
						(SockAddr.sin_addr.S_un.S_un_b.s_b4 << 0);

		m_iRPort = ntohs(SockAddr.sin_port);
 
		// Patch for limit
		tmp.Format("Connected\r\n");
		if ((UINT)(tmp.GetLength()+m_strReceive.GetLength()) > m_cRBuffer.GetLimitText()) 
			m_strReceive.Delete(0, tmp.GetLength());

		m_strReceive.Insert(m_strReceive.GetLength(), tmp);

		UpdateDataPatch(FALSE);

		m_cSend.EnableWindow(TRUE);

	}
	else {
		SetErrorString(m_pSocket->GetLastError(), str, sizeof(str));
		MessageBox(str, "Can't accept socket connection", MB_ICONSTOP | MB_OK);
	}

}

void CSpooferDlg::OnDebug() 
{
	UpdateDataPatch(TRUE);
}

void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonUp(nFlags, point);

	EndModalLoop(1);
}

void CAboutDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnRButtonUp(nFlags, point);

	EndModalLoop(1);
}

void CSpooferDlg::OnCancel() 
{
	if (MessageBox("Do you really want to quit?", "TCP/IP Builder", MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES) {


		CDialog::OnCancel();
	}
}

void CSpooferDlg::SaveToRegistry()
{
	LONG res;
	CRegKey registry;
	DWORD dwValue;

		// Save to registry
		res = registry.Create(HKEY_CURRENT_USER, "Software\\DRKLHF\\Builder");

		if (res == ERROR_SUCCESS) {

			UpdateDataPatch(TRUE);

			// IP
			m_cIP.GetAddress(dwValue);
			registry.SetDWORDValue("LocalIP", dwValue);

			// Port
			registry.SetDWORDValue("LocalPort", m_iPort);

			// TCP/UDP
			dwValue = GetCheckedRadioButton(IDC_TCP, IDC_UDP);
			registry.SetDWORDValue("Protocol", dwValue);

			// RIP
			m_cRIP.GetAddress(dwValue);
			registry.SetDWORDValue("RemoteIP", dwValue);

			// RPort
			registry.SetDWORDValue("RemotePort", m_iRPort);

			// SendFlags
			dwValue = 0;
			if (m_bNoRoute) dwValue |= 0x01;
			if (m_bOOB) dwValue |= 0x02;
			if (m_bParse) dwValue |= 0x04;
      if (m_bBCast) dwValue |= 0x08;
			registry.SetDWORDValue("SFlags", dwValue);
		}
}

