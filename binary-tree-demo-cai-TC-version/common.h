#include "math.h"
#include "stdio.h"
#define NULL 0

/*通用功能函数*/
void delay(int inter);
void MessageBox(char * str);

/*==============树的声明开始=========================*/
typedef struct tagTreeData
{
    float x ; 
    float y ;
    int color;
    char word;
}TreeData;

typedef struct tagTreeNode
{
    TreeData data;
    struct tagTreeNode * lchild;
    struct tagTreeNode * rchild;
    struct tagTreeNode * parent;
}TreeNode;

    /*函数指针：在CreateVisitList中使用，可以得到特定的叶子结点 */  
    TreeNode * m_pTree;     /*当前显示的树*/
    TreeNode ** m_pVisitList;   /*存储遍历节点指针*/

    int m_Height;           /*树的高度*/
    int m_LeafNum;          /*树的叶子数*/
    int  m_NodeNum ;        /*树的节点数*/
    int  m_VisitNum ;       /*已经节点遍历的个数*/
    char    m_StrFileName[100];
    char    m_StrTree[100]={0};     /*当前要新建的树*/    
/*===========函数========/*
    /*新建树*/
    TreeNode * CreateTree( char ** str);    
    /*先序遍历*/
    void PreOrder(TreeNode * Tree,int (*func)(TreeNode * Tree));
    /*中序遍历*/
    void InOrder(TreeNode * Tree,int (*func)(TreeNode * Tree));
    /*后序遍历*/
    void PostOrder(TreeNode * Tree,int (*func)(TreeNode * Tree));
    /*在树中查找元素*/
    TreeNode * FindNode(TreeNode * Tree , char ch,int (*func)(TreeNode * Tree) );
    /*计算树的叶子节点*/
    int GetLeafs(TreeNode * Tree);
    /*计算树的高度*/
    int GetHeight(TreeNode * Tree);
    /* 在树pos的位置的loor子树插入elem  ,返回插入节点的位置 */
    TreeNode * InsertTree(TreeNode * Tree , char pos,char loor,char elem);
    int DeleteNode(TreeNode * Tree);            /*删除某个节点*/
    int DestoryTree(TreeNode ** Tree);          /*销毁树*/
    int FreeTree(TreeNode ** Tree,char pos);        /*删除树中某个节点下面所有的子树*/

    void NodeCount(TreeNode * Tree,int * numNode);      /*统计书中节点个数*/

    int FindLeafs(TreeNode *Tree);              /*判断是否为叶子*/

    void ReCalTreeInfo(TreeNode* Tree);         /*计算树的信息：高度，叶子数*/

    int CreateVisitList(TreeNode * Tree);           /*遍历树的时候*/
            		
    void SetNodeCoord(TreeNode * Tree,int);         /*设置树的坐标*/
    
    int (*m_pfLegalFinder)(TreeNode * Tree);    

     void OnButtonCreatetree();
     void OnButtonPreorder();
     void OnButtonInorder();
     void OnButtonPosorder();
     void OnButtonInsertnode();
     void OnButtonFindnode();
     void OnButtonDeletenode();
     void EraseOrder();
     int OnButtonOpenFile();
     void OnButtonIdentityLeaf();
     void OnButtonExit();
/*===================树声明结束================================*/

