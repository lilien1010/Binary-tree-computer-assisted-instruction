// MyCAIView.cpp : implementation of the CMyCAIView class
//

#include "stdafx.h"
#include "MyCAI.h"

#include "MyCAIDoc.h"
#include "MyCAIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCAIView

UINT StartShowHanoi(LPVOID LPARAM );

void Hanoi(int n , int x,int y , int z ,CMyCAIView * pMyView);
IMPLEMENT_DYNCREATE(CMyCAIView, CScrollView)

BEGIN_MESSAGE_MAP(CMyCAIView, CScrollView)
	//{{AFX_MSG_MAP(CMyCAIView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(IDM_SHOWTREE, OnShowtree)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)


//	ON_UPDATE_COMMAND_UI(IDC_BUTTON_SUSPEND,OnUpdateButtonSuspend)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCAIView construction/destruction

CMyCAIView::CMyCAIView()
{
	m_TimeId = 1 ;
	m_pDC = 0;
	m_bTreeRunning = 0;
	m_pDrawTree = 0;
	m_pTreeDlg = 0;
	m_pOrderTree = 0 ;
	m_rate =0.0;
	m_bTreeTraversed = 0; 
	m_DrawedNode = 0;
	m_bTreeFinding = 0;

	m_LineColor.SetFromCOLORREF(RGB(0,125,250));
	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);

}

CMyCAIView::~CMyCAIView()
{
}

BOOL CMyCAIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyCAIView drawing

void CMyCAIView::OnDraw(CDC* pDC)
{
	CMyCAIDoc* pDoc = GetDocument();
	m_pDC = pDC ;
	ASSERT_VALID(pDoc);

	if(m_bTreeRunning)
	{
	
		DrawTree(m_pDrawTree,pDC);

		if( m_bTreeTraversed   && m_pTreeDlg->m_pVisitList && *(m_pTreeDlg->m_pVisitList))
		{
				DrawTreeOrder(pDC);	
		}
	}

}

void CMyCAIView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT,CSize(1360,742));

}

/////////////////////////////////////////////////////////////////////////////
// CMyCAIView printing

BOOL CMyCAIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyCAIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyCAIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyCAIView diagnostics

#ifdef _DEBUG
void CMyCAIView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMyCAIView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMyCAIDoc* CMyCAIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCAIDoc)));
	return (CMyCAIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCAIView message handlers
CMainFrame * CMyCAIView::GetMainFrame()
{
	CMainFrame  * pFrame = (CMainFrame *)AfxGetMainWnd();
	return pFrame;
}

//��ʼ��ʱ��
void CMyCAIView::StartMyTimer()
{
	m_DrawedNode = 0;
	m_LineColor.SetFromCOLORREF(RGB(250,20,5));
	m_bTreeTraversed = 0;
 	m_TimeId = SetTimer(m_TimeId,10,NULL);
	
}

//��ֹ��ʱ��
void CMyCAIView::KillMyTimer()
{

 	KillTimer(m_TimeId);
	BYTE R = m_LineColor.GetR();
	BYTE G = m_LineColor.GetG();
	BYTE B = m_LineColor.GetB();
	if(m_bTreeRunning)
	{
		m_bTreeFinding = 0;
		m_LineColor.SetFromCOLORREF(RGB(B,G,R));
	}

}


int CMyCAIView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	this-> ShowScrollBar(   SB_BOTH   );
	return 0;
}

//��ʱ�����ᶯ���ӹ���
void CMyCAIView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default	
	CView::OnTimer(nIDEvent);

	if(m_bTreeRunning)
	{
		MoveTreeOrderNode();
	}

}


void CMyCAIView::ShowInfo(CString &info)
{
	MessageBox(info);
}

void CMyCAIView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

	Invalidate();
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);

}

void CMyCAIView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	Invalidate();
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);

}

BOOL CMyCAIView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CScrollView::OnEraseBkgnd(pDC);
}

