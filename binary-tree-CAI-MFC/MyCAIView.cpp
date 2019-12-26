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
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)

	ON_COMMAND(IDC_BUTTON_HANOI,   OnButtonStartHanoi) 
        ON_UPDATE_COMMAND_UI(IDC_BUTTON_HANOI,   OnUpdateButtonHanoi) 
	
	ON_COMMAND(IDC_BUTTON_SUSPEND,OnButtonSuspend)
	ON_COMMAND(IDC_BUTTON_STOP,OnButtonStop)
//	ON_UPDATE_COMMAND_UI(IDC_BUTTON_SUSPEND,OnUpdateButtonSuspend)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCAIView construction/destruction

CMyCAIView::CMyCAIView()
{
	// TODO: add construction code here
	int i = 0 ;
	m_bShowState = 0 ;  //0 便是可以暂停
	m_HanoiNum  = 0;
	m_pHanoiThread = NULL;
	m_PlateDir = 0;
	m_TimeId = 1 ;
	m_bHanoiRunning = 0;
	m_pDC = 0;
//TREE NEED
	m_bTreeRunning = 0;
	m_pDrawTree = 0;
	m_pTreeDlg = 0;
	m_pOrderTree = 0 ;
	m_rate =0.0;
	m_bTreeTraversed = 0; 
	 for( i = 0 ; i < 3 ; i++)
	 {
		m_Floor[i].height = 20;
		m_Floor[i].width = 120;
		m_Floor[i].y = 250 ;
		m_Floor[i].color = Color(0,0,0);
		m_Floor[i].x = 160 + i * 180;

	 }

	 for( i = 0 ; i < 3 ; i++)
	 {
		m_Stick[i].height = 150;
		m_Stick[i].width = 10;
		m_Stick[i].x = m_Floor[i].x + 60 - 5 ;
		m_Stick[i].color = Color(60,60,40);
		m_Stick[i].y = 100;
	 }


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
	int i;
/**/	if(m_bHanoiRunning)
	{
		for(  i = 0 ; i < 3  ; i++)
		 { 
			DrawWidget(&m_Floor[i],pDC);
			DrawWidget(&m_Stick[i],pDC);
		 }
		for(  i = 0 ; i < m_HanoiNum  ; i++)
		 { 
			DrawWidget(&m_Plate[i],pDC);
		 }
	}
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

//开始计时器（盘子开始移动），暂停汉诺塔计算线程
void CMyCAIView::StartMyTimer()
{
 	m_TimeId = SetTimer(m_TimeId,30,NULL);
	if (m_bHanoiRunning)
		m_pHanoiThread->SuspendThread();	
}

//终止计时器（盘子停止移动），汉诺塔计算线程计算得到下一个移动步骤
void CMyCAIView::KillMyTimer()
{
 	KillTimer(m_TimeId);
	if (m_bHanoiRunning)
		m_pHanoiThread->ResumeThread();
}

//在传进来的pDC上面画一个盘子
BOOL CMyCAIView::DrawWidget(WIDGETINFO * pWidget ,CDC *pDC)
{	
	if( m_pDC == NULL || pWidget == NULL )
		return FALSE;

	Graphics g(pDC->m_hDC);

 	Pen pen( pWidget->color );
	
	SolidBrush  newBrush( pWidget->color); 

	g.FillRectangle(&newBrush, pWidget->x, pWidget-> y, pWidget-> width, pWidget->height) ;

	g.ReleaseHDC(m_pDC->m_hDC);
	return TRUE;
}

//按下“开始演示”，得到输入的盘子数
void CMyCAIView::OnButtonStartHanoi()
{
	m_HanoiNum = GetMainFrame()->m_wndDlgBar.GetDlgItemInt(IDC_EDIT_HANOI);

	if( m_HanoiNum > 6 || m_HanoiNum < 1 )m_HanoiNum  = 6;

	InitPlate();

	m_FloorTop[0] = 230 - ( m_HanoiNum  ) * 20 ;
	

	SetScrollSizes( MM_TEXT,CSize(1000,400));
	

	InvalidateRect(NULL);

	m_pHanoiThread = ::AfxBeginThread(::StartShowHanoi,this,THREAD_PRIORITY_NORMAL,1024*1024*5);
/*	
*/
	InvalidateRect(NULL);
}

//暂停搬动盘子，让线程暂停，计时器终止，恢复的话就是开启线程，打开计时器
void CMyCAIView::OnButtonSuspend()
{

	if(!m_pHanoiThread)
		return ;

	if(m_bShowState == 0 && m_bHanoiRunning)
	{	
		KillTimer(m_TimeId);
		m_pHanoiThread->SuspendThread();
		(GetMainFrame()->m_wndDlgBar.GetDlgItem(IDC_BUTTON_SUSPEND) )->SetWindowText("恢复");
		m_bShowState = 1;
	}
	else if(m_bShowState == 1 && m_bHanoiRunning)
	{
 		m_TimeId = SetTimer(m_TimeId,10,NULL);
		m_pHanoiThread->ResumeThread();	
		(GetMainFrame()->m_wndDlgBar.GetDlgItem(IDC_BUTTON_SUSPEND))->SetWindowText("暂停");
		m_bShowState = 0;
	}


}
//按下“终止”，关系汉诺塔线程，停止计时器
void CMyCAIView::OnButtonStop()
{
	if( m_bHanoiRunning == 1)
	{
		CloseHandle(m_pHanoiThread->m_hThread);
		m_pHanoiThread = 0;
		KillTimer(m_TimeId);
		m_bHanoiRunning = 0;
		InvalidateRect(NULL);
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
	if( m_bHanoiRunning)
	{
		MoveHanoiPlate();
	}
	if(m_bTreeRunning)
	{
		MoveTreeOrderNode();
	}

}


void CMyCAIView::ShowInfo(CString &info)
{
	MessageBox(info);
}

//运算汉诺塔线程
UINT StartShowHanoi(LPVOID lparam)
{
	CMyCAIView * pMyView = (CMyCAIView * )lparam;

	pMyView->m_bHanoiRunning = 1;	
	Hanoi(pMyView->m_HanoiNum,1,2, 3, pMyView);

	pMyView->ShowInfo((CString)"所有盘子都办完啦啦啦啦！！！！");
	pMyView->m_bHanoiRunning = 0;
 
	return 1;
}


void Hanoi(int n , int x,int y , int z ,CMyCAIView * pMyView)
{

	if( n == 1)
	{
		pMyView->m_NowStep.num = n;
		pMyView->m_NowStep.src = x;
		pMyView->m_NowStep.des = z;
		pMyView->StartMyTimer();
		return ;
	}
	else
	{
	Hanoi(n -1 ,x,z,y,pMyView);

		pMyView->m_NowStep.num =n;
		pMyView->m_NowStep.src = x;
		pMyView->m_NowStep.des = z;	//将编号为n的盘子从x号柱子上移动到z上面
	pMyView->StartMyTimer();

	Hanoi(n -1 ,y,x,z,pMyView);	
	}
}


//对盘子和记录盘子的运动数据重新赋值。在按下开始演示 就要初始化
void CMyCAIView::InitPlate()
{
	 for(int i = 0 ; i < 6 ; i++)
	 {
		m_Plate[i].height = 10;
		m_Plate[i].width = 100  - i * 14;

		m_Plate[i].x = m_Floor[0].x + 60 - m_Plate[i].width / 2 ;
		m_Plate[i].color = Color(50 + i* 40, - i * 60,255);
		m_Plate[i].y = 230 - i * 20 ;

		if(i<3)	
			m_FloorTop[i] = 230 ;
	 }
	m_bShowState = 0 ;		//0 便是可以暂停
	m_pHanoiThread = NULL;		//hanoi线程的结束后置为空
	m_PlateDir = 0;			//当前盘子移动的方向
	m_TimeId = 1 ;			//计时器ID
	m_bHanoiRunning = 0;		//判断hanoi是否在运行
	m_bTreeRunning = 0;		//判断hanoi是否在运行
}

//在盘子在移动的过程中 开始演示按钮无效 变灰
void CMyCAIView::OnUpdateButtonHanoi(CCmdUI *pCmdUI)
{
	if( m_bHanoiRunning == 0)
	{
		pCmdUI->Enable(TRUE); 

	}
	else if( m_bHanoiRunning == 1)
	{
		pCmdUI->Enable(FALSE); 
	}

}



void CMyCAIView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	InvalidateRect(NULL);
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);

}

