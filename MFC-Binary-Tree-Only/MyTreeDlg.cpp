// MyTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyCAI.h"
#include "MyTreeDlg.h"
#include "MyCAIView.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTreeDlg dialog


CMyTreeDlg::CMyTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyTreeDlg)
	m_StrTree = _T("");
	m_StrInsertPos = _T("");
	m_StrInsertNew = _T("");
	m_StrFindNode = _T("");
	m_StrDeleteNode = _T("");
	//}}AFX_DATA_INIT
	  m_Height = 0 ;	
	  m_LeafNum = 0;
	  m_NowTmp = 0;
	  m_pTree = 0;
	  m_NodeNum = 0;
	  m_pVisitList = 0;
	  m_VisitNum = 0;

	  m_pfLegalFinder = 0;
}


void CMyTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyTreeDlg)
	DDX_Control(pDX, IDC_COMBO_LOOR, m_ComLoor);
	DDX_Text(pDX, IDC_EDIT_TREESTRING, m_StrTree);
	DDX_Text(pDX, IDC_EDIT_INSERTPOS, m_StrInsertPos);
	DDX_Text(pDX, IDC_EDIT_INSERTNODE, m_StrInsertNew);
	DDX_Text(pDX, IDC_EDIT_FINDNODE, m_StrFindNode);
	DDX_Text(pDX, IDC_EDIT_DELETENODE, m_StrDeleteNode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CMyTreeDlg)
	ON_BN_CLICKED(IDC_BUTTON_CREATETREE, OnButtonCreatetree)
	ON_BN_CLICKED(IDC_BUTTON_PTRORDER, OnButtonPreorder)
	ON_BN_CLICKED(IDC_BUTTON_INORDER, OnButtonInorder)
	ON_BN_CLICKED(IDC_BUTTON_POSORDER, OnButtonPosorder)
	ON_BN_CLICKED(IDC_BUTTON_INSERTNODE, OnButtonInsertnode)
	ON_BN_CLICKED(IDC_BUTTON_FINDNODE, OnButtonFindnode)
	ON_BN_CLICKED(IDC_BUTTON_DELETENODE, OnButtonDeletenode)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_FINDLEAF,OnButtonIdentityLeaf)
	ON_BN_CLICKED(IDC_BUTTON_ERASE_ORDER,OnButtonEraseOrder)
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE,OnButtonOpenFile)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeDlg message handlers


BOOL CMyTreeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ComLoor.InsertString(0,"������");
	m_ComLoor.InsertString(0,"������");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

TreeNode * CMyTreeDlg::CreateTree( char ** str)
{
	char t = 0;
	TreeNode * newTree = 0;
	if(!( str && *str) ) return 0 ;
	
	t =	** str;
	if ( t == 0)	return 0;
	(*str) ++ ;
	if( t == '.')	return 0;

	newTree = (TreeNode *)malloc( sizeof(TreeNode) );
	if( !newTree ) return 0;
	newTree->data.word = t;
	newTree->data.color.SetFromCOLORREF(RGB(0,0,0));
	newTree->parent = 0;
	newTree->lchild = CreateTree(str);
	if(  newTree->lchild ) 	newTree->lchild->parent = newTree;
		
	newTree->rchild = CreateTree(str);
	if(  newTree->rchild ) 	newTree->rchild->parent = newTree;
	
	return newTree;
}

void CMyTreeDlg::PreOrder(TreeNode * Tree,int (CMyTreeDlg::*func)(TreeNode * Tree))
{
	if( ! Tree ) return ;
	
	if ( !( this->*func)(Tree) )
		return;
	PreOrder(Tree->lchild,func);
	PreOrder(Tree->rchild,func);
}

void CMyTreeDlg::InOrder(TreeNode * Tree,int (CMyTreeDlg::*func)(TreeNode * Tree))
{
	if( ! Tree ) return ;
	
	InOrder(Tree->lchild,func);	
	if ( !( this->*func)(Tree)  ) 
		return;
	InOrder(Tree->rchild,func);
}

void CMyTreeDlg::PostOrder(TreeNode * Tree,int (CMyTreeDlg::*func)(TreeNode * Tree))
{
	if( ! Tree ) return ;
	
	PostOrder(Tree->lchild,func);
	PostOrder(Tree->rchild,func);	
	if ( !( this->*func)(Tree)  ) 
		return;
}

