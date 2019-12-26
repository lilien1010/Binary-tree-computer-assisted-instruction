#include "math.h"
#include "stdio.h"
#define NULL 0

/*ͨ�ù��ܺ���*/
void delay(int inter);
void MessageBox(char * str);

/*==============����������ʼ=========================*/
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

    /*����ָ�룺��CreateVisitList��ʹ�ã����Եõ��ض���Ҷ�ӽ�� */  
    TreeNode * m_pTree;     /*��ǰ��ʾ����*/
    TreeNode ** m_pVisitList;   /*�洢�����ڵ�ָ��*/

    int m_Height;           /*���ĸ߶�*/
    int m_LeafNum;          /*����Ҷ����*/
    int  m_NodeNum ;        /*���Ľڵ���*/
    int  m_VisitNum ;       /*�Ѿ��ڵ�����ĸ���*/
    char    m_StrFileName[100];
    char    m_StrTree[100]={0};     /*��ǰҪ�½�����*/    
/*===========����========/*
    /*�½���*/
    TreeNode * CreateTree( char ** str);    
    /*�������*/
    void PreOrder(TreeNode * Tree,int (*func)(TreeNode * Tree));
    /*�������*/
    void InOrder(TreeNode * Tree,int (*func)(TreeNode * Tree));
    /*�������*/
    void PostOrder(TreeNode * Tree,int (*func)(TreeNode * Tree));
    /*�����в���Ԫ��*/
    TreeNode * FindNode(TreeNode * Tree , char ch,int (*func)(TreeNode * Tree) );
    /*��������Ҷ�ӽڵ�*/
    int GetLeafs(TreeNode * Tree);
    /*�������ĸ߶�*/
    int GetHeight(TreeNode * Tree);
    /* ����pos��λ�õ�loor��������elem  ,���ز���ڵ��λ�� */
    TreeNode * InsertTree(TreeNode * Tree , char pos,char loor,char elem);
    int DeleteNode(TreeNode * Tree);            /*ɾ��ĳ���ڵ�*/
    int DestoryTree(TreeNode ** Tree);          /*������*/
    int FreeTree(TreeNode ** Tree,char pos);        /*ɾ������ĳ���ڵ��������е�����*/

    void NodeCount(TreeNode * Tree,int * numNode);      /*ͳ�����нڵ����*/

    int FindLeafs(TreeNode *Tree);              /*�ж��Ƿ�ΪҶ��*/

    void ReCalTreeInfo(TreeNode* Tree);         /*����������Ϣ���߶ȣ�Ҷ����*/

    int CreateVisitList(TreeNode * Tree);           /*��������ʱ��*/
            		
    void SetNodeCoord(TreeNode * Tree,int);         /*������������*/
    
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
/*===================����������================================*/

/*===================��ͼ������ʼ================================*/

    TreeNode * m_pDrawTree;     /*��ǰҪ���Ƶ���*/
    float m_rate;               /*���ƶ����ƶ�����*/    

    float m_ScreenX;

    float m_ScreenY; 
    int m_TimerSwitch;          /*��ʱ������*/  
    int m_LineColor = 2;    
    int m_bTreeFinding = 0; 
    int m_NodeColor = 2;

    TreeNode *m_pDrawTree= NULL;
    
    void StartMyTimer();        /*��ʼ��ʱ����*/
    void KillMyTimer();         /*ֹͣ��ʱ��*/
    void OnDraw();
    void OnTimer() ;
    int m_DrawedNode;
    int m_bTreeTraversed;       /*��ʶ�Ƿ������ɣ�ÿ�δ򿪼�ʱ��������Ϊ0*/
    
    void DrawTree(TreeNode * Tree,int LineColor);/*����TreeNodeָ��ָ������*/
    
    void DrawTreeOrder(TreeNode **);    /*���ݼ�ʱ������̬��ʾ���������*/
    
    void MoveTreeOrderNode(TreeNode **);    /*�ڼ�ʱ�������У�������ʾ��̬����˳��*/
            			
                        /*�ڽ�������Ľ���ŵ�����*/
    void ResetTreeOrderNode(TreeNode ** ThisTree,int dis,int NodeNum);

    int CaculateGgradient(float  xp,float  yp,float  xc,float  yc,float * arccos,float * arcsin);/*��������ֱ�ӵĽǶ�ֵ*/

    void DrawLine(int Color,int kd,int x1, int y1, int x2, int y2);
    void DrawString(int Color,int x,int y,char * str);
    void FillEllipse(int Color,int x, int y, int radius,char);
    