/*===================绘图声明开始================================*/

    TreeNode * m_pDrawTree;     /*当前要绘制的树*/
    float m_rate;               /*绘制动画移动速率*/    

    float m_ScreenX;

    float m_ScreenY; 
    int m_TimerSwitch;          /*计时器开关*/  
    int m_LineColor = 2;    
    int m_bTreeFinding = 0; 
    int m_NodeColor = 2;

    TreeNode *m_pDrawTree= NULL;
    
    void StartMyTimer();        /*开始计时器，*/
    void KillMyTimer();         /*停止计时器*/
    void OnDraw();
    void OnTimer() ;
    int m_DrawedNode;
    int m_bTreeTraversed;       /*标识是否遍历完成，每次打开计时器就重置为0*/
    
    void DrawTree(TreeNode * Tree,int LineColor);/*绘制TreeNode指针指定的树*/
    
    void DrawTreeOrder(TreeNode **);    /*根据计时器来动态演示遍历的情况*/
    
    void MoveTreeOrderNode(TreeNode **);    /*在计时器中运行，动画显示动态遍历顺序*/
            			
                        /*在将遍历后的结果放到顶部*/
    void ResetTreeOrderNode(TreeNode ** ThisTree,int dis,int NodeNum);

    int CaculateGgradient(float  xp,float  yp,float  xc,float  yc,float * arccos,float * arcsin);/*计算两点直接的角度值*/

    void DrawLine(int Color,int kd,int x1, int y1, int x2, int y2);
    void DrawString(int Color,int x,int y,char * str);
    void FillEllipse(int Color,int x, int y, int radius,char);
    
/*===================绘图声明结束======================*/

/*===================绘图的操作开始======================*/
void DrawLine(int Color,int kd,int x1, int y1, int x2, int y2)
{
    setcolor(Color);    
    if( kd != 1) kd = 3;    
    setlinestyle(SOLID_LINE,1,kd );
    line(x1,  y1,  x2,  y2);
}
 /*        DEFAULT_FONT   =0   8x8 点阵
        TRIPLEX_FONT   =1   三倍笔划
        SMALL_FONT     =2   小号字体
        SANS_SERIF_FONT=3   无衬线字体
        GOTHIC_FONT    =4   哥特字体
 */
void DrawString(int Color,int x,int y,char * str)
{
    settextstyle( TRIPLEX_FONT , HORIZ_DIR, 3);
    setcolor(Color);
    outtextxy( x,  y, str);
}

void FillEllipse(int Color,int x, int y, int radius,char ch)
{

	char str[20]={0};
    setfillstyle(SOLID_FILL,Color);
    setcolor(Color);
    fillellipse( x,  y,  radius,radius );
            /*节点写上字符的*/
   str[0]=ch;
   DrawString(15 - Color,x -3,y-3,(char *)&str);
}
    
    
void InitDrawData()
{
    m_NodeColor = 2;
    m_pDrawTree = 0;
    m_LineColor = 9;
    m_rate =0.0;
    m_bTreeTraversed = 1; 
    m_DrawedNode = 0;
    m_bTreeFinding = 0;
    m_TimerSwitch = 0;
}

void OnDraw()
{

 	setfillstyle(SOLID_FILL,0);/* 黑色色背景 */
        bar(1,m_ScreenY + 28,640-2,480-2);

  	if(m_pDrawTree == 0)
	{
		setfillstyle(SOLID_FILL,0);/* 黑色抹掉原来的信息 */
		bar(6,69,640-6,85);
	}
        DrawTree(m_pDrawTree,9);
 
	if( m_bTreeTraversed   && m_pVisitList && *(m_pVisitList))
        {
            DrawTreeOrder(m_pVisitList);    
        } 

        /* 画树的区域框*/
        setcolor(2);/* Green色 */
        rectangle(0,61,639,479);
}
/*开始计时器*/
void StartMyTimer()
{
    m_DrawedNode = 0;
    m_bTreeTraversed = 0;
    m_TimerSwitch =1;
    m_rate = 0.0;
    while(m_TimerSwitch)
    {
        OnTimer();
        delay(32);
    }
    
}

/*终止计时器, 修改连线的颜色*/
void KillMyTimer()
{
    m_LineColor ^=0x7f;
    m_TimerSwitch = 0;
    m_bTreeFinding = 0;
    m_bTreeTraversed = 1;
}



/*计时器，搬动盘子过程*/
void OnTimer() 
{
    if( m_pVisitList )
    {
        /*传进去要动态遍历的节点链表*/
        MoveTreeOrderNode(m_pVisitList);
    }

}


