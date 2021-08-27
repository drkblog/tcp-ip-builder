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

// DetailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Spoofer.h"
#include "DetailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDetailDlg dialog


CDetailDlg::CDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDetailDlg)
	m_strScreen = _T("");
	m_bAppend = FALSE;
	m_bBoundaries = FALSE;
	//}}AFX_DATA_INIT
}


void CDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDetailDlg)
	DDX_Control(pDX, IDC_SCREEN, m_cScreen);
	DDX_Text(pDX, IDC_SCREEN, m_strScreen);
	DDX_Check(pDX, IDC_APPEND, m_bAppend);
	DDX_Check(pDX, IDC_BOUNDARIES, m_bBoundaries);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CDetailDlg)
	ON_BN_CLICKED(IDC_APPEND, OnAppend)
	ON_BN_CLICKED(IDC_BOUNDARIES, OnBoundaries)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetailDlg message handlers

void CDetailDlg::AddDetail(char *data, int length)
{
	int i;
	CString tmp;

	if (m_bAppend) {
	}
	else {
		// Clr
		m_strScreen.Empty();
		m_iCP = 0;
	}

	for(i=0; i < length; i++) {
		tmp.Empty();
		// CUIDADO: No quitar (usigned char) cast porque sino se imprimen numeros DWORD en RAW Data window
		tmp.Format("%02X%s", (unsigned char)data[i], ((m_iCP + i + 1)%16)?":":"\r\n");

		// Patch for limit
		if ((UINT)(tmp.GetLength()+m_strScreen.GetLength()) > m_cScreen.GetLimitText()) 
			m_strScreen.Delete(0, tmp.GetLength());

		m_strScreen += tmp;
	}

	if (m_bBoundaries) 
		if (m_strScreen.GetAt(m_strScreen.GetLength() - 1) == ':')
			m_strScreen.SetAt(m_strScreen.GetLength() - 1, '|');

	UpdateData(FALSE);

	m_cScreen.UpdatePos();

	m_iCP += i;
	if (m_iCP >= 16) m_iCP %= 16;
}

void CDetailDlg::Clear()
{
	// Clr
	m_strScreen.Empty();
	m_iCP = 0;
	UpdateData(FALSE);
}

BOOL CDetailDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Init
	
	m_bAppend = TRUE;
	m_bBoundaries = FALSE;
	m_strScreen.Empty();
	m_iCP = 0;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDetailDlg::OnAppend() 
{
	UpdateData(TRUE);
}

void CDetailDlg::OnBoundaries() 
{
	UpdateData(TRUE);
}
