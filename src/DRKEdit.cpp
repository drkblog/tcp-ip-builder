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

// DRKEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Spoofer.h"
#include "DRKEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDRKEdit

CDRKEdit::CDRKEdit()
{
}

CDRKEdit::~CDRKEdit()
{
}


BEGIN_MESSAGE_MAP(CDRKEdit, CEdit)
	//{{AFX_MSG_MAP(CDRKEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRKEdit message handlers

void CDRKEdit::UpdatePos()
{
	LineScroll(this->GetLineCount(), 0);
}