/*===================��ͼ��������======================*/

/*===================��ͼ�Ĳ�����ʼ======================*/
void DrawLine(int Color,int kd,int x1, int y1, int x2, int y2)
{
    setcolor(Color);    
    if( kd != 1) kd = 3;    
    setlinestyle(SOLID_LINE,1,kd );
    line(x1,  y1,  x2,  y2);
}
 /*        DEFAULT_FONT   =0   8x8 ����
        TRIPLEX_FONT   =1   �����ʻ�
        SMALL_FONT     =2   С������
        SANS_SERIF_FONT=3   �޳�������
        GOTHIC_FONT    =4   ��������
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
            /*�ڵ�д���ַ���*/
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

 	setfillstyle(SOLID_FILL,0);/* ��ɫɫ���� */
        bar(1,m_ScreenY + 28,640-2,480-2);

  	if(m_pDrawTree == 0)
	{
		setfillstyle(SOLID_FILL,0);/* ��ɫĨ��ԭ������Ϣ */
		bar(6,69,640-6,85);
	}
        DrawTree(m_pDrawTree,9);
 
	if( m_bTreeTraversed   && m_pVisitList && *(m_pVisitList))
        {
            DrawTreeOrder(m_pVisitList);    
        } 

        /* �����������*/
        setcolor(2);/* Greenɫ */
        rectangle(0,61,639,479);
}
/*��ʼ��ʱ��*/
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

/*��ֹ��ʱ��, �޸����ߵ���ɫ*/
void KillMyTimer()
{
    m_LineColor ^=0x7f;
    m_TimerSwitch = 0;
    m_bTreeFinding = 0;
    m_bTreeTraversed = 1;
}



/*��ʱ�����ᶯ���ӹ���*/
void OnTimer() 
{
    if( m_pVisitList )
    {
        /*����ȥҪ��̬�����Ľڵ�����*/
        MoveTreeOrderNode(m_pVisitList);
    }

}


/*�ݹ����һ��������*/
void DrawTree(TreeNode *Tree,int LineColor)
{
    char str[100] = {0};    
    float px,py;            /*�ֱ߱�ʾ���ڵ�͵�ǰ�ڵ㣨���ӣ���x y*/
    float arcsin = 0.0f,arccos =  0.0f; /*���ڵ㵽�ӽڵ�����ߺ�x����Ƕ� ��sinֵ*/ 
    float radius =10.0f;
    
    if( Tree == NULL ) return ;
  
    /*��ʾ������Ϣ��*/
    if(Tree->parent == 0 && m_bTreeTraversed  )
    {
        setfillstyle(SOLID_FILL,0);/* ��ɫĨ��ԭ�� */
        bar(6,69,640-6,85);
	sprintf(str,"All Nodes = %d Tree Height=%d Tree LeafNum = %d  \0",m_NodeNum,m_Height,m_LeafNum);
        DrawString( 14,7,75,str);   
    }
    
    /*����һ����ϵ���׽ڵ���߶�*/
    if( Tree->parent  )
    {
        /*����Ĳ�����Ϊ�˷�ֹ���Ƶ��߶��ڽڵ�Բ֮��*/
        {
            /*���㵱ǰ�ڵ�͸��ڵ����ߵĽǶ�ֵ*/ 
            CaculateGgradient(Tree->parent->data.x,Tree->parent->data.y,
                Tree->data.x,Tree->data.y, &arccos,&arcsin);

            py = Tree->parent->data.y - radius * arcsin ;
	    px = Tree->parent->data.x - radius * arccos ;
 
	}
        DrawLine(LineColor,1,(int)(Tree->data.x),(int)(Tree->data.y),(int)(px),(int)(py));
    }
    /*�����ڵ�data�������ݻ��ƽڵ�*/
    FillEllipse(Tree->data.color,Tree->data.x,Tree->data.y,10,Tree->data.word);

    DrawTree(Tree->lchild,LineColor);
    DrawTree(Tree->rchild,LineColor);
}

