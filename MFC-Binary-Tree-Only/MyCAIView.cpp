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

//开始计时器
void CMyCAIView::StartMyTimer()
{
	m_DrawedNode = 0;
	m_LineColor.SetFromCOLORREF(RGB(250,20,5));
	m_bTreeTraversed = 0;
 	m_TimeId = SetTimer(m_TimeId,10,NULL);
	
}

//终止计时器
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

//计时器，搬动盘子过程
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

//用计时器来控制的汉诺塔盘子搬动


//按下二叉树演示按钮
void CMyCAIView::OnShowtree() 
{
	// TODO: Add your command handler code here
	if(m_pTreeDlg != NULL)
	{
		//如果已经创建好了，就只原位置显示
		m_pTreeDlg->ShowWindow(SW_SHOWNOACTIVATE);
		return ;
	}

	m_pTreeDlg = new CMyTreeDlg;
 
	m_pTreeDlg->Create(IDD_DIALOG_TREE,NULL);

	m_pTreeDlg->ShowWindow(SW_SHOW);
	//每开始一次新的演示，就重置绘制树的相关数据
	m_pDrawTree = NULL;
	m_pOrderTree = NULL ;
	m_rate =0.0;
	m_bTreeTraversed = 0; 
	m_bTreeRunning = 1;
}

//递归绘制一个二叉树
void CMyCAIView::DrawTree(TreeNode *Tree,CDC *pDC)
{
	Font myFont(L"Arial", 12);	//显示字符的字体	
	CString str = "";	
	float px,py;			//分边表示父节点和当前节点（孩子）的x y
	float arcsin = 0.0f,arccos =  0.0f;	//父节点到子节点的连线和x方向角度 的sin值
	float M =  0.0f;			//线段长度
	float radius = 10.0f;
	
	SolidBrush newBrush(Color(255, 0,0,0));
	Graphics g(pDC->m_hDC);
	if( Tree == NULL || m_pDC == NULL)
	{
		return ;
	}
	
	PointF origin((REAL)(Tree->data.x - 10+2.5), (REAL)(Tree->data.y - 10+ 1.5));
 	newBrush.SetColor(Color(255,255,0,255));


	//显示树的信息，
	if(Tree->parent == 0)
	{
		str.Format("树的总节点数 = %d\r\n树的高度 = %d \r\n树的叶子数 = %d  \0",m_pTreeDlg->m_NodeNum,m_pTreeDlg->m_Height,m_pTreeDlg->m_LeafNum);	
		g.DrawString( str.AllocSysString(),-1,&myFont,PointF(5.0f,6.0f),&newBrush);	
	}
	

	//绘制一根联系父亲节点的线段
	if( Tree->parent  )
	{
		//下面的步骤是为了防止绘制的线段在节点圆之上
		{
			//计算当前节点和父节点连线的角度值
			CaculateGgradient(Tree->parent->data.x,Tree->parent->data.y,
				Tree->data.x,Tree->data.y, &arccos,&arcsin);

			py = Tree->parent->data.y - radius * arcsin ;
			px = Tree->parent->data.x - radius * arccos ;
		}
		Pen newPen(Color(255,0,125,250),2);	//绘制线段的笔刷，蓝色
		g.DrawLine(&newPen,(REAL)(Tree->data.x),(REAL)(Tree->data.y),(REAL)(px),(REAL)(py));
	}

	//用树节点data里面数据绘制节点
	newBrush.SetColor( Tree->data.color );
	Rect ellipseRect(Tree->data.x -10,Tree->data.y -10, 20, 20);
	g.FillEllipse(&newBrush, ellipseRect );

	//节点写上字符的颜色
	newBrush.SetColor(Color(255, 255,0,255));

	//在节点写上字符
	WCHAR W = Tree->data.word;
	g.DrawString( &W,1,&myFont,origin,&newBrush);

	
	g.ReleaseHDC(pDC->m_hDC);
	DrawTree(Tree->lchild,pDC);
	DrawTree(Tree->rchild,pDC);
}