/*递归绘制一个二叉树*/
void DrawTree(TreeNode *Tree,int LineColor)
{
    char str[100] = {0};    
    float px,py;            /*分边表示父节点和当前节点（孩子）的x y*/
    float arcsin = 0.0f,arccos =  0.0f; /*父节点到子节点的连线和x方向角度 的sin值*/ 
    float radius =10.0f;
    
    if( Tree == NULL ) return ;
  
    /*显示树的信息，*/
    if(Tree->parent == 0 && m_bTreeTraversed  )
    {
        setfillstyle(SOLID_FILL,0);/* 黑色抹掉原来 */
        bar(6,69,640-6,85);
	sprintf(str,"All Nodes = %d Tree Height=%d Tree LeafNum = %d  \0",m_NodeNum,m_Height,m_LeafNum);
        DrawString( 14,7,75,str);   
    }
    
    /*绘制一根联系父亲节点的线段*/
    if( Tree->parent  )
    {
        /*下面的步骤是为了防止绘制的线段在节点圆之上*/
        {
            /*计算当前节点和父节点连线的角度值*/ 
            CaculateGgradient(Tree->parent->data.x,Tree->parent->data.y,
                Tree->data.x,Tree->data.y, &arccos,&arcsin);

            py = Tree->parent->data.y - radius * arcsin ;
	    px = Tree->parent->data.x - radius * arccos ;
 
	}
        DrawLine(LineColor,1,(int)(Tree->data.x),(int)(Tree->data.y),(int)(px),(int)(py));
    }
    /*用树节点data里面数据绘制节点*/
    FillEllipse(Tree->data.color,Tree->data.x,Tree->data.y,10,Tree->data.word);

    DrawTree(Tree->lchild,LineColor);
    DrawTree(Tree->rchild,LineColor);
}

/*绘制遍历的所有节点，类是链表*/
void DrawTreeOrder(TreeNode **pVisitList)              
{  
    float arcsin = 0.0f,arccos =  0.0f; /*父节点到子节点的连线和x方向角度 的sin值*/
    float radius = 10.0f;            /*半径*/
    float Xi = 0, Yi = 0,Xj =0 ,Yj =0 ;         /*线段和两个圆的交点坐标（j=父 i=子）*/
    TreeNode * ThisTree;
  
    if( m_bTreeTraversed && m_bTreeFinding == 0 )/*绘制完毕就重复画树，得到动态拉直效果*/
    {
	    DrawTree(pVisitList[0],m_LineColor);
	    return;
    }

        ThisTree = pVisitList[m_DrawedNode];
        if(!ThisTree) return;

        /*用newBrush画一个半径为10的圆 颜色来自节点数据     */
        if( m_rate <= 0.15  )
        {
            FillEllipse(ThisTree->data.color,ThisTree->data.x,ThisTree->data.y,10,ThisTree->data.word);

        }
        /*如果当前是最后一个节点就不需要向后计算*/
        if(ThisTree->lchild)
        {	
                /*计算当前节点和父节点连线的角度值*/
            CaculateGgradient(ThisTree->data.x,ThisTree->data.y,
                ThisTree->lchild->data.x,ThisTree->lchild->data.y, &arccos,&arcsin);

            Xj = ThisTree->data.x - radius * arccos ;
            Yj = ThisTree->data.y - radius * arcsin ;

            Xi = ThisTree->lchild->data.x + radius * arccos ;
            Yi = ThisTree->lchild->data.y + radius * arcsin ;
       
 
    /*绘制一根联系已经遍历完的最后一个节点到下一个目标的线段，m_rate自加动态*/
	DrawLine(m_LineColor,3,(int)(Xj ),(int)(Yj ),
            (int)( Xj + m_rate *  (Xi - Xj) ),(int)( Yj + m_rate *  (Yi - Yj)  ));
	 }
	
}