BOOL CMyCAIView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
		Invalidate();
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMyCAIView::UpdateScroll()
{
	if(m_bTreeRunning && m_pTreeDlg )
	{	
		int Hor = (int)pow(2,m_pTreeDlg->m_Height) * 15 ;
		int Vel = (m_pTreeDlg->m_Height )* 85;
		SetScrollSizes( MM_TEXT,CSize(Hor,Vel));
	}
}

//�ü�ʱ�������Ƶĺ�ŵ�����Ӱᶯ


//���¶�������ʾ��ť
void CMyCAIView::OnShowtree() 
{
	// TODO: Add your command handler code here
	if(m_pTreeDlg != NULL)
	{
		//����Ѿ��������ˣ���ֻԭλ����ʾ
		m_pTreeDlg->ShowWindow(SW_SHOWNOACTIVATE);
		return ;
	}

	m_pTreeDlg = new CMyTreeDlg;
 
	m_pTreeDlg->Create(IDD_DIALOG_TREE,NULL);

	m_pTreeDlg->ShowWindow(SW_SHOW);
	//ÿ��ʼһ���µ���ʾ�������û��������������
	m_pDrawTree = NULL;
	m_pOrderTree = NULL ;
	m_rate =0.0;
	m_bTreeTraversed = 0; 
	m_bTreeRunning = 1;
}

//�ݹ����һ��������
void CMyCAIView::DrawTree(TreeNode *Tree,CDC *pDC)
{
	Font myFont(L"Arial", 12);	//��ʾ�ַ�������	
	CString str = "";	
	float px,py;			//�ֱ߱�ʾ���ڵ�͵�ǰ�ڵ㣨���ӣ���x y
	float arcsin = 0.0f,arccos =  0.0f;	//���ڵ㵽�ӽڵ�����ߺ�x����Ƕ� ��sinֵ
	float M =  0.0f;			//�߶γ���
	float radius = 10.0f;
	
	SolidBrush newBrush(Color(255, 0,0,0));
	Graphics g(pDC->m_hDC);
	if( Tree == NULL || m_pDC == NULL)
	{
		return ;
	}
	
	PointF origin((REAL)(Tree->data.x - 10+2.5), (REAL)(Tree->data.y - 10+ 1.5));
 	newBrush.SetColor(Color(255,255,0,255));


	//��ʾ������Ϣ��
	if(Tree->parent == 0)
	{
		str.Format("�����ܽڵ��� = %d\r\n���ĸ߶� = %d \r\n����Ҷ���� = %d  \0",m_pTreeDlg->m_NodeNum,m_pTreeDlg->m_Height,m_pTreeDlg->m_LeafNum);	
		g.DrawString( str.AllocSysString(),-1,&myFont,PointF(5.0f,6.0f),&newBrush);	
	}
	

	//����һ����ϵ���׽ڵ���߶�
	if( Tree->parent  )
	{
		//����Ĳ�����Ϊ�˷�ֹ���Ƶ��߶��ڽڵ�Բ֮��
		{
			//���㵱ǰ�ڵ�͸��ڵ����ߵĽǶ�ֵ
			CaculateGgradient(Tree->parent->data.x,Tree->parent->data.y,
				Tree->data.x,Tree->data.y, &arccos,&arcsin);

			py = Tree->parent->data.y - radius * arcsin ;
			px = Tree->parent->data.x - radius * arccos ;
		}
		Pen newPen(Color(255,0,125,250),2);	//�����߶εı�ˢ����ɫ
		g.DrawLine(&newPen,(REAL)(Tree->data.x),(REAL)(Tree->data.y),(REAL)(px),(REAL)(py));
	}

	//�����ڵ�data�������ݻ��ƽڵ�
	newBrush.SetColor( Tree->data.color );
	Rect ellipseRect(Tree->data.x -10,Tree->data.y -10, 20, 20);
	g.FillEllipse(&newBrush, ellipseRect );

	//�ڵ�д���ַ�����ɫ
	newBrush.SetColor(Color(255, 255,0,255));

	//�ڽڵ�д���ַ�
	WCHAR W = Tree->data.word;
	g.DrawString( &W,1,&myFont,origin,&newBrush);

	
	g.ReleaseHDC(pDC->m_hDC);
	DrawTree(Tree->lchild,pDC);
	DrawTree(Tree->rchild,pDC);
}

