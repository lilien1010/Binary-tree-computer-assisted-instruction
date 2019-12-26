// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__5F940B07_B7FC_412A_BE43_D0AA6723DFAB__INCLUDED_)
#define AFX_STDAFX_H__5F940B07_B7FC_412A_BE43_D0AA6723DFAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxole.h>
#include <afxtempl.h>

//初始化一下com口

#ifndef ULONG_PTR
#define ULONG_PTR unsigned long*
#include "GdiPlus.h"
using namespace Gdiplus;
#endif
#pragma comment(lib,"gdiplus.lib")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5F940B07_B7FC_412A_BE43_D0AA6723DFAB__INCLUDED_)
