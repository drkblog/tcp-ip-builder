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

// SpooferDlg.h : header file
//

#if !defined(AFX_SPOOFERDLG_H__D1DD7968_5BB1_11D6_804B_004033E1EE0D__INCLUDED_)
#define AFX_SPOOFERDLG_H__D1DD7968_5BB1_11D6_804B_004033E1EE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Iphlpapi.h>

#include "MSocket.h"
#include "DRKEdit.h"
#include "DRKEdit2.h"
#include "DetailDlg.h"
#include "afxwin.h"

#define RCV_BUFFER_SIZE 1025
#define DRK_IPS 50

/////////////////////////////////////////////////////////////////////////////
// CSpooferDlg dialog

class CSpooferDlg : public CDialog
{
// Construction
public:
	void Accept(void);
	void Connected(void);
	void Receive(BOOL bOOB);
	CSpooferDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSpooferDlg)
	enum { IDD = IDD_SPOOFER_DIALOG };
	CDRKEdit2	m_cSBuffer;
	CButton	m_cBind;
	CDRKEdit	m_cRBuffer;
	CIPAddressCtrl	m_cRIP;
	CButton	m_cConnect;
	CButton	m_cSend;
	CButton	m_cDestroy;
	CButton	m_cCreate;
	CIPAddressCtrl	m_cIP;
	UINT	m_iPort;
	CString	m_strReceive;
	CString	m_strSend;
	BOOL	m_bNoRoute;
	BOOL	m_bOOB;
	UINT	m_iRPort;
	CString	m_strPackets;
	CString	m_strBytes;
	CString	m_strLast;
	BOOL	m_bKeepAlive;
	BOOL	m_bNoDelay;
	BOOL	m_bDebug;
	BOOL	m_bParse;
	//}}AFX_DATA
	IP_ADAPTER_ADDRESSES ip_address[DRK_IPS];
	ULONG ip_address_size = sizeof(ip_address);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpooferDlg)
public:
	virtual BOOL DestroyWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

private:
	char str[RCV_BUFFER_SIZE];
	char estr[256];

// Implementation
protected:
	DWORD m_dwRAddress;
	CDetailDlg * m_pDetailDlg;
	DWORD m_dwBytes;
	DWORD m_dwPackets;
	CString m_strRIP;
	void SetErrorString(int error, char *str, int strsize);
	int m_iType;
	CString m_strIP;
	void UpdateDataPatch(BOOL bGetData);
	CMSocket * m_pSocket;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSpooferDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCreate();
	afx_msg void OnDesroy();
	afx_msg void OnSend();
	afx_msg void OnConnect();
	afx_msg void OnChangeRbuffer();
	afx_msg void OnRclr();
	afx_msg void OnSclr();
	afx_msg void OnAbout();
	afx_msg void OnKeepalive();
	afx_msg void OnNodelay();
	afx_msg void OnNetstat();
	afx_msg void OnDnsres();
	afx_msg void OnRdetail();
	afx_msg void OnHelpb();
	afx_msg void OnBind();
	afx_msg void OnDebug();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
  void SaveToRegistry();
  afx_msg void OnBnBroadcase();
  CButton m_cBCast;
  BOOL m_bBCast;
  BOOL m_bReuse;
  afx_msg void OnBnClickedReuse();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPOOFERDLG_H__D1DD7968_5BB1_11D6_804B_004033E1EE0D__INCLUDED_)