//���Ʊ��������нڵ㣬��������
void CMyCAIView::DrawTreeOrder(CDC *pDC)		       
{
	Font myFont(L"Arial", 12);		//��ʾ�ַ�������		

	float arcsin = 0.0f,arccos =  0.0f;	//���ڵ㵽�ӽڵ�����ߺ�x����Ƕ� ��sinֵ
	float M =  0.0f;			//�߶γ���
	float radius = 9.0f;			//�뾶
	float Xi, Yi,Xj,Yj;			//�߶κ�����Բ�Ľ������꣨j=�� i=�ӣ�

	SolidBrush PieBrush(Color(255, 0,0,0));	//�ڵ�԰����ɫ��ˢ
	int StartNode = 0;			//��ʼ���Ƶı����ڵ���
	TreeNode * ThisTree = 0;

	Pen newPen(m_LineColor,4);	//�����߶εı�ˢ
	Graphics g(pDC->m_hDC);
	
 	//���߹��Ľڵ�ȫ�����Ƴ���
	for( StartNode = 0 ; StartNode <= m_DrawedNode  ; StartNode ++)
	{
		ThisTree = m_pTreeDlg->m_pVisitList[StartNode];
		if(!ThisTree) return;
		PointF origin( (REAL)( ThisTree->data.x - 10+2.5), (REAL)(ThisTree->data.y - 10+ 1.5));  

		//��newBrush��һ���뾶Ϊ10��Բ ��ɫ���Խڵ�����		
		{
			PieBrush.SetColor( ThisTree->data.color );
			Rect ellipseRect(ThisTree->data.x -10,ThisTree->data.y -10, 20, 20);
			g.FillEllipse(&PieBrush, ellipseRect );

			//�ڽڵ���д�Ͻڵ��ַ�,��ɫ�Ǻ�ɫ
			PieBrush.SetColor(Color(255, 0,250,0));
			WCHAR W = ThisTree->data.word;
			g.DrawString( &W,1,&myFont,origin,&PieBrush);
		}
				//�����ǰ�����һ���ڵ�Ͳ���Ҫ������
		if(ThisTree->lchild)
		{	
				//���㵱ǰ�ڵ�͸��ڵ����ߵĽǶ�ֵ
			CaculateGgradient(ThisTree->data.x,ThisTree->data.y,
				ThisTree->lchild->data.x,ThisTree->lchild->data.y, &arccos,&arcsin);

			Xj = ThisTree->data.x - radius * arccos ;
			Yj = ThisTree->data.y - radius * arcsin ;

			Xi = ThisTree->lchild->data.x + radius * arccos ;
			Yi = ThisTree->lchild->data.y + radius * arcsin ;
		}
		//ֻ���Ѿ��߹��ĵ�����������
		if( StartNode < m_DrawedNode )
		{		
			g.DrawLine(&newPen,(REAL)(Xj ),(REAL)(Yj),(REAL)(Xi),(REAL)( Yi ));
		}
	}

	//����һ����ϵ���ӽڵ���߶�
	if( ThisTree->lchild  )
	{
		g.DrawLine(&newPen,(REAL)(Xj ),(REAL)(Yj ),(REAL)(m_Xtmp),(m_Ytmp));
	}

	g.ReleaseHDC(pDC->m_hDC);
}

