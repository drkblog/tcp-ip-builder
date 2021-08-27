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

// ProtoInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Spoofer.h"
#include "ProtoInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtoInfoDlg dialog


CProtoInfoDlg::CProtoInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProtoInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProtoInfoDlg)
	m_strInfo = _T("");
	//}}AFX_DATA_INIT
}


void CProtoInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtoInfoDlg)
	DDX_Text(pDX, IDC_INFO, m_strInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProtoInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CProtoInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtoInfoDlg message handlers

BOOL CProtoInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	////
	SYSTEM_INFO lpSystemInfo;
	struct hostent FAR *host;
	CString strPArch, strPType, strCName;
	CString strPInfo, strCInfo, strWSInfo;
	CString str, tmp;
	int i=0, j=0;
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;


	SetCursor(LoadCursor(NULL, IDC_WAIT));

	// Sysinfo
	GetSystemInfo(&lpSystemInfo);
 
	switch(lpSystemInfo.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_INTEL:	strPArch = "x86";
											break;
		case PROCESSOR_ARCHITECTURE_MIPS:	strPArch = "MIPS";
											break;
		case PROCESSOR_ARCHITECTURE_ALPHA:	strPArch = "Alpha";
											break;
		case PROCESSOR_ARCHITECTURE_PPC:	strPArch = "PowerPC";
											break;
		case PROCESSOR_ARCHITECTURE_UNKNOWN:	strPArch = "Unknown";
												break;
		case PROCESSOR_ARCHITECTURE_IA64:	strPArch = "IA64";
											break;
		default:	strPArch = "Couldn't get info";
					break;
	}

	if (lpSystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
		switch(lpSystemInfo.wProcessorLevel) {
			case 3: strPType = "Intel 80386";
					break;
			case 4: strPType = "Intel 80486";
					break;
			case 5: strPType = "Intel Pentium";
					break;
			case 6: strPType = "Intel Pentium II, III, IV or better";
					break;
			default:	strPType = "Couldn't get info";
						break;
		}

	if (lpSystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_MIPS)
		strPType = "R4000";

	if (lpSystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
		strPType = "1";

	if (lpSystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ALPHA)
		switch(lpSystemInfo.wProcessorLevel) {
			case 21064: strPType = "Alpha 21064";
					break;
			case 21066: strPType = "Alpha 21066";
					break;
			case 21164: strPType = "Alpha 21164";
					break;
			default:	strPType = "Couldn't get info";
						break;
		}

	if (lpSystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_PPC)
		switch(lpSystemInfo.wProcessorLevel) {
			case 1: strPType = "PPC 601";
					break;
			case 3: strPType = "PPC 603";
					break;
			case 4: strPType = "PPC 604";
					break;
			case 6: strPType = "PPC 603+";
					break;
			case 9: strPType = "PPC 604+";
					break;
			case 20:	strPType = "PPC 620";
						break;
			default:	strPType = "Couldn't get info";
						break;
		}

	strPInfo.Format("Processor architecure: \t%s\r\nProcessor type: \t\t%s\r\nQuantity: \t\t\t%d\r\n", strPArch, strPType, lpSystemInfo.dwNumberOfProcessors);

	// Computer info
 	if (host = gethostbyname ("")) {
		strCInfo.Format("Computer name: \t%s\r\nAddresses: \r\n", host->h_name);

		while(host->h_addr_list[i]) {
			str = "\t\t";
			for(j=0; j<host->h_length; j++) {
				tmp.Format("%d", (unsigned char)host->h_addr_list[i][j]);
				str += tmp;
				if (j<(host->h_length-1)) str += ".";
			}
			str += "\r\n";
			strCInfo.Insert(strCInfo.GetLength(), str);
			i++;
		}
	}
	else {
		strCInfo = "Can't get computer name nor addresses.\r\n";
	}


	// WinSock Info
	wVersionRequested = MAKEWORD(1,0);
 
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		strWSInfo = "Can't find WinSock DLL";
	}
	else {

		strWSInfo.Format("Version: \t\t%d.%d\r\nDescription: \t%s\r\nSystem status: \t%s\r\nMax UDP packet: \t%d bytes\r\n\r\n", HIBYTE(wsaData.wHighVersion), LOBYTE(wsaData.wHighVersion), wsaData.szDescription, wsaData.szSystemStatus, wsaData.iMaxUdpDg);

		/* Clean up*/ 
		WSACleanup();
	}
 
    
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	m_strInfo.Format("--- Processor Info ---\r\n%s\r\n--- Computer Info ---\r\n%s\r\n--- WinSock Info ---\r\n%s\r\n", strPInfo, strCInfo, strWSInfo);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
