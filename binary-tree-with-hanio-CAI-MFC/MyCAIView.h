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
typedef struct tagWIDGETINFO {
	int x;				// x coordinate of widget's upper left corner
	int y;				// y coordinate of widget's upper left corner
	int width;			// width of widget
	int height;			// height of widget
	Color color;			// The widget's color
} WIDGETINFO;


typedef struct tagSTEPINFO {
	int num;			
	int src;
	int des;
} STEPINFO;


class CMyCAIView : public CScrollView
{
protected: // create from serialization only
	CMyCAIView();
	DECLARE_DYNCREATE(CMyCAIView)
public:
/***********汉诺塔所用**************************/
	WIDGETINFO m_Floor[3] ;		//三个底盘
	int m_FloorTop[3] ;		//三个盘子的可放顶部

	STEPINFO m_NowStep;		//当前移动步骤
	UINT m_TimeId;			//计时器ID

	WIDGETINFO m_Stick[3];		//三个棍子

	WIDGETINFO m_Plate[6];		//最大允许六个移动盘

	UINT m_HanoiNum ;		//实际盘子数量

	BOOL m_bShowState;		//移动状态，标记暂停

	UINT m_StepNum;			//记录从某个棍子到另一个棍子的移动像素个数
	
	UINT m_PlateDir;		//盘子的移动方向

	BOOL m_bHanoiRunning;		//标识汉诺塔演示是否在运行

	CWinThread * m_pHanoiThread;		//汉诺塔移动线程指针
	
	BOOL DrawWidget(WIDGETINFO *,CDC *pDC);	//绘制由WIDGETINFO指针指定的方块（盘子。棍子等）

	void InitPlate();			//每次开始演示之前的初始化

	void MoveHanoiPlate();			//根据计时器来按像素移动盘子

	void StartMyTimer();			//开始汉诺塔移动计时器，同时暂停计算线程

	void KillMyTimer();			//停止汉诺塔计时器，同时恢复计算线程
/************下面是画树所用**********/
	TreeNode * m_pDrawTree;			//当前要绘制的树

	TreeNode * m_pOrderTree;		//遍历时所需要的

	float m_rate;				//绘制动画的比率

	float m_Xtmp;				//绘制遍历树的结果，记录当前绘制在那个坐标 
	float m_Ytmp;
	
	CMyTreeDlg *m_pTreeDlg;			//指向绘制树的对话框指针

	CDC *m_pDC;				//暂时未用		
	BOOL m_bTreeTraversed;		//标识汉诺塔演示是否在运行
	BOOL m_bTreeRunning;			//表示树是否在演示
	void DrawTree(TreeNode * Tree,CDC *pDC);	//绘制TreeNode指针指定的树	
	void DrawTreeOrder(CDC * );	//根据计时器来动态演示遍历的情况

	void MoveTreeOrderNode();	//在计时器中运行，动画显示动态遍历顺序
	void ResetTreeOrderNode(TreeNode ** ThisTree,int dis,int NodeNum);
	int CaculateGgradient(float  xp,float  yp,float  xc,float  yc,float * arccos,float * arcsin);


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
	afx_msg void OnButtonStartHanoi();
	afx_msg void OnUpdateButtonHanoi( CCmdUI *pCmdUI);
	afx_msg void OnButtonStop();
	afx_msg void OnButtonSuspend();
//	afx_msg void OnUpdateButtonSuspend();
// Implementation
public:


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