//绘制遍历的所有节点，类是链表
void CMyCAIView::DrawTreeOrder(CDC *pDC)		       
{
	Font myFont(L"Arial", 12);		//显示字符的字体		

	float arcsin = 0.0f,arccos =  0.0f;	//父节点到子节点的连线和x方向角度 的sin值
	float M =  0.0f;			//线段长度
	float radius = 9.0f;			//半径
	float Xi, Yi,Xj,Yj;			//线段和两个圆的交点坐标（j=父 i=子）

	SolidBrush PieBrush(Color(255, 0,0,0));	//节点园的颜色画刷
	int StartNode = 0;			//开始绘制的遍历节点编号
	TreeNode * ThisTree = 0;

	Pen newPen(m_LineColor,4);	//绘制线段的笔刷
	Graphics g(pDC->m_hDC);
	
 	//将走过的节点全部绘制出来
	for( StartNode = 0 ; StartNode <= m_DrawedNode  ; StartNode ++)
	{
		ThisTree = m_pTreeDlg->m_pVisitList[StartNode];
		if(!ThisTree) return;
		PointF origin( (REAL)( ThisTree->data.x - 10+2.5), (REAL)(ThisTree->data.y - 10+ 1.5));  

		//用newBrush画一个半径为10的圆 颜色来自节点数据		
		{
			PieBrush.SetColor( ThisTree->data.color );
			Rect ellipseRect(ThisTree->data.x -10,ThisTree->data.y -10, 20, 20);
			g.FillEllipse(&PieBrush, ellipseRect );

			//在节点上写上节点字符,颜色是红色
			PieBrush.SetColor(Color(255, 0,250,0));
			WCHAR W = ThisTree->data.word;
			g.DrawString( &W,1,&myFont,origin,&PieBrush);
		}
				//如果当前是最后一个节点就不需要向后计算
		if(ThisTree->lchild)
		{	
				//计算当前节点和父节点连线的角度值
			CaculateGgradient(ThisTree->data.x,ThisTree->data.y,
				ThisTree->lchild->data.x,ThisTree->lchild->data.y, &arccos,&arcsin);

			Xj = ThisTree->data.x - radius * arccos ;
			Yj = ThisTree->data.y - radius * arcsin ;

			Xi = ThisTree->lchild->data.x + radius * arccos ;
			Yi = ThisTree->lchild->data.y + radius * arcsin ;
		}
		//只把已经走过的点用线连起来
		if( StartNode < m_DrawedNode )
		{		
			g.DrawLine(&newPen,(REAL)(Xj ),(REAL)(Yj),(REAL)(Xi),(REAL)( Yi ));
		}
	}

	//绘制一根联系孩子节点的线段
	if( ThisTree->lchild  )
	{
		g.DrawLine(&newPen,(REAL)(Xj ),(REAL)(Yj ),(REAL)(m_Xtmp),(m_Ytmp));
	}

	g.ReleaseHDC(pDC->m_hDC);
}

//通过计时器按照一定的间隔增长斜率方向的长度， 调用 DrawTreeOrder 形成动画
void CMyCAIView::MoveTreeOrderNode()
{
	float arcsin = 0.0f,arccos =  0.0f;	//父节点到子节点的连线和x方向角度 的sin值
	float M =  0.0f;			//线段长度
	float radius = 10.0f;			//半径
	float Xi, Yi,Xj,Yj;			//线段和两个圆的交点坐标（j=父 i=子）
	TreeNode * ThisTree = 0 ;
	CClientDC dc(this);
	Graphics g(dc.m_hDC);

	ThisTree = m_pTreeDlg->m_pVisitList[m_DrawedNode];

	if( ThisTree == NULL )
	{
		KillMyTimer();
		return ;
	}


	if( ThisTree ->lchild == NULL)	//如果当前节点是遍历的最后一个有效节点
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

	//绘制一根联系孩子节点的线段
	if( ThisTree->lchild  )
	{
		//下面计算当前绘制到的节点向下一个节点要走的坐标
		{
			//计算当前节点和父节点连线的角度值
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

	m_rate  +=0.05f;				//每0.03秒要绘制到的坐标在下一个节点方向增长5%的长度

	if(m_rate >= 1.1)
	{
		m_rate = 0.0 ;				//到达一个节点之后，重置
		m_DrawedNode ++;		//将目标移向下一个节点
	}

	DrawTreeOrder(&dc);

}

void CMyCAIView::ResetTreeOrderNode(TreeNode ** ThisTree,int dis,int NodeNum)
{
	float arcsin = 0.0f,arccos =  0.0f;	//父节点到子节点的连线和x方向角度 的sin值
	float radius = 10.0f;			//半径
	float Xnow, Ynow,Xdes,Ydes;		//现在坐标和目的坐标
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
	m_rate  +=0.025f;				//每0.03秒要绘制到的坐标在下一个节点方向增长2.5%的长度

	if(m_rate >= 1.05)
	{
		return ;
	}

}
//计算两点之间的斜率 返回的是arcsin和arccos
int CMyCAIView::CaculateGgradient(float xp, float yp, float xc, float yc, float *arccos, float *arcsin)
{
	float M= 0.0 ;
	if(!(arcsin && arccos))	return 0;
	M = sqrt( pow((xp-xc),2) + pow((yp - yc),2) );
	*arccos = (xp -xc) / M;	
	*arcsin = (yp -yc) / M;
	return 1;
}


