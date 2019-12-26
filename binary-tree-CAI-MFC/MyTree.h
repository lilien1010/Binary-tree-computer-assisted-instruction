typedef struct tagTreeData
{
	int x ; 
	int y ; 
	char word;
}TreeData;

typedef struct tagTreeNode
{
	TreeData data;
	struct tagTreeNode * lchild;
	struct tagTreeNode * rchild;
	struct tagTreeNode * parent;
}TreeNode;

TreeNode * CreateTree( char ** str)
{
	char t = 0;
	TreeNode * newTree = 0;
	if(!( str && *str) ) return 0 ;
	
	t =	** str;	
	(*str) ++ ;	
	if( t == '.' || t == 0)	return 0;

	newTree = (TreeNode *)malloc( sizeof(TreeNode) );
	if( !newTree ) return 0;
	newTree->data.word = t;
	newTree->parent = 0;
	newTree->lchild = CreateTree(str);
	if(  newTree->lchild ) 	newTree->lchild->parent = newTree;
		
	newTree->rchild = CreateTree(str);
	if(  newTree->rchild ) 	newTree->rchild->parent = newTree;
	
	return newTree;
}

void PreOrder(TreeNode * Tree,void (*func)(TreeNode * Tree))
{
	if( ! Tree ) return ;
	
	func(Tree);
	PreOrder(Tree->lchild,func);
	PreOrder(Tree->rchild,func);
}

void InOrder(TreeNode * Tree,void (*func)(TreeNode * Tree))
{
	if( ! Tree ) return ;
	
	InOrder(Tree->lchild,func);	
	func(Tree);	
	InOrder(Tree->rchild,func);
}

void PostOrder(TreeNode * Tree,void (*func)(TreeNode * Tree))
{
	if( ! Tree ) return ;
	
	PostOrder(Tree->lchild,func);
	PostOrder(Tree->rchild,func);	
	func(Tree);
}

/*在树中查找元素*/
TreeNode * FindNode(TreeNode * Tree , char ch)
{
	TreeNode * Finded = 0;
	if( ! Tree ) return 0;
	
	if ( ch == Tree->data.word )
	{
		return Tree;
	}
	
	Finded  = FindNode(Tree->lchild,ch);
	
	if(Finded)	return Finded;
	
	Finded  = FindNode(Tree->rchild,ch);
	
	if(Finded)	return Finded;

	return 0 ;
}
/*计算树的叶子节点*/
int GetLeafs(TreeNode * Tree)
{
	if( ! Tree )
		return 0;
	
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
int InsertTree(TreeNode * Tree , char pos,char loor,char elem)
{
	TreeNode * FindTree = 0;
	TreeNode * NewTree = 0;

	if(!( Tree &&  (loor == 'l' || loor == 'r' ) ))
		return 0 ;

	FindTree = FindNode(Tree,pos);
	NewTree = (TreeNode*)malloc( sizeof(TreeNode) );
	memset(NewTree,0,sizeof(TreeNode));
	if(! ( FindTree && NewTree ))
		return 0 ;

	NewTree->data.word = elem ;
	if( loor == 'l')
	{
		NewTree->lchild = FindTree->lchild;
		FindTree->lchild = NewTree;
	}
	if( loor == 'r')
	{
		NewTree->rchild = FindTree->rchild;
		FindTree->rchild = NewTree;	
	}


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

	return 1;
}

int FreeTree(TreeNode ** Tree,char pos)	/*删除树中某个节点下面所有的子树*/
{
	TreeNode * FindTree = 0;

	if(! (Tree && *Tree))
		return 0 ;

	FindTree = FindNode(*Tree,pos);

	if(FindTree == * Tree)
		*Tree = 0;
	return DeleteNode(FindTree);
}