//ͨ����ʱ������һ���ļ������б�ʷ���ĳ��ȣ� ���� DrawTreeOrder �γɶ���
void CMyCAIView::MoveTreeOrderNode()
{
	float arcsin = 0.0f,arccos =  0.0f;	//���ڵ㵽�ӽڵ�����ߺ�x����Ƕ� ��sinֵ
	float M =  0.0f;			//�߶γ���
	float radius = 10.0f;			//�뾶
	float Xi, Yi,Xj,Yj;			//�߶κ�����Բ�Ľ������꣨j=�� i=�ӣ�
	TreeNode * ThisTree = 0 ;
	CClientDC dc(this);
	Graphics g(dc.m_hDC);

	ThisTree = m_pTreeDlg->m_pVisitList[m_DrawedNode];

	if( ThisTree == NULL )
	{
		KillMyTimer();
		return ;
	}


	if( ThisTree ->lchild == NULL)	//�����ǰ�ڵ��Ǳ��������һ����Ч�ڵ�
	{
		m_bTreeTraversed = 1;

		if(  m_rate <=1.00 && m_bTreeFinding == 0 )
			ResetTreeOrderNode(m_pTreeDlg->m_pVisitList,40,m_pTreeDlg->m_NodeNum);
		else
		{
			KillMyTimer();
		}
		InvalidateRect(NULL);

		return ;
	}

	//����һ����ϵ���ӽڵ���߶�
	if( ThisTree->lchild  )
	{
		//������㵱ǰ���Ƶ��Ľڵ�����һ���ڵ�Ҫ�ߵ�����
		{
			//���㵱ǰ�ڵ�͸��ڵ����ߵĽǶ�ֵ
			CaculateGgradient(ThisTree->data.x,ThisTree->data.y,
				ThisTree->lchild->data.x,ThisTree->lchild->data.y, &arccos,&arcsin);

			Xj = ThisTree->data.x - radius * arccos ;
			Yj = ThisTree->data.y - radius * arcsin ;

			Xi = ThisTree->lchild->data.x + radius * arccos ;
			Yi = ThisTree->lchild->data.y + radius * arcsin ;

			m_Xtmp = Xj + m_rate *  (Xi - Xj);
			m_Ytmp = Yj + m_rate *  (Yi - Yj);
		}

	}

	m_rate  +=0.05f;				//ÿ0.03��Ҫ���Ƶ�����������һ���ڵ㷽������5%�ĳ���

	if(m_rate >= 1.1)
	{
		m_rate = 0.0 ;				//����һ���ڵ�֮������
		m_DrawedNode ++;		//��Ŀ��������һ���ڵ�
	}

	DrawTreeOrder(&dc);

}

void CMyCAIView::ResetTreeOrderNode(TreeNode ** ThisTree,int dis,int NodeNum)
{
	float arcsin = 0.0f,arccos =  0.0f;	//���ڵ㵽�ӽڵ�����ߺ�x����Ƕ� ��sinֵ
	float radius = 10.0f;			//�뾶
	float Xnow, Ynow,Xdes,Ydes;		//���������Ŀ������
	int pos = 0 ;

	if( !( ThisTree && (*ThisTree ) ))
	{
		m_rate = 0.0 ;
		m_bTreeTraversed = 0;
		return ;
	}

	for(pos = 0 ; pos < NodeNum; pos ++)
	{
		Xdes = 20 + dis * pos;
		Ydes = (m_pTreeDlg->m_Height ) * 80 ;

		Xnow = ThisTree[pos]->data.x ;
		Ynow = ThisTree[pos]->data.y ;
		if( (Xdes - Xnow) >=-0.01 && (Xdes - Xnow) <= 0.01)	continue;
		CaculateGgradient(Xdes,Ydes,Xnow,Ynow, &arccos,&arcsin);

		ThisTree[pos]->data.x += m_rate *  fabs(Xnow - Xdes) * arccos;
		ThisTree[pos]->data.y += m_rate *  fabs(Ydes - Ynow) * arcsin;
	}
	m_rate  +=0.025f;				//ÿ0.03��Ҫ���Ƶ�����������һ���ڵ㷽������2.5%�ĳ���

	if(m_rate >= 1.05)
	{
		return ;
	}

}
//��������֮���б�� ���ص���arcsin��arccos
int CMyCAIView::CaculateGgradient(float xp, float yp, float xc, float yc, float *arccos, float *arcsin)
{
	float M= 0.0 ;
	if(!(arcsin && arccos))	return 0;
	M = sqrt( pow((xp-xc),2) + pow((yp - yc),2) );
	*arccos = (xp -xc) / M;	
	*arcsin = (yp -yc) / M;
	return 1;
}