/*�����в���Ԫ��*/
TreeNode * CMyTreeDlg::FindNode(TreeNode * Tree , char ch,int (CMyTreeDlg::*func)(TreeNode * Tree) )
{
	TreeNode * Finded = 0;

	if( ! Tree ) return 0;	
	
	if(func != NULL)
	{	
		(this->*func)(Tree);
	}
	
	if ( ch == Tree->data.word )
	{

		return Tree;
	}


	
	Finded  = FindNode(Tree->lchild,ch,func);
	
	if(Finded)	return Finded;
	
	Finded  = FindNode(Tree->rchild,ch,func);
	
	if(Finded)	return Finded;

	return 0 ;
}
/*��������Ҷ�ӽڵ�*/
int CMyTreeDlg::GetLeafs(TreeNode * Tree)
{
	if( ! Tree )
		return 0;
	
	if( Tree -> lchild == 0 && Tree -> rchild == 0 )
		return 1;
	else	
		return GetLeafs(Tree -> lchild ) + GetLeafs(Tree -> rchild) ;
}
/*�������ĸ߶�*/
int CMyTreeDlg::GetHeight(TreeNode * Tree)
{
	int lh= 0 ,rh = 0;

	if( Tree == 0 )
		return 0;

	lh = GetHeight(Tree -> lchild );
	rh = GetHeight(Tree -> rchild);
	
	return lh   >= rh ? ( lh+ 1 ) : ( rh + 1);
}
/* 
�����нڵ�Ԫ��Ϊpos��λ�õ�
(loor����������������)
��������elem 
*/
TreeNode * CMyTreeDlg::InsertTree(TreeNode * Tree , char pos,char loor,char elem)
{
	TreeNode * FindTree = 0;
	TreeNode * NewTree = 0;

	if(!( Tree &&  (loor == 'l' || loor == 'r' ) ))
		return 0 ;

	FindTree = FindNode(Tree,pos,NULL);
	NewTree = (TreeNode*)malloc( sizeof(TreeNode) );
	memset(NewTree,0,sizeof(TreeNode));
	if(! ( FindTree && NewTree ))
		return 0 ;
	NewTree->data.word = elem ;

	NewTree->parent = FindTree;

	if( loor == 'l')
	{
		if(FindTree->lchild)
			FindTree->lchild->parent = NewTree;
		NewTree->lchild = FindTree->lchild;
		FindTree->lchild = NewTree;
		return NewTree;
	}
	if( loor == 'r')
	{
		if(FindTree->rchild)
			FindTree->rchild->parent = NewTree;
		NewTree->rchild = FindTree->rchild;
		FindTree->rchild = NewTree;
		return NewTree;	
	}

	return 0 ;
}

int CMyTreeDlg::DeleteNode(TreeNode * Tree)
{
	if(!Tree)
		return 0 ;
		
	if( Tree->parent && Tree->parent->lchild == Tree  )
		Tree->parent->lchild = 0;
		
	if( Tree->parent && Tree->parent->rchild == Tree  )
		Tree->parent->rchild = 0;

	DeleteNode( Tree->lchild);
	
	DeleteNode( Tree->rchild);
	
	free(Tree);
		Tree = 0;
	return 1;
}

void CMyTreeDlg::NodeCount(TreeNode * Tree,int * numNode)
{
	if( ! Tree ) 
		return ;
	* numNode = * numNode +1;
 
	NodeCount(Tree->lchild,numNode);

	NodeCount(Tree->rchild,numNode);
}

int CMyTreeDlg::FreeTree(TreeNode ** Tree,char pos)	/*ɾ������ĳ���ڵ��������е�����*/
{
	TreeNode * FindTree = 0;

	if(! (Tree && *Tree))
		return 0 ;

	FindTree = FindNode(*Tree,pos,NULL);

	if(FindTree == * Tree)
		*Tree = 0;
	return DeleteNode(FindTree);
}

int CMyTreeDlg::DestoryTree(TreeNode ** Tree)	/*ɾ������ĳ���ڵ��������е�����*/
{
	TreeNode * FindTree = 0;

	if(! (Tree && *Tree))
		return 0 ;

	FindTree = * Tree;
	*Tree = 0;

	return DeleteNode(FindTree);
}