/*通过计时器按照一定的间隔增长斜率方向的长度， 调用 DrawTreeOrder 形成动画*/
void MoveTreeOrderNode(TreeNode **pVisitList)
{
    TreeNode * ThisTree = 0 ;   
    ThisTree = pVisitList[m_DrawedNode];

    if( ThisTree ->lchild == NULL || m_DrawedNode >= m_VisitNum-1 )      /*如果当前节点是遍历的最后一个有效节点*/
    {
        m_bTreeTraversed = 1;
        /*所有已经遍历完的节点按顺序想目的移动,如是查找节点就不要水平排序*/
        if(  m_rate <=1.0 && m_bTreeFinding == 0 )
        {
            ResetTreeOrderNode(pVisitList,30,m_DrawedNode+1);
        }
        else     /*m_rate大于1表示所有节点都到达*/
        {
            KillMyTimer();
	    return;
        }
        /*重新绘制*/
        OnDraw();
        return;
    }  

    m_rate  +=0.015f;           /*每0.03秒要绘制到的坐标在下一个节点方向增长5%的长度*/

    if(m_rate >= 1.015)
    {
        m_rate = 0.0 ;          /*到达一个节点之后，重置*/
        m_DrawedNode ++;        /*将目标移向下一个节点*/
    }
     DrawTreeOrder(pVisitList);   
    /*传进去要动态遍历绘制的链表*/

}

void ResetTreeOrderNode(TreeNode ** ThisTree,int dis,int NodeNum)
{
    float arcsin = 0.0f,arccos =  0.0f; /*父节点到子节点的连线和x方向角度 的sin值*/
    float Xnow, Ynow,Xdes,Ydes;     /*现在坐标和目的坐标*/
    int pos = 0 ;

    if( !( ThisTree && (*ThisTree ) ))
    {
        m_rate = 0.0 ;
        return ;
    }

    if(m_rate >= 1.25)
    {   
        return ;
    }   
    /*将NodeNum个节点的坐标向目的方向增加8%*/
    for(pos = 0 ; pos < NodeNum; pos ++)
    {
        Xdes = 20 + dis * pos;
        Ydes = m_ScreenY + 380 ;

        Xnow = ThisTree[pos]->data.x ;
        Ynow = ThisTree[pos]->data.y ;

        CaculateGgradient(Xdes,Ydes,Xnow,Ynow, &arccos,&arcsin);

        ThisTree[pos]->data.x += m_rate *  (float)fabs(Xnow - Xdes) * arccos;
        ThisTree[pos]->data.y += m_rate *  (float)fabs(Ydes - Ynow) * arcsin;
    }

    m_rate  +=0.08f;        /*每0.01秒要绘制到的坐标在下一个节点方向增长8%的长度*/
}


/*计算两点之间的斜率 返回的是arcsin和arccos*/
int CaculateGgradient(float px, float py, float cx, float cy, float *arccos, float *arcsin)
{

	float M= 0.0 ;
	double Q = 0.0;
	if(!(arcsin && arccos)) return 0;

    Q = (double)( (px-cx)*(px-cx) + (py - cy)*(py - cy));
/*
    if(( Q < 1 || px ==320.0 ) && m_bTreeFinding)
    {
		sprintf(&str,"%f %f %f %f : %f %f %f", px,py,cx,cy,(px-cx)*(px-cx),(py - cy)*(py - cy),Q);
		MessageBox(&str);
		getch(); 
	    *arccos=0;
	    *arcsin=0;
	    return 1;
    }
*/
    M = (float)sqrt(Q);

    *arccos = (px -cx) / M; 
    *arcsin = (py -cy) / M;

    return 1;
}
/*=================================================绘图操作结束======================*/




