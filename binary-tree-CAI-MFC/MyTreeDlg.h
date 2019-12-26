#if !defined(AFX_MYTREEDLG_H__B5A786A4_4EED_488E_B926_1E70C87C4C54__INCLUDED_)
#define AFX_MYTREEDLG_H__B5A786A4_4EED_488E_B926_1E70C87C4C54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTreeDlg.h : header file
//
#include "math.h"
/////////////////////////////////////////////////////////////////////////////
// CMyTreeDlg dialog
 
typedef struct tagTreeData
{
	float x ; 
	float y ;
	Color color;
	char word;
}TreeData;

typedef struct tagTreeNode
{
	TreeData data;
	struct tagTreeNode * lchild;
	struct tagTreeNode * rchild;
	struct tagTreeNode * parent;
}TreeNode;

class CMyTreeDlg : public CDialog
{
// Construction
public:
	int CreateVisitList(TreeNode * Tree);


	CMyTreeDlg(CWnd* pParent = NULL);   // standard constructor
	void SetNodeCoord(TreeNode * Tree,int);

	TreeNode * m_pTree;		//当前显示的树

	TreeNode ** m_pVisitList;	//存储遍历节点指针

	UINT m_NowTmp;		//全局临时变量
	UINT m_Height;		//树的高度
	UINT m_LeafNum;		//树的叶子数
	int  m_NodeNum ;	//树的节点数
	int  m_VisitNum ;	//已经节点遍历的个数

	/*新建树*/
	TreeNode * CreateTree( char ** str);	

	void PreOrder(TreeNode * Tree,int (CMyTreeDlg::*func)(TreeNode * Tree));

	void InOrder(TreeNode * Tree,int (CMyTreeDlg::*func)(TreeNode * Tree));

	void PostOrder(TreeNode * Tree,int (CMyTreeDlg::*func)(TreeNode * Tree));

	void NodeCount(TreeNode * Tree,int * numNode);
	/*在树中查找元素*/
	TreeNode * FindNode(TreeNode * Tree , char ch);
	void ReSetTraverseCoord(TreeNode ** Tree,int dis);
	/*计算树的叶子节点*/
	int GetLeafs(TreeNode * Tree);

	/*计算树的高度*/
	int GetHeight(TreeNode * Tree);
	/* 
	在树中节点元素为pos的位置的
	(loor左子树还是右子树)
	插入子树elem  ,返回插入节点的位置
	*/
	TreeNode * InsertTree(TreeNode * Tree , char pos,char loor,char elem);

	int DeleteNode(TreeNode * Tree);		//删除某个节点

	int DestoryTree(TreeNode ** Tree);		//销毁树

	int FreeTree(TreeNode ** Tree,char pos);	/*删除树中某个节点下面所有的子树*/

// Dialog Data
	//{{AFX_DATA(CMyTreeDlg)
	enum { IDD = IDD_DIALOG_TREE };
	CComboBox	m_ComLoor;
	CString	m_StrTree;		/*当前要新建的树*/
	CString	m_StrInsertPos;		/*要插入的位置*/
	CString	m_StrInsertNew;		/*要插入的新的节点树*/
	CString	m_StrFindNode;		/*要查找的节点*/		
	CString	m_StrDeleteNode;	/*要删除的节点*/
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyTreeDlg)
	afx_msg void OnButtonCreatetree();
	afx_msg void OnButtonPreorder();
	afx_msg void OnButtonInorder();
	afx_msg void OnButtonPosorder();
	afx_msg void OnButtonInsertnode();
	afx_msg void OnButtonFindnode();
	afx_msg void OnButtonDeletenode();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG	
	afx_msg void OnButtonEraseOrder();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREEDLG_H__B5A786A4_4EED_488E_B926_1E70C87C4C54__INCLUDED_)
