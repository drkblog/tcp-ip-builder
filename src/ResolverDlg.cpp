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

// ResolverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Spoofer.h"
#include "ResolverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResolverDlg dialog


CResolverDlg::CResolverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResolverDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResolverDlg)
	m_strName = _T("");
	m_strResult = _T("");
	//}}AFX_DATA_INIT
}


void CResolverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResolverDlg)
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 256);
	DDX_Text(pDX, IDC_RESULT, m_strResult);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResolverDlg, CDialog)
	//{{AFX_MSG_MAP(CResolverDlg)
	ON_BN_CLICKED(IDC_RESOLVE, OnResolve)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResolverDlg message handlers

void CResolverDlg::OnResolve() 
{
	CString strCInfo, tmp, str;
	struct hostent *host;
	int i=0, j=0;

	UpdateData(TRUE);

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	if (host = gethostbyname (m_strName)) {
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

	SetCursor(LoadCursor(NULL, IDC_ARROW));

	m_strResult.Format("--- DNS lookup for '%s' ---\r\n%s", m_strName, strCInfo);
	
	UpdateData(FALSE);
}