/*===================================树操作开始======================================*/
void InitTreeData()
{
    memset(m_StrTree,0,100);

      m_Height = 0 ;    
      m_LeafNum = 0;
      m_pTree = NULL;
      m_NodeNum = 0;
      m_pVisitList = NULL;
      m_VisitNum = 0;
      m_pfLegalFinder = NULL;

}


TreeNode * CreateTree( char ** str)
{
    char t = 0;
    TreeNode * newTree = 0;
    if(!( str && *str) ) return 0 ;

    t = ** str;
    if ( t == 0)    return 0;
    (*str) ++ ;
    if( t == '.')   return 0;

    newTree = (TreeNode *)malloc( sizeof(TreeNode) );
    if( !newTree ) return 0;
    newTree->data.word = t;
    newTree->data.color = m_NodeColor;
    newTree->parent = 0;
    newTree->lchild = CreateTree(str);
    if(  newTree->lchild )  newTree->lchild->parent = newTree;
        
    newTree->rchild = CreateTree(str);
    if(  newTree->rchild )  newTree->rchild->parent = newTree;
    
    return newTree;
}

void PreOrder(TreeNode * Tree,int (*func)(TreeNode * Tree))
{
    if( ! Tree ) return ;
    
    if ( !func(Tree) )
        return;

    PreOrder(Tree->lchild,func);
    PreOrder(Tree->rchild,func);
}

void InOrder(TreeNode * Tree,int (*func)(TreeNode * Tree))
{
    if( ! Tree ) return ;
    
    InOrder(Tree->lchild,func); 
    if ( !func(Tree)  ) 
        return;
    InOrder(Tree->rchild,func);
}

void PostOrder(TreeNode * Tree,int (*func)(TreeNode * Tree))
{
    if( ! Tree ) return ;
    
    PostOrder(Tree->lchild,func);
    PostOrder(Tree->rchild,func);   
    if ( !func(Tree)  ) 
        return;
}

/*在树中查找元素*/
TreeNode * FindNode(TreeNode * Tree , char ch,int (*func)(TreeNode * Tree) )
{
    TreeNode * Finded = 0;

    if( ! Tree ) return 0;  
    
    if(func != NULL)
    {   
        func(Tree);
    }
    
    if ( ch == Tree->data.word )
    {
        return Tree;
    }
    
    Finded  = FindNode(Tree->lchild,ch,func);
    
    if(Finded)  return Finded;
    
    Finded  = FindNode(Tree->rchild,ch,func);
    
    if(Finded)  return Finded;

    return 0 ;
}
/*计算树的叶子节点*/
int GetLeafs(TreeNode * Tree)
{
    if( ! Tree )     return 0;
    if( Tree -> lchild == 0 && Tree -> rchild == 0 )
        return 1;
    else    
        return GetLeafs(Tree -> lchild ) + GetLeafs(Tree -> rchild) ;
}
/*计算树的高度*/
int GetHeight(TreeNode * Tree)
{
    int lh= 0 ,rh = 0;
    if( Tree == 0 )
        return 0;
    lh = GetHeight(Tree -> lchild );
    rh = GetHeight(Tree -> rchild);
    return lh   >= rh ? ( lh+ 1 ) : ( rh + 1);
}
/* 
在树中节点元素为pos的位置的
(loor左子树还是右子树)
插入子树elem 
*/
TreeNode * InsertTree(TreeNode * Tree , char pos,char loor,char elem)
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

int DeleteNode(TreeNode * Tree)
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
/*计算总节点个数*/
void NodeCount(TreeNode * Tree,int * numNode)
{
    if( ! Tree ) 
        return ;
    * numNode = * numNode +1;
 
    NodeCount(Tree->lchild,numNode);

    NodeCount(Tree->rchild,numNode);
}

int FreeTree(TreeNode ** Tree,char pos) /*删除树中某个节点下面所有的子树*/
{
    TreeNode * FindTree = 0;

    if(! (Tree && *Tree))
        return 0 ;

    FindTree = FindNode(*Tree,pos,NULL);

    if(FindTree == * Tree)
        *Tree = 0;
    return DeleteNode(FindTree);
}