void CMyCAIView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	InvalidateRect(NULL);
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);

}



void CMyCAIView::UpdateScroll()
{
	if(m_bTreeRunning && m_pTreeDlg )
	{	
		int Hor = (int)pow(2,m_pTreeDlg->m_Height) * 15 ;
		int Vel = (m_pTreeDlg->m_Height - 1)* 85;
		SetScrollSizes( MM_TEXT,CSize(Hor,Vel));
	}
}

//用计时器来控制的汉诺塔盘子搬动
void CMyCAIView::MoveHanoiPlate()
{
	WIDGETINFO * pWidget = &m_Plate[m_HanoiNum - m_NowStep.num  ];		
	if( 0 == m_PlateDir)	//向上弹出
	{
		pWidget->y -=6;
	
		InvalidateRect(CRect(pWidget->x,pWidget->y ,pWidget->x + pWidget->width+10 ,pWidget->y + pWidget->height +10 ));	
	
		if(pWidget->y <= 90)
		{
			m_FloorTop[m_NowStep.src - 1] += 20;
			m_PlateDir = 1;
			m_StepNum = 0;
		}

	}
	else if( m_PlateDir == 1)	//平行移到到目的地
	{
	
		m_StepNum ++;	
	 
		pWidget->x += 4*( m_NowStep.des - m_NowStep.src);
		
		InvalidateRect(CRect(pWidget->x - 10,pWidget->y - 4,pWidget->x + pWidget->width +  10,pWidget->y + pWidget->height +4 ));
		
		if(m_StepNum >= 45)
		{
			m_StepNum  = 0;
			m_PlateDir = 2;
		}

	}
	else if ( m_PlateDir == 2)	//向下压入
	{

		pWidget->y +=6;
				 
		InvalidateRect(CRect(pWidget->x,pWidget->y - 10,pWidget->x + pWidget->width + 4,pWidget->y + pWidget->height + 2 ));
				
		if( pWidget->y >= m_FloorTop[m_NowStep.des - 1] )
		{
				m_FloorTop[m_NowStep.des -1 ] -= 20;
				m_PlateDir = 0;
				KillMyTimer();
		}
	}
}

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
	OnButtonStop();		//关闭汉诺塔演示

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

	if( Tree == NULL || m_pDC == NULL)
	{
		return ;
	}
	
	PointF origin((REAL)(Tree->data.x - 10+2.5), (REAL)(Tree->data.y - 10+ 1.5));
 	newBrush.SetColor(Color(255,255,0,255));
	Graphics g(pDC->m_hDC);

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


