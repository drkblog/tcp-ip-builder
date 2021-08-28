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

// Spoofer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Spoofer.h"
#include "SpooferDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpooferApp

BEGIN_MESSAGE_MAP(CSpooferApp, CWinApp)
	//{{AFX_MSG_MAP(CSpooferApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpooferApp construction

CSpooferApp::CSpooferApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSpooferApp object

CSpooferApp theApp;
WSADATA wsaData;

/////////////////////////////////////////////////////////////////////////////
// CSpooferApp initialization

BOOL CSpooferApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
    // manifest specifies use of ComCtl32.dll version 6 or later to enable
    // visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	if (!AfxSocketInit(&wsaData))
	{
		AfxMessageBox("Unable to initialize Sockets API.", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
#endif

	m_pDlg = new CSpooferDlg();
	m_pMainWnd = m_pDlg;
	int nResponse = m_pDlg->DoModal();

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	delete m_pDlg;

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



BOOL CSpooferApp::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message) {
						// OnConnect
		case WM_USER+1: if (m_pDlg) {
							m_pDlg->Connected();
						}
						break;
						// OnReceive data
		case WM_USER+2:	if (m_pDlg) {
							m_pDlg->Receive(pMsg->lParam > 0);
						}
						break;
						// OnAccept
		case WM_USER+3:	if (m_pDlg) {
							m_pDlg->Accept();
						}
						break;
	}
	
	return CWinApp::PreTranslateMessage(pMsg);
}
