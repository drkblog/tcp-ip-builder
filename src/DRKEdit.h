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

#if !defined(AFX_DRKEDIT_H__727E45E1_5FAC_11D6_804B_004033E1EE0D__INCLUDED_)
#define AFX_DRKEDIT_H__727E45E1_5FAC_11D6_804B_004033E1EE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DRKEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDRKEdit window

class CDRKEdit : public CEdit
{
// Construction
public:
	CDRKEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDRKEdit)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdatePos(void);
	virtual ~CDRKEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDRKEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRKEDIT_H__727E45E1_5FAC_11D6_804B_004033E1EE0D__INCLUDED_)
