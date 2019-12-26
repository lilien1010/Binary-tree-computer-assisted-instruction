// MyCAI.h : main header file for the MYCAI application
//

#if !defined(AFX_MYCAI_H__134EC613_FD51_4ADC_9F52_128050616B14__INCLUDED_)
#define AFX_MYCAI_H__134EC613_FD51_4ADC_9F52_128050616B14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyCAIApp:
// See MyCAI.cpp for the implementation of this class
//

class CMyCAIApp : public CWinApp
{
public:
	CMyCAIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCAIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyCAIApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCAI_H__134EC613_FD51_4ADC_9F52_128050616B14__INCLUDED_)
