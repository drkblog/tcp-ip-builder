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

// ResolverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Spoofer.h"
#include "ResolverDlg.h"
#include "CAddressResolver.h"

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
	CAddressResolver resolver;
	CString strCInfo, ips, error;

	UpdateData(TRUE);

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	if (resolver.resolve(m_strName, ips, error) == 0) {
		strCInfo.Format("Addresses: \r\n%s\r\n", ips);
	}
	else {
		strCInfo.Format("Can't get computer name nor addresses: %s\r\n", error);
	}

	SetCursor(LoadCursor(NULL, IDC_ARROW));

	m_strResult.Format("--- DNS lookup for '%s' ---\r\n%s", m_strName, strCInfo);
	
	UpdateData(FALSE);
}