/*���Ʊ��������нڵ㣬��������*/
void DrawTreeOrder(TreeNode **pVisitList)              
{  
    float arcsin = 0.0f,arccos =  0.0f; /*���ڵ㵽�ӽڵ�����ߺ�x����Ƕ� ��sinֵ*/
    float radius = 10.0f;            /*�뾶*/
    float Xi = 0, Yi = 0,Xj =0 ,Yj =0 ;         /*�߶κ�����Բ�Ľ������꣨j=�� i=�ӣ�*/
    TreeNode * ThisTree;
  
    if( m_bTreeTraversed && m_bTreeFinding == 0 )/*������Ͼ��ظ��������õ���̬��ֱЧ��*/
    {
	    DrawTree(pVisitList[0],m_LineColor);
	    return;
    }

        ThisTree = pVisitList[m_DrawedNode];
        if(!ThisTree) return;

        /*��newBrush��һ���뾶Ϊ10��Բ ��ɫ���Խڵ�����     */
        if( m_rate <= 0.15  )
        {
            FillEllipse(ThisTree->data.color,ThisTree->data.x,ThisTree->data.y,10,ThisTree->data.word);

        }
        /*�����ǰ�����һ���ڵ�Ͳ���Ҫ������*/
        if(ThisTree->lchild)
        {	
                /*���㵱ǰ�ڵ�͸��ڵ����ߵĽǶ�ֵ*/
            CaculateGgradient(ThisTree->data.x,ThisTree->data.y,
                ThisTree->lchild->data.x,ThisTree->lchild->data.y, &arccos,&arcsin);

            Xj = ThisTree->data.x - radius * arccos ;
            Yj = ThisTree->data.y - radius * arcsin ;

            Xi = ThisTree->lchild->data.x + radius * arccos ;
            Yi = ThisTree->lchild->data.y + radius * arcsin ;
       
 
    /*����һ����ϵ�Ѿ�����������һ���ڵ㵽��һ��Ŀ����߶Σ�m_rate�ԼӶ�̬*/
	DrawLine(m_LineColor,3,(int)(Xj ),(int)(Yj ),
            (int)( Xj + m_rate *  (Xi - Xj) ),(int)( Yj + m_rate *  (Yi - Yj)  ));
	 }
	
}

/*ͨ����ʱ������һ���ļ������б�ʷ���ĳ��ȣ� ���� DrawTreeOrder �γɶ���*/
void MoveTreeOrderNode(TreeNode **pVisitList)
{
    TreeNode * ThisTree = 0 ;   
    ThisTree = pVisitList[m_DrawedNode];

    if( ThisTree ->lchild == NULL || m_DrawedNode >= m_VisitNum-1 )      /*�����ǰ�ڵ��Ǳ��������һ����Ч�ڵ�*/
    {
        m_bTreeTraversed = 1;
        /*�����Ѿ�������Ľڵ㰴˳����Ŀ���ƶ�,���ǲ��ҽڵ�Ͳ�Ҫˮƽ����*/
        if(  m_rate <=1.0 && m_bTreeFinding == 0 )
        {
            ResetTreeOrderNode(pVisitList,30,m_DrawedNode+1);
        }
        else     /*m_rate����1��ʾ���нڵ㶼����*/
        {
            KillMyTimer();
	    return;
        }
        /*���»���*/
        OnDraw();
        return;
    }  

    m_rate  +=0.015f;           /*ÿ0.03��Ҫ���Ƶ�����������һ���ڵ㷽������5%�ĳ���*/

    if(m_rate >= 1.015)
    {
        m_rate = 0.0 ;          /*����һ���ڵ�֮������*/
        m_DrawedNode ++;        /*��Ŀ��������һ���ڵ�*/
    }
     DrawTreeOrder(pVisitList);   
    /*����ȥҪ��̬�������Ƶ�����*/

}

