// MyCAIDoc.cpp : implementation of the CMyCAIDoc class
//

#include "stdafx.h"
#include "MyCAI.h"

#include "MyCAIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCAIDoc

IMPLEMENT_DYNCREATE(CMyCAIDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyCAIDoc, CDocument)
	//{{AFX_MSG_MAP(CMyCAIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCAIDoc construction/destruction

CMyCAIDoc::CMyCAIDoc()
{
	// TODO: add one-time construction code here

}

CMyCAIDoc::~CMyCAIDoc()
{
}

BOOL CMyCAIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyCAIDoc serialization

void CMyCAIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyCAIDoc diagnostics

#ifdef _DEBUG
void CMyCAIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyCAIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCAIDoc commands
