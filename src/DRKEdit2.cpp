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

// DRKEdit2.cpp : implementation file
//

#include "stdafx.h"
#include "Spoofer.h"
#include "DRKEdit2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDRKEdit2

CDRKEdit2::CDRKEdit2()
{
	m_bSpecial = FALSE;
	m_bLowSpecial = FALSE;
	m_iCount = 0;
}

CDRKEdit2::~CDRKEdit2()
{
}


BEGIN_MESSAGE_MAP(CDRKEdit2, CEdit)
	//{{AFX_MSG_MAP(CDRKEdit2)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRKEdit2 message handlers

void CDRKEdit2::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	BOOL bPosted = FALSE;
	UINT newChar = 0;

	/* Is the user about to type a special character? */
	if (nChar == '\\') {

		/* Yes, unless it is the second backslash */
		if (!m_bSpecial) {
			m_bSpecial = TRUE;
			m_iCount = 0;
		}
		else {
			m_bSpecial = FALSE;
			m_iCount = 0;
		}

	}

	/* Am I receiving a special character? */
	if (m_bSpecial) {

		/* Is it a digi? */
		if (isdigit(nChar)) {

			/* OK, let's put this digit into the buffer */
			m_strBuffer[m_iCount] = nChar;
			m_iCount++;

			/* at most 3 digits */
			if (m_iCount == 3) m_bSpecial = FALSE;

		}
		else {
			if (nChar != '\\') m_bSpecial = FALSE;
		}

		/* Is this the end of a special input? */
		if (!m_bSpecial) {
			m_strBuffer[m_iCount] = 0;

			/* Build the special character */
			newChar = atoi(m_strBuffer);
			if (newChar >= 256) newChar = 255;

			/* Post it to process as a user input */
			if (newChar < 0x20) m_bLowSpecial = TRUE;
			bPosted = PostMessage(WM_CHAR, (WPARAM)newChar, (LPARAM)nFlags);
			
		}
	}

	if (!m_bSpecial) {

		/* If the special input end up with a space or anything but a digit, 
		   we should make this character visible, then we post this character too
		*/
		if (bPosted) {
			if ((!isdigit(nChar)) && (nChar != ' '))
				PostMessage(WM_CHAR, (WPARAM)nChar, (LPARAM)nFlags);
		}
		else {

			/* Am I processing a special character under 0x20? */
			if ((nChar < 0x20) && (m_bLowSpecial)) {

				CString tmp;

				GetWindowText(tmp);
				tmp.Insert(tmp.GetLength(), nChar);
				SetWindowText(tmp);

				SetSel(tmp.GetLength(), tmp.GetLength(), FALSE);

				m_bLowSpecial = FALSE;

			}
			else {
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
		}
	}
}