void ResetTreeOrderNode(TreeNode ** ThisTree,int dis,int NodeNum)
{
    float arcsin = 0.0f,arccos =  0.0f; /*���ڵ㵽�ӽڵ�����ߺ�x����Ƕ� ��sinֵ*/
    float Xnow, Ynow,Xdes,Ydes;     /*���������Ŀ������*/
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
    /*��NodeNum���ڵ��������Ŀ�ķ�������8%*/
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

    m_rate  +=0.08f;        /*ÿ0.01��Ҫ���Ƶ�����������һ���ڵ㷽������8%�ĳ���*/
}


/*��������֮���б�� ���ص���arcsin��arccos*/
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
/*=================================================��ͼ��������======================*/




/*===================================��������ʼ======================================*/
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

/*�����в���Ԫ��*/
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
/*��������Ҷ�ӽڵ�*/
int GetLeafs(TreeNode * Tree)
{
    if( ! Tree )     return 0;
    if( Tree -> lchild == 0 && Tree -> rchild == 0 )
        return 1;
    else    
        return GetLeafs(Tree -> lchild ) + GetLeafs(Tree -> rchild) ;
}
/*�������ĸ߶�*/
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
�����нڵ�Ԫ��Ϊpos��λ�õ�
(loor����������������)
��������elem 
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
/*�����ܽڵ����*/
void NodeCount(TreeNode * Tree,int * numNode)
{
    if( ! Tree ) 
        return ;
    * numNode = * numNode +1;
 
    NodeCount(Tree->lchild,numNode);

    NodeCount(Tree->rchild,numNode);
}

int FreeTree(TreeNode ** Tree,char pos) /*ɾ������ĳ���ڵ��������е�����*/
{
    TreeNode * FindTree = 0;

    if(! (Tree && *Tree))
        return 0 ;

    FindTree = FindNode(*Tree,pos,NULL);

    if(FindTree == * Tree)
        *Tree = 0;
    return DeleteNode(FindTree);
}

int DestoryTree(TreeNode ** Tree)       /*������*/
{
    TreeNode * FindTree = 0;

    if(! (Tree && *Tree))
        return 0 ;

    FindTree = * Tree;
    *Tree = 0;
    return DeleteNode(FindTree);
}

/*�ݹ����ڵ�����*/
void SetNodeCoord(TreeNode * Tree,int dis)
{
    if(!Tree ) return;

    if(Tree->parent == 0)           /*��ǰ�ڵ��Ǹ��ڵ�*/
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

        Tree->data.y = Tree->parent->data.y + 60;   /*ÿ����һ��y�����80������*/

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
	if( m_pVisitList )  /*����Ѵ�����ڵ㣬�ػ��� */
	{
		DestoryTree(m_pVisitList);
		free(m_pVisitList);
	}
	if(m_pTree)
		DestoryTree(&m_pTree);
	 

        exit(1);
    } 
}
/*===================================��ť��Ӧ��ʼ======================================*/
/*��������ť*/
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

    if( m_pVisitList )   /*�������еĽڵ�ָ��*/ 
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

 /*�����������ť */
