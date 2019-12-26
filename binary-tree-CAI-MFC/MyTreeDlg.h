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

	TreeNode * m_pTree;		//��ǰ��ʾ����

	TreeNode ** m_pVisitList;	//�洢�����ڵ�ָ��

	UINT m_NowTmp;		//ȫ����ʱ����
	UINT m_Height;		//���ĸ߶�
	UINT m_LeafNum;		//����Ҷ����
	int  m_NodeNum ;	//���Ľڵ���
	int  m_VisitNum ;	//�Ѿ��ڵ�����ĸ���

	/*�½���*/
	TreeNode * CreateTree( char ** str);	

	void PreOrder(TreeNode * Tree,int (CMyTreeDlg::*func)(TreeNode * Tree));

	void InOrder(TreeNode * Tree,int (CMyTreeDlg::*func)(TreeNode * Tree));

	void PostOrder(TreeNode * Tree,int (CMyTreeDlg::*func)(TreeNode * Tree));

	void NodeCount(TreeNode * Tree,int * numNode);
	/*�����в���Ԫ��*/
	TreeNode * FindNode(TreeNode * Tree , char ch);
	void ReSetTraverseCoord(TreeNode ** Tree,int dis);
	/*��������Ҷ�ӽڵ�*/
	int GetLeafs(TreeNode * Tree);

	/*�������ĸ߶�*/
	int GetHeight(TreeNode * Tree);
	/* 
	�����нڵ�Ԫ��Ϊpos��λ�õ�
	(loor����������������)
	��������elem  ,���ز���ڵ��λ��
	*/
	TreeNode * InsertTree(TreeNode * Tree , char pos,char loor,char elem);

	int DeleteNode(TreeNode * Tree);		//ɾ��ĳ���ڵ�

	int DestoryTree(TreeNode ** Tree);		//������

	int FreeTree(TreeNode ** Tree,char pos);	/*ɾ������ĳ���ڵ��������е�����*/

// Dialog Data
	//{{AFX_DATA(CMyTreeDlg)
	enum { IDD = IDD_DIALOG_TREE };
	CComboBox	m_ComLoor;
	CString	m_StrTree;		/*��ǰҪ�½�����*/
	CString	m_StrInsertPos;		/*Ҫ�����λ��*/
	CString	m_StrInsertNew;		/*Ҫ������µĽڵ���*/
	CString	m_StrFindNode;		/*Ҫ���ҵĽڵ�*/		
	CString	m_StrDeleteNode;	/*Ҫɾ���Ľڵ�*/
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
