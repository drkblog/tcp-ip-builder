/***********************************************************************************

	TCP/IP Builder -- Windows Socket testing tool
	Copyright (C) 2002 - 2009 by DRK Open source software

	Visit https://www.drk.com.ar/en/legacy/tcp-ip-builder

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
#include "AddressResolver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtoInfoDlg dialog


CProtoInfoDlg::CProtoInfoDlg(PIP_ADAPTER_ADDRESSES addresses, CWnd* pParent /*=NULL*/)
	: CDialog(CProtoInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProtoInfoDlg)
	m_strInfo = _T("");
	//}}AFX_DATA_INIT
	this->addresses = addresses;
}


void CProtoInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtoInfoDlg)
	DDX_Text(pDX, IDC_INFO, m_strInfo);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_INFO, m_ctlInfo);
}


BEGIN_MESSAGE_MAP(CProtoInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CProtoInfoDlg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CLOSE_INFO, &CProtoInfoDlg::OnClickedCloseInfo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtoInfoDlg message handlers

BOOL CProtoInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	////
	SYSTEM_INFO lpSystemInfo;
	CString strPArch, strPType, strCName;
	CString strPInfo, strNetworkAdapters, strWSInfo;
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
	PIP_ADAPTER_ADDRESSES address = addresses;
	while (address != NULL) {
		strNetworkAdapters.Append(CStringA(address->FriendlyName) + "\r\n");
		strNetworkAdapters.Append(CStringA(address->Description) + "\r\n");
		strNetworkAdapters.Append(CStringA(address->AdapterName) + "\r\n");
		strNetworkAdapters.Append("MAC: ");
		for (UINT i = 0; i < address->PhysicalAddressLength; i++) {
			CString number;
			number.Format("%02X", address->PhysicalAddress[i]);
			strNetworkAdapters.Append(number);
			if (i+1 < address->PhysicalAddressLength) {
				strNetworkAdapters.Append(":");
			}
		}
		strNetworkAdapters.Append("\r\n\r\n");
		address = address->Next;
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
	m_strInfo.Format("--- Processor Info ---\r\n%s\r\n--- Network adapters ---\r\n%s\r\n--- WinSock Info ---\r\n%s\r\n", strPInfo, strNetworkAdapters, strWSInfo);

	m_ctlInfo.SetSel(-1,0);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CProtoInfoDlg::OnClickedCloseInfo()
{
	EndDialog(0);
}
