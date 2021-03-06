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

#if !defined(AFX_PROTOINFODLG_H__37CCC5A6_64EA_11D6_804B_004033E1EE0D__INCLUDED_)
#define AFX_PROTOINFODLG_H__37CCC5A6_64EA_11D6_804B_004033E1EE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProtoInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProtoInfoDlg dialog

class CProtoInfoDlg : public CDialog
{
// Construction
public:
	CProtoInfoDlg(PIP_ADAPTER_ADDRESSES addresses, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProtoInfoDlg)
	enum { IDD = IDD_PROTOINFO };
	CString	m_strInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtoInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProtoInfoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	PIP_ADAPTER_ADDRESSES addresses;
public:
	CEdit m_ctlInfo;
	afx_msg void OnClickedCloseInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTOINFODLG_H__37CCC5A6_64EA_11D6_804B_004033E1EE0D__INCLUDED_)
