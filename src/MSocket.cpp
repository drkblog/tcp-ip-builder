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

// MSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Spoofer.h"
#include "MSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSocket

CMSocket::CMSocket()
{
}

CMSocket::~CMSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CMSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMSocket member functions

void CMSocket::SetErrorString(int error, char *str, int strsize)
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


void CMSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	PostMessage(NULL, WM_USER+1, nErrorCode, 0);

	if (nErrorCode) {
		char str[256];

		SetErrorString(nErrorCode, str, sizeof(str));
		MessageBox(AfxGetApp()->m_pMainWnd->m_hWnd, str, "CMSocket", MB_ICONSTOP | MB_OK);
	}

	CAsyncSocket::OnConnect(nErrorCode);
}


void CMSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	PostMessage(NULL, WM_USER+2, nErrorCode, 0);

	if (nErrorCode) {
		char str[256];

		SetErrorString(nErrorCode, str, sizeof(str));
		MessageBox(AfxGetApp()->m_pMainWnd->m_hWnd, str, "CMSocket", MB_ICONSTOP | MB_OK);
	}
	
	CAsyncSocket::OnReceive(nErrorCode);
}

void CMSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	PostMessage(NULL, WM_USER+3, nErrorCode, 0);

	if (nErrorCode) {
		char str[256];

		SetErrorString(nErrorCode, str, sizeof(str));
		MessageBox(AfxGetApp()->m_pMainWnd->m_hWnd, str, "CMSocket", MB_ICONSTOP | MB_OK);
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

void CMSocket::OnOutOfBandData(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	PostMessage(NULL, WM_USER+2, nErrorCode, 1); // OOB

	if (nErrorCode) {
		char str[256];

		SetErrorString(nErrorCode, str, sizeof(str));
		MessageBox(AfxGetApp()->m_pMainWnd->m_hWnd, str, "CMSocket", MB_ICONSTOP | MB_OK);
	}

	CAsyncSocket::OnOutOfBandData(nErrorCode);
}
