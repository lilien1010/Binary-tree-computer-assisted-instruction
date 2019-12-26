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
/***********��ŵ������**************************/
	WIDGETINFO m_Floor[3] ;		//��������
	int m_FloorTop[3] ;		//�������ӵĿɷŶ���

	STEPINFO m_NowStep;		//��ǰ�ƶ�����
	UINT m_TimeId;			//��ʱ��ID

	WIDGETINFO m_Stick[3];		//��������

	WIDGETINFO m_Plate[6];		//������������ƶ���

	UINT m_HanoiNum ;		//ʵ����������

	BOOL m_bShowState;		//�ƶ�״̬�������ͣ

	UINT m_StepNum;			//��¼��ĳ�����ӵ���һ�����ӵ��ƶ����ظ���
	
	UINT m_PlateDir;		//���ӵ��ƶ�����

	BOOL m_bHanoiRunning;		//��ʶ��ŵ����ʾ�Ƿ�������

	CWinThread * m_pHanoiThread;		//��ŵ���ƶ��߳�ָ��
	
	BOOL DrawWidget(WIDGETINFO *,CDC *pDC);	//������WIDGETINFOָ��ָ���ķ��飨���ӡ����ӵȣ�

	void InitPlate();			//ÿ�ο�ʼ��ʾ֮ǰ�ĳ�ʼ��

	void MoveHanoiPlate();			//���ݼ�ʱ�����������ƶ�����

	void StartMyTimer();			//��ʼ��ŵ���ƶ���ʱ����ͬʱ��ͣ�����߳�

	void KillMyTimer();			//ֹͣ��ŵ����ʱ����ͬʱ�ָ������߳�
/************�����ǻ�������**********/
	TreeNode * m_pDrawTree;			//��ǰҪ���Ƶ���

	TreeNode * m_pOrderTree;		//����ʱ����Ҫ��

	float m_rate;				//���ƶ����ı���

	float m_Xtmp;				//���Ʊ������Ľ������¼��ǰ�������Ǹ����� 
	float m_Ytmp;
	
	CMyTreeDlg *m_pTreeDlg;			//ָ��������ĶԻ���ָ��

	CDC *m_pDC;				//��ʱδ��		
	BOOL m_bTreeTraversed;		//��ʶ��ŵ����ʾ�Ƿ�������
	BOOL m_bTreeRunning;			//��ʾ���Ƿ�����ʾ
	void DrawTree(TreeNode * Tree,CDC *pDC);	//����TreeNodeָ��ָ������	
	void DrawTreeOrder(CDC * );	//���ݼ�ʱ������̬��ʾ���������

	void MoveTreeOrderNode();	//�ڼ�ʱ�������У�������ʾ��̬����˳��
	void ResetTreeOrderNode(TreeNode ** ThisTree,int dis,int NodeNum);
	int CaculateGgradient(float  xp,float  yp,float  xc,float  yc,float * arccos,float * arcsin);


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