//�ݹ����ڵ�����
void CMyTreeDlg::SetNodeCoord(TreeNode * Tree,int dis)
{
	if(!Tree ) return;
	//��ǰ�ڵ��Ǹ��ڵ�
	if(Tree->parent == 0)
	{

		Tree->data.x = dis/2;
	
		if( m_Height > 0 && m_Height <= 6)
		{	
			Tree->data.x = 480;	//��ǰ��Ļ����������6�����
			dis = 480;
		}
		else dis /= 2;

		Tree->data.y = 29;
	}
	else	//�Ǹ��׽ڵ�
	{
		//�����ǰ�ڵ��Ǹ��׵�����
		if( Tree->parent->lchild == Tree  )
		{
			Tree->data.x = Tree->parent->data.x - dis ;
		}
		//�����ǰ�ڵ��Ǹ��׵��Һ���
		if( Tree->parent->rchild == Tree  )
		{
			Tree->data.x = Tree->parent->data.x + dis ;
		}

		Tree->data.y = Tree->parent->data.y + 80;

	}
	SetNodeCoord( Tree->lchild,dis / 2);
	SetNodeCoord( Tree->rchild,dis / 2);	
}


//�ݹ����ڵ�����
void CMyTreeDlg::ModifyNodeCoord(TreeNode * Tree,int dir,int dis)
{
	if(!Tree && dis == 0) return;
	//ˮƽ����x����
	if( dir == 1)
	{
		Tree->data.x += dis;
	}
	//��ֱ����y����
	if( dir == -1)	
	{
		Tree->data.y += dis;
	}
	else return;
	ModifyNodeCoord( Tree->lchild,dir, dis);
	ModifyNodeCoord( Tree->rchild,dir, dis);	
}

//dis �������ڵ�ļ��


void CMyTreeDlg::OnButtonCreatetree() 
{
	char * str;
	UpdateData();
	if(m_StrTree.GetLength() < 1 || m_StrTree[0] == '.')
	{//1234#$Q..T....A..&H..D..MFGH...G..67..8.9....
		
		m_StrTree = "1234...5..67..8.9..";
	//1234...5..67..8.9..
		//12344..R..QR..T..5W..E..67D..B..8A..9..
	//1234XV..E..VV..E..MRV..E..QR..T..5WHV..d..BV..v..e2#..E..h3..m..67D#x..L..#2..^..M(V..$..]V..@..hVB*../..M*../..EG*../..F*../....8AB(V.E..]..V..
	}
	str = m_StrTree.GetBuffer(100);
	
	if(m_pTree)
		FreeTree(&m_pTree,m_pTree->data.word);

	OnButtonEraseOrder();

	m_pTree = CreateTree(&str);

	if(!m_pTree)	return;

	ReCalTreeInfo(m_pTree);

	if( m_pVisitList )	//�������еĽڵ�ָ��
	{
		DestoryTree(m_pVisitList);
		free(m_pVisitList);
		m_pVisitList = 0;
	}

	m_pVisitList  = (TreeNode**)malloc( sizeof(TreeNode *) * m_NodeNum );

	memset( m_pVisitList,0,sizeof(TreeNode *) * m_NodeNum);

	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_pDrawTree = m_pTree;
	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->InvalidateRect(NULL);

	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_bTreeRunning = 1;
	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->UpdateScroll();
}


void CMyTreeDlg::OnButtonPreorder() 
{

	if(!m_pTree || ! m_pVisitList)
		return;
	int (CMyTreeDlg::*pfunc)(TreeNode *);	//����һ���Ͳ�������һ���ĺ���ָ��
	
	pfunc =& CMyTreeDlg::CreateVisitList;	//ָ��ָ��Ҫ���õĺ���

	OnButtonEraseOrder();

	PreOrder(m_pTree,pfunc);		//��������ָ�뿴����������


	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->StartMyTimer();
}

void CMyTreeDlg::OnButtonInorder() 
{
	if(!m_pTree || ! m_pVisitList)
		return;
	int (CMyTreeDlg::*pfunc)(TreeNode *);	//����һ���Ͳ�������һ���ĺ���ָ��
	
	pfunc =& CMyTreeDlg::CreateVisitList;	//ָ��ָ��Ҫ���õĺ���
	OnButtonEraseOrder();

	InOrder(m_pTree,pfunc);		//��������ָ�뿴����������

	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->StartMyTimer();
}