void OnButtonPreorder() 
{

    if(!m_pTree || ! m_pVisitList)
        return;
 
    EraseOrder();

    m_NodeColor = 4;
    m_LineColor = 14;
    MessageBox("     Traversing  ");
    PreOrder(m_pTree,CreateVisitList);      /*��������ָ�봫��*/
    StartMyTimer();   
    MessageBox("     Traversed  ");
}
  /*�����������ť */
void OnButtonInorder() 
{
    if(!m_pTree || ! m_pVisitList)
        return;
    EraseOrder();

    m_NodeColor = 4;
    m_LineColor = 14;

    MessageBox("     Traversing  ");

    InOrder(m_pTree,CreateVisitList);           /*��������ָ�봫��*/
    StartMyTimer();
    MessageBox("     Traversed  ");
}
 /*�����������ť */
void OnButtonPosorder() 
{
    if(!m_pTree || ! m_pVisitList)
        return;
    EraseOrder();

    m_NodeColor = 4;
    m_LineColor = 14;
    MessageBox("     Traversing  ");
    PostOrder(m_pTree,CreateVisitList);     /*��������ָ�봫��*/
    StartMyTimer(); 
    MessageBox("     Traversed  ");
}

  /*��ʶҶ�ӽڵ㣬��ť */
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

 /*��ձ����������������γɵ�ͼ�Σ���ť */
void EraseOrder()
{
    if( m_pVisitList )  /* /*����Ѵ�����ڵ㣬�ػ��� */
    {
        DestoryTree(m_pVisitList);
	memset(m_pVisitList,0,m_NodeNum*sizeof(TreeNode*));
        OnDraw();
    }
    m_pfLegalFinder = 0;
    m_VisitNum = 0;
}

/* /*����ڵ㣬��ť */
void OnButtonInsertnode() 
{
    int sel = 0;
    char StrInsertPos = '';
    char StrInsertNew = '';
    char Loor = ' ';
    TreeNode * InsertedNode = 0;
            
    if(sel < 0) return;     /*��������û��ѡ��*/

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
        /*���¼������нڵ�����  */	
        ReCalTreeInfo(m_pTree);
        /*���·���ڵ����ָ��ռ�*/
        m_pVisitList  = (TreeNode**)realloc( m_pVisitList,sizeof(TreeNode *) * m_NodeNum );
        memset( m_pVisitList,0,sizeof(TreeNode *) * m_NodeNum);
        InsertedNode->data.color =6;
        /*������ͼ���Ա�����ʾ���нڵ㣻*/
        OnDraw();
    }
    
}

/*���ҽڵ㣬��ť */
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

/*ɾ���ڵ㣬��ť */
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
/*���ļ�����ȡ�����������ַ��� */
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


/*�������б�����ʱ����һ�������������m_pfLegalFinder��Ϊ�գ���������Ľڵ���������ָ��ĺ��� */
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

/*���¼������������Ϣ */
void ReCalTreeInfo(TreeNode *Tree)
{
    if(!Tree)   return ;
    m_Height = GetHeight(m_pTree);

    m_LeafNum = GetLeafs(m_pTree);
    m_NodeNum = 0 ;
    NodeCount(m_pTree,&m_NodeNum);
    SetNodeCoord( m_pTree ,640);
    
}

/*�ж��Ƿ�Ϊ��ָ�룬�ó�Ա����ָ��ָ��m_pfLegalFinder���������������ʱ����Ϊ�ж����ݣ�*/
/*ֻ������ʱ��m_pfLegalFinderΪ�� */
int FindLeafs(TreeNode *Tree)
{
	if(!Tree)	return 0;
    if(  Tree->lchild == 0 && Tree->rchild == 0 )
        return 1;
    return 0;
}

/*===================================����������====================================*/

/* ֻ�ڵڶ�����ʾ */
void MessageBox( char * str)
{
    setfillstyle(SOLID_FILL,0);/* ��ɫɫ���� */
    bar(20,39,640-2,57);
    setcolor(7);    /* ��ɫ��ť�ϵ��� */
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
