// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D1DD796A_5BB1_11D6_804B_004033E1EE0D__INCLUDED_)
#define AFX_STDAFX_H__D1DD796A_5BB1_11D6_804B_004033E1EE0D__INCLUDED_

#define _WIN32_WINNT 0x0503

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <atlbase.h>		// Reg

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D1DD796A_5BB1_11D6_804B_004033E1EE0D__INCLUDED_)