void CMyTreeDlg::OnButtonPosorder() 
{
	if(!m_pTree || ! m_pVisitList)
		return;

	int (CMyTreeDlg::*pfunc)(TreeNode *);	//����һ���Ͳ�������һ���ĺ���ָ��
	
	pfunc =& CMyTreeDlg::CreateVisitList;	//ָ��ָ��Ҫ���õĺ���

	OnButtonEraseOrder();

	
	PostOrder(m_pTree,pfunc);		//��������ָ�뿴����������
	
	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->StartMyTimer();
	
}

void CMyTreeDlg::OnButtonIdentityLeaf()
{

	TreeNode * FindedNode = 0;

	int (CMyTreeDlg::*func)(TreeNode *);

	OnButtonEraseOrder();		

	func =& CMyTreeDlg::CreateVisitList;

	m_pfLegalFinder = & CMyTreeDlg::FindLeafs;



	if( m_pTree )
	{
		FindedNode =FindNode(m_pTree,'.',func);	
		
 		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_bTreeFinding = 1;

		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->StartMyTimer();

		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_LineColor.SetFromCOLORREF(RGB(150,200,15));
			
		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_pDrawTree = m_pTree;	
		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->InvalidateRect(NULL);
	}
}

//��ձ�������
void CMyTreeDlg::OnButtonEraseOrder()
{
	if( m_pVisitList )	//����Ѵ�����ڵ㣬�ػ���
	{
		DestoryTree(m_pVisitList);
		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->InvalidateRect(NULL);
		
		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->KillMyTimer();
	}
	m_pfLegalFinder = 0;
	m_VisitNum = 0;
}


void CMyTreeDlg::OnButtonInsertnode() 
{
	int sel = 0;
	UpdateData();
	TreeNode * InsertedNode = 0;
	CString Loor = "";
	sel = m_ComLoor.GetCurSel();
	if(sel < 0)	return;

	OnButtonEraseOrder();

	m_ComLoor.GetLBText(m_ComLoor.GetCurSel(),Loor);

	if(Loor == "������"  )
		Loor = "l";
	else if	(Loor == "������"  )
		Loor = "r";

	if(m_pTree && Loor != "" && m_StrInsertPos!= "" && m_StrInsertNew!= "")
	{
		InsertedNode = InsertTree(m_pTree,m_StrInsertPos[0],Loor[0],m_StrInsertNew[0]);
		if( InsertedNode  == 0)
		{
			MessageBox("û���ҵ�Ҫ����Ľڵ㣬����ʧ�ܣ�");
			return;
		}
		//���¼������нڵ�����
		
		ReCalTreeInfo(m_pTree);
		//���·���ڵ����ָ��ռ�
		m_pVisitList  = (TreeNode**)realloc( m_pVisitList,sizeof(TreeNode *) * m_NodeNum );
		memset( m_pVisitList,0,sizeof(TreeNode *) * m_NodeNum);


		InsertedNode->data.color.SetFromCOLORREF(RGB(100,80,255));

		//������ͼ���Ա�����ʾ���нڵ㣻
		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_pDrawTree = m_pTree;		
		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->UpdateScroll();
		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->InvalidateRect(NULL);
	}
	
}