int DestoryTree(TreeNode ** Tree)       /*销毁树*/
{
    TreeNode * FindTree = 0;

    if(! (Tree && *Tree))
        return 0 ;

    FindTree = * Tree;
    *Tree = 0;
    return DeleteNode(FindTree);
}

/*递归计算节点坐标*/
void SetNodeCoord(TreeNode * Tree,int dis)
{
    if(!Tree ) return;

    if(Tree->parent == 0)           /*当前节点是根节点*/
    {
        Tree->data.x = 320;
        dis /= 2;
        Tree->data.y = m_ScreenY+40;
    }
    else
    {
    
        if( Tree->parent->lchild == Tree  )
        {
            Tree->data.x = Tree->parent->data.x - dis ;
        }
        
        if( Tree->parent->rchild == Tree  )
        {
            Tree->data.x = Tree->parent->data.x + dis ;
        }

        Tree->data.y = Tree->parent->data.y + 60;   /*每向下一层y方向加80个像素*/

    }
    SetNodeCoord( Tree->lchild,dis / 2);
    SetNodeCoord( Tree->rchild,dis / 2);    
}

void OnButtonExit()
{
	char q = 0;
    
	MessageBox("You sure to exit? (press 'y' to eixt)");
    
	q = getch();

    if(	'y' == q  || 'Y' == q)
    {	 
	if( m_pVisitList )  /*清楚已存遍历节点，重绘制 */
	{
		DestoryTree(m_pVisitList);
		free(m_pVisitList);
	}
	if(m_pTree)
		DestoryTree(&m_pTree);
	 

        exit(1);
    } 
}
/*===================================按钮响应开始======================================*/
/*建树，按钮*/
void OnButtonCreatetree() 
{
    char  * pstr = "12344..R..QR..T..5W..E..67D..B..8A..9..";

    int i =0;
    char q ;
    MessageBox(":input the Tree");

    memset(m_StrTree,0,100);

    memset(m_StrFileName,0,100);
    q  = getch();

    while(q != 0x0d)
    {   
        if(q == 0x08) m_StrTree[--i] = 0; 
        else    m_StrTree[i++] = q;
        MessageBox(m_StrTree);
        q  = getch();
    }

    if(m_StrTree[0] == '.')
    {
        strcpy(&m_StrFileName,&m_StrTree[1]);
        if( !OnButtonOpenFile() ) return;
        MessageBox(m_StrTree);
    }

    if( strlen(m_StrTree) > 0 )
    {/* x#$Q..T....A..&H..D..MFGH...G..67..8.9....*/
        
        pstr  = (char *)&m_StrTree ;
    /* x...5..67..8.9..*/
        /* x..R..QR..T..5W..E..67D..B..8A..9..*/
    /* x..E..VV..E..MRV..E..QR..T..5WHV..d..BV..v..e2#..E..h3..m..67D#x..L..#2..^..M(V..$..]V..@..hVB*../..M*../..EG*../..F*../....8AB(V.E..]..V..*/
    }

    
    if(m_pTree)
        DestoryTree(&m_pTree);

    EraseOrder();
    m_NodeColor = 2;
    m_LineColor = 9;
    m_pTree = CreateTree(&pstr);

    if(!m_pTree)    return;

    ReCalTreeInfo(m_pTree);

    if( m_pVisitList )   /*存下所有的节点指针*/ 
    {
        DestoryTree(m_pVisitList);
        free(m_pVisitList);
        m_pVisitList = 0;
    }

    m_pVisitList  = (TreeNode**)malloc( sizeof(TreeNode *) * m_NodeNum );

    memset( m_pVisitList,0,sizeof(TreeNode *) * m_NodeNum);

    m_pDrawTree = m_pTree;

    OnDraw();
}

 /*先序遍历，按钮 */
