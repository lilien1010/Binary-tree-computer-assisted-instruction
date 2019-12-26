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
	void StartMyTimer();			//开始计时器，
	int	m_TimeId  ;
	void KillMyTimer();			//停止塔计时器
/************下面是画树所用**********/
	TreeNode * m_pDrawTree;			//当前要绘制的树

	TreeNode * m_pOrderTree;		//遍历时所需要的

	float m_rate;				//绘制动画移动速率

	float m_Xtmp;				//绘制遍历树的结果，记录当前绘制在那个坐标
	
	float m_Ytmp;
	
	CMyTreeDlg *m_pTreeDlg;			//指向绘制树的对话框指针

	CDC *m_pDC;				//暂时未用
	
	BOOL m_bTreeTraversed;			//标识是否遍历完成，每次打开计时器就重置为0

	BOOL m_bTreeFinding;			//表示树是在查找
	Color m_LineColor;
	BOOL m_bTreeRunning;			//表示树是否在演示

	void DrawTree(TreeNode * Tree,CDC *pDC);//绘制TreeNode指针指定的树
	
	void DrawTreeOrder(CDC * );		//根据计时器来动态演示遍历的情况
	
	void MoveTreeOrderNode();		//在计时器中运行，动画显示动态遍历顺序
						
						//在将遍历后的结果放到顶部
	void ResetTreeOrderNode(TreeNode ** ThisTree,int dis,int NodeNum);

	int CaculateGgradient(float  xp,float  yp,float  xc,float  yc,float * arccos,float * arcsin);//计算两点直接的角度值


// Attributes
public:
	CMyCAIDoc* GetDocument();		//得到文件指针
	CMainFrame * GetMainFrame();		//得到的框架的指针

	void UpdateScroll();			//更新试图窗口的滚动条
	void ShowInfo(CString & info);		//将传进来的字符串提示出来


	GdiplusStartupInput m_gdiplusStartupInput;	//gdi+全局变量
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