void CMyTreeDlg::OnButtonFindnode() 
{
	UpdateData();
	TreeNode * FindedNode = 0;
	CDC * pDC = 0;
	int (CMyTreeDlg::*func)(TreeNode *);
		
	CClientDC dc(((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView()));
	Graphics g(dc.m_hDC);

	func =& CMyTreeDlg::CreateVisitList;

	OnButtonEraseOrder();

	if(m_pTree && m_StrFindNode!= "")
	{
		FindedNode =FindNode(m_pTree,m_StrFindNode[0],func);	
		if(FindedNode)
		{
		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_bTreeFinding = 1;

		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->StartMyTimer();
		
		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_LineColor.SetFromCOLORREF(RGB(5,150,240));
		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_pDrawTree = m_pTree;
		
		((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->InvalidateRect(NULL);
		}
		else
		{	OnButtonEraseOrder();
			MessageBox("û���ҵ��ڵ�");
		}

	}
}

//ɾ���ڵ�
void CMyTreeDlg::OnButtonDeletenode() 
{
	UpdateData();
	OnButtonEraseOrder();	
	if(m_pTree && m_StrDeleteNode!= "" )
	{
		if(FreeTree(&m_pTree,m_StrDeleteNode[0]) )
		{
			ReCalTreeInfo(m_pTree);
			((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_pDrawTree = m_pTree;
			((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->InvalidateRect(NULL);
		}
		else
		{	OnButtonEraseOrder();
			MessageBox("û���ҵ�Ҫɾ���Ľڵ�ڵ�");
		}
	}
	
}
//���ļ�����ȡ�����������ַ���
void CMyTreeDlg::OnButtonOpenFile()
{
	CFileDialog fDlg(TRUE,".txt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, this);

	CString FilePathName = "";
	CStdioFile MyFile;
	if(fDlg.DoModal()==IDOK)
		FilePathName=fDlg.GetPathName();

	if(! MyFile.Open(FilePathName,CFile::modeRead ) )return;
	
	MyFile.ReadString(m_StrTree);
	
	UpdateData(FALSE);
}

//�رյ�ʱ����һЩ�ͷŹ���
void CMyTreeDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(m_pTree)
		DestoryTree(&m_pTree);

	if( m_pVisitList )	//�������еĽڵ�ָ��
	{
		DestoryTree(m_pVisitList);
		free(m_pVisitList);
		m_pVisitList = 0;
	}
	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_pDrawTree  = NULL;	
	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_pTreeDlg = NULL;
	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_bTreeRunning = 0;
	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->m_bTreeTraversed = 0;	
	((CMyCAIView *)((CMainFrame *)GetParent())->GetActiveView())->Invalidate();


	CDialog::OnClose();
}
//�������б�����ʱ����һ����������
int CMyTreeDlg::CreateVisitList(TreeNode *Tree)
{

	if(!Tree)
		return 0;

	if(m_pfLegalFinder)
	{
		if( !(this->*m_pfLegalFinder)(Tree) )
			return 0;
	
	}
	m_pVisitList[m_VisitNum] = (TreeNode *)malloc(sizeof(TreeNode));
	
	memset( m_pVisitList[m_VisitNum] ,0,sizeof(TreeNode) );

	m_pVisitList[m_VisitNum]->data = Tree->data;

	m_pVisitList[m_VisitNum]->data.color.SetFromCOLORREF(RGB(25,45,23));	
	
	if(m_VisitNum == 0)
	{
		m_pVisitList[m_VisitNum]->parent = 0;
	
	}
	else
	{
		m_pVisitList[m_VisitNum]->parent = m_pVisitList[m_VisitNum-1];
		m_pVisitList[m_VisitNum - 1]->lchild = m_pVisitList[m_VisitNum];
	}

	m_VisitNum++;
	return 1;
}


/**/
 

//���¼������������Ϣ
void CMyTreeDlg::ReCalTreeInfo(TreeNode *Tree)
{
	if(!Tree)	return ;
	m_Height = GetHeight(m_pTree);

	m_LeafNum = GetLeafs(m_pTree);
	m_NodeNum = 0 ;
	NodeCount(m_pTree,&m_NodeNum);
	SetNodeCoord( m_pTree ,pow(2,m_Height) * 15);

}

//��ϢԤ���������Լ��Ļس�����ȥ������esc���˳������
BOOL CMyTreeDlg::PreTranslateMessage(MSG * pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam  == VK_ESCAPE)
		{
			return TRUE;
		}	
		if(pMsg->wParam  == VK_RETURN)
		{
			OnButtonCreatetree();
			return TRUE;
		}	
	}
	return CDialog::PreTranslateMessage(pMsg);
}

//�ж��Ƿ�Ϊ��ָ�룬�ó�Ա����ָ��ָ��m_pfLegalFinder���������������ʱ����Ϊ�ж����ݣ�
//ֻ�Ǳ�����ʱ��m_pfLegalFinderΪ��
int CMyTreeDlg::FindLeafs(TreeNode *Tree)
{
	if(  Tree->lchild == 0 && Tree->rchild == 0 )
		return 1;
	return 0;
}