void OnButtonPreorder() 
{

    if(!m_pTree || ! m_pVisitList)
        return;
 
    EraseOrder();

    m_NodeColor = 4;
    m_LineColor = 14;
    MessageBox("     Traversing  ");
    PreOrder(m_pTree,CreateVisitList);      /*将声明的指针传入*/
    StartMyTimer();   
    MessageBox("     Traversed  ");
}
  /*中序遍历，按钮 */
void OnButtonInorder() 
{
    if(!m_pTree || ! m_pVisitList)
        return;
    EraseOrder();

    m_NodeColor = 4;
    m_LineColor = 14;

    MessageBox("     Traversing  ");

    InOrder(m_pTree,CreateVisitList);           /*将声明的指针传入*/
    StartMyTimer();
    MessageBox("     Traversed  ");
}
 /*后序遍历，按钮 */
void OnButtonPosorder() 
{
    if(!m_pTree || ! m_pVisitList)
        return;
    EraseOrder();

    m_NodeColor = 4;
    m_LineColor = 14;
    MessageBox("     Traversing  ");
    PostOrder(m_pTree,CreateVisitList);     /*将声明的指针传入*/
    StartMyTimer(); 
    MessageBox("     Traversed  ");
}

  /*标识叶子节点，按钮 */
void OnButtonIdentityLeaf()
{
	EraseOrder();

	m_NodeColor = 10;
	m_LineColor = 15;

	m_pfLegalFinder = &FindLeafs;
	if( m_pTree )
	{
		FindNode(m_pTree,'.',CreateVisitList);
		m_bTreeFinding = 1;
		OnDraw();
		MessageBox("     Finding  ");
		StartMyTimer();	
		MessageBox("     Finded  ");
	}
}

 /*清空遍历链表，擦除遍历形成的图形，按钮 */
void EraseOrder()
{
    if( m_pVisitList )  /* /*清楚已存遍历节点，重绘制 */
    {
        DestoryTree(m_pVisitList);
	memset(m_pVisitList,0,m_NodeNum*sizeof(TreeNode*));
        OnDraw();
    }
    m_pfLegalFinder = 0;
    m_VisitNum = 0;
}

/* /*插入节点，按钮 */
void OnButtonInsertnode() 
{
    int sel = 0;
    char StrInsertPos = '';
    char StrInsertNew = '';
    char Loor = ' ';
    TreeNode * InsertedNode = 0;
            
    if(sel < 0) return;     /*左右子树没有选中*/

    EraseOrder();
    /**/
    MessageBox("Input the NodeTree that you want to Add");
    StrInsertPos = getch();

    MessageBox("which Tree you want to Add('l' or 'r')");
    Loor = getch();

    MessageBox("Input the New Node that you want to Add");
    StrInsertNew = getch();

    if(m_pTree && Loor != 0 && StrInsertPos!= 0 && StrInsertNew!= 0)
    {
        InsertedNode = InsertTree(m_pTree,StrInsertPos,Loor,StrInsertNew);
        if( InsertedNode  == 0)
        {
            MessageBox("Insert Failed");
            return;
        }
        /*重新计算所有节点坐标  */	
        ReCalTreeInfo(m_pTree);
        /*重新分配节点个数指针空间*/
        m_pVisitList  = (TreeNode**)realloc( m_pVisitList,sizeof(TreeNode *) * m_NodeNum );
        memset( m_pVisitList,0,sizeof(TreeNode *) * m_NodeNum);
        InsertedNode->data.color =6;
        /*更新视图，以便能显示所有节点；*/
        OnDraw();
    }
    
}

