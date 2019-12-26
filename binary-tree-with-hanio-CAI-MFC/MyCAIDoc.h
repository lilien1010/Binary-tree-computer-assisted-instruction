// MyCAIDoc.h : interface of the CMyCAIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCAIDOC_H__D0B6CEC1_D37B_47A1_B9BA_2FFD5F1C5B80__INCLUDED_)
#define AFX_MYCAIDOC_H__D0B6CEC1_D37B_47A1_B9BA_2FFD5F1C5B80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyCAIDoc : public CDocument
{
protected: // create from serialization only
	CMyCAIDoc();
	DECLARE_DYNCREATE(CMyCAIDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCAIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyCAIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyCAIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCAIDOC_H__D0B6CEC1_D37B_47A1_B9BA_2FFD5F1C5B80__INCLUDED_)