void CMyCAIView::DrawTreeOrder(CDC *pDC)		       
{
	Font myFont(L"Arial", 12);		//显示字符的字体		

	float arcsin = 0.0f,arccos =  0.0f;	//父节点到子节点的连线和x方向角度 的sin值
	float M =  0.0f;			//线段长度
	float radius = 10.0f;			//半径
	float Xi, Yi,Xj,Yj;			//线段和两个圆的交点坐标（j=父 i=子）

	SolidBrush PieBrush(Color(255, 0,0,0));	//节点园的颜色画刷
	int StartNode = 0;			//开始绘制的遍历节点编号
	TreeNode * ThisTree = 0;

	Pen newPen(Color(255,255,50,10),4);	//绘制线段的笔刷
	Graphics g(pDC->m_hDC);
	
 	//将走过的节点全部绘制出来
	for( StartNode = 0 ; StartNode <= m_pTreeDlg->m_VisitNum  ; StartNode ++)
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
			PieBrush.SetColor(Color(255, 255,0,255));
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
		if( StartNode < m_pTreeDlg->m_VisitNum )
		{		
			g.DrawLine(&newPen,(REAL)(Xj),(REAL)(Yj),(REAL)(Xi),(REAL)( Yi ));
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

	ThisTree = m_pTreeDlg->m_pVisitList[m_pTreeDlg->m_VisitNum];

	if( ThisTree == NULL )
	{
		m_rate = 0.0 ;
		m_bTreeTraversed = 0;
		KillTimer(m_TimeId);
		return ;
	}

	//字符在圆圈里面的位置
	PointF origin((REAL)(ThisTree->data.x - 10+2.5), (REAL)(ThisTree->data.y - 10+ 1.5));
	

	if( ThisTree ->lchild == NULL)	//如果当前节点是遍历的最后一个有效节点，那么在绘制完成节点之后就可以结束了
	{
		m_bTreeTraversed = 1;
		ResetTreeOrderNode(m_pTreeDlg->m_pVisitList,60,m_pTreeDlg->m_NodeNum);
		if(m_pTreeDlg->m_pVisitList[0]->data.y <= 10.5)	
			KillTimer(m_TimeId);
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
		m_pTreeDlg->m_VisitNum ++;		//将目标移向下一个节点
	}

	DrawTreeOrder(&dc);

}

void CMyCAIView::ResetTreeOrderNode(TreeNode ** ThisTree,int des,int NodeNum)
{
	float arcsin = 0.0f,arccos =  0.0f;	//父节点到子节点的连线和x方向角度 的sin值
	float radius = 10.0f;			//半径
	float Xnow, Ynow,Xdes,Ydes;			//线段和两个圆的交点坐标（j=父 i=子）
	int pos = 0 ;

	if( ThisTree == NULL && *ThisTree )
	{
		m_rate = 0.0 ;
		m_bTreeTraversed = 0;
		return ;
	}
	if(	m_rate  >= 1.05f ) 	m_rate   = 0.0f;

	for(pos = 0 ; pos < NodeNum; pos ++)
	{
		Xdes = 180 + 60 * pos;
		Ydes = 10;

		Xnow = ThisTree[pos]->data.x ;
		Ynow = ThisTree[pos]->data.y ;

		CaculateGgradient(Xdes,Ydes,Xnow,Ynow, &arccos,&arcsin);


		ThisTree[pos]->data.x += m_rate *  fabs(Xnow - Xdes) * arccos;
		ThisTree[pos]->data.y += m_rate *  fabs(Ydes - Ynow) * arcsin;
	}
	m_rate  +=0.025f;				//每0.03秒要绘制到的坐标在下一个节点方向增长5%的长度

	if(m_rate >= 1.05)
	{
		m_rate = 0.0 ;				//到达一个节点之后，重置
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

BOOL CMyCAIView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CScrollView::OnEraseBkgnd(pDC);
}