/*查找节点，按钮 */
void OnButtonFindnode() 
{
    TreeNode * FindedNode;
    char StrFindNode = '';
    char str[100]={0};

    EraseOrder();

    MessageBox("Input the Node that you want");
    StrFindNode = getch();

    m_NodeColor = 3;
    m_LineColor = 7;
    

    if(m_pTree)
    {		
	    sprintf(str,"input is %c",StrFindNode);
	    MessageBox(&str); 
        FindedNode =FindNode(m_pTree,StrFindNode,CreateVisitList);

        if(FindedNode)
        {

		m_bTreeFinding = 1;
		OnDraw();
	
	
		FillEllipse(14,FindedNode->data.x,FindedNode->data.y,10,FindedNode->data.word);
   	
		MessageBox("     Finding  ");
		StartMyTimer();	
		MessageBox("     Finded  ");
        }
        else
        { 	 
            MessageBox("Have Not Find The Node");
        }

    }
}

/*删除节点，按钮 */
void OnButtonDeletenode() 
{
	char StrDeleteNode = ' ';
    EraseOrder();   

    MessageBox("Input the Node that you want to Delete");
    StrDeleteNode = getch();

    if(m_pTree )
    {
        if(FreeTree(&m_pTree,StrDeleteNode) )
        {
            ReCalTreeInfo(m_pTree);
	    m_pDrawTree = m_pTree;
        }
        else
        {
            MessageBox("Did't Find the Node That you Want to Delete");
        }
	OnDraw();
    }
    
}
/*打开文件，读取到建树所用字符串 */
int OnButtonOpenFile()
{
    FILE *fp;
    fp=fopen((char*)&m_StrFileName,"r");
    memset((char*)&m_StrTree,0,100);
  
	if(!fp) 
	{
		strcpy((char*)&m_StrTree,"open");
		strcpy((char*)&m_StrTree,(char*)&m_StrFileName);
		strcpy((char*)&m_StrTree,"open file Wrong");
		MessageBox((char*)&m_StrTree);
		return 0 ;
	}
  
    fgets((char*)&m_StrTree,100,fp);
    fclose(fp);	
    return 1 ;
}


/*对树进行遍历的时候建立一个访问链表，如果m_pfLegalFinder不为空，链表里面的节点满足它所指向的函数 */
int CreateVisitList(TreeNode *Tree)
{
    if(!Tree)
        return 0;

    if(m_pfLegalFinder)
    {
        if( !m_pfLegalFinder(Tree) )
            return 0;
    
    }

    m_pVisitList[m_VisitNum] = (TreeNode *)malloc(sizeof(TreeNode));
    
    memset( m_pVisitList[m_VisitNum] ,0,sizeof(TreeNode) );

    m_pVisitList[m_VisitNum]->data = Tree->data;

    m_pVisitList[m_VisitNum]->data.color = m_NodeColor; 
    
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

/*重新计算树的相关信息 */
void ReCalTreeInfo(TreeNode *Tree)
{
    if(!Tree)   return ;
    m_Height = GetHeight(m_pTree);

    m_LeafNum = GetLeafs(m_pTree);
    m_NodeNum = 0 ;
    NodeCount(m_pTree,&m_NodeNum);
    SetNodeCoord( m_pTree ,640);
    
}

/*判断是否为空指针，用成员函数指针指向m_pfLegalFinder，创建遍历链表的时候作为判断依据，*/
/*只遍历的时候m_pfLegalFinder为空 */
int FindLeafs(TreeNode *Tree)
{
	if(!Tree)	return 0;
    if(  Tree->lchild == 0 && Tree->rchild == 0 )
        return 1;
    return 0;
}

/*===================================树操作结束====================================*/

/* 只在第二栏显示 */
void MessageBox( char * str)
{
    setfillstyle(SOLID_FILL,0);/* 黑色色背景 */
    bar(20,39,640-2,57);
    setcolor(7);    /* 白色按钮上的字 */
    outtextxy(20 + 5,39 + 10,str);
}

void delay(int inter)
{
    int i ,j;
    for( i =0 ; i < inter*80; i++)
    {
        for( j = 0 ; j < 500; j++);
    }
/*
    sleep(1);
*/
}
