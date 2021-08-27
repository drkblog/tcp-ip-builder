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

#if !defined(AFX_DRKEDIT2_H__6A300BE4_7577_11D6_804B_004033E1EE0D__INCLUDED_)
#define AFX_DRKEDIT2_H__6A300BE4_7577_11D6_804B_004033E1EE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DRKEdit2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDRKEdit2 window

class CDRKEdit2 : public CEdit
{
// Construction
public:
	CDRKEdit2();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDRKEdit2)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDRKEdit2();

	// Generated message map functions
protected:
	BOOL m_bLowSpecial;
	char m_strBuffer[5];
	int m_iCount;
	BOOL m_bSpecial;
	//{{AFX_MSG(CDRKEdit2)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRKEDIT2_H__6A300BE4_7577_11D6_804B_004033E1EE0D__INCLUDED_)
