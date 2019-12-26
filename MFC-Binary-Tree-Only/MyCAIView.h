// MyCAIView.h : interface of the CMyCAIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCAIVIEW_H__B6EF8F41_FC0A_42D6_8879_45DBE48F38AA__INCLUDED_)
#define AFX_MYCAIVIEW_H__B6EF8F41_FC0A_42D6_8879_45DBE48F38AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MainFrm.h"
#include "MyCAIDoc.h"
#include "MyTreeDlg.h"

#include "stdafx.h"




class CMyCAIView : public CScrollView
{
protected: // create from serialization only
	CMyCAIView();
	DECLARE_DYNCREATE(CMyCAIView)
public:
	void StartMyTimer();			//��ʼ��ʱ����
	int	m_TimeId  ;
	void KillMyTimer();			//ֹͣ����ʱ��
/************�����ǻ�������**********/
	TreeNode * m_pDrawTree;			//��ǰҪ���Ƶ���

	TreeNode * m_pOrderTree;		//����ʱ����Ҫ��

	float m_rate;				//���ƶ����ƶ�����

	float m_Xtmp;				//���Ʊ������Ľ������¼��ǰ�������Ǹ�����
	
	float m_Ytmp;
	
	CMyTreeDlg *m_pTreeDlg;			//ָ��������ĶԻ���ָ��

	CDC *m_pDC;				//��ʱδ��
	
	BOOL m_bTreeTraversed;			//��ʶ�Ƿ������ɣ�ÿ�δ򿪼�ʱ��������Ϊ0

	BOOL m_bTreeFinding;			//��ʾ�����ڲ���
	Color m_LineColor;
	BOOL m_bTreeRunning;			//��ʾ���Ƿ�����ʾ

	void DrawTree(TreeNode * Tree,CDC *pDC);//����TreeNodeָ��ָ������
	
	void DrawTreeOrder(CDC * );		//���ݼ�ʱ������̬��ʾ���������
	
	void MoveTreeOrderNode();		//�ڼ�ʱ�������У�������ʾ��̬����˳��
						
						//�ڽ�������Ľ���ŵ�����
	void ResetTreeOrderNode(TreeNode ** ThisTree,int dis,int NodeNum);

	int CaculateGgradient(float  xp,float  yp,float  xc,float  yc,float * arccos,float * arcsin);//��������ֱ�ӵĽǶ�ֵ


// Attributes
public:
	CMyCAIDoc* GetDocument();		//�õ��ļ�ָ��
	CMainFrame * GetMainFrame();		//�õ��Ŀ�ܵ�ָ��

	void UpdateScroll();			//������ͼ���ڵĹ�����
	void ShowInfo(CString & info);		//�����������ַ�����ʾ����


	GdiplusStartupInput m_gdiplusStartupInput;	//gdi+ȫ�ֱ���
	ULONG_PTR m_pGdiToken;		
 
//	afx_msg void OnUpdateButtonSuspend();
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCAIView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

//	afx_msg void OnUpdateButtonSuspend();
// Implementation
public:
	int m_DrawedNode;


	virtual ~CMyCAIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyCAIView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowtree();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyCAIView.cpp
inline CMyCAIDoc* CMyCAIView::GetDocument()
   { return (CMyCAIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCAIVIEW_H__B6EF8F41_FC0A_42D6_8879_45DBE48F38AA__INCLUDED_)
