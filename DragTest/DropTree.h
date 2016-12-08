#include "OleDropTargetEx.h"

#if !defined(AFX_DROPTREE_H__438EAF4E_0C41_421B_9EB4_9EFC452ADC08__INCLUDED_)
#define AFX_DROPTREE_H__438EAF4E_0C41_421B_9EB4_9EFC452ADC08__INCLUDED_

#if _MSC_VER > 1000
#pragma once

#endif // _MSC_VER > 1000
// DropTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDropTree window

class CDropTree : public CTreeCtrl
{
// Construction
public:
	CDropTree();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual BOOL Register();
	virtual ~CDropTree();
	BOOL m_bDraging;
	void ExpandTreeItems(const   CTreeCtrl&   tree,HTREEITEM   hItem,CString filrPathName,CString strBuf); 

	// Generated message map functions
protected:
	//{{AFX_MSG(CDropTree)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	COleDropTargetEx m_dropEx;
	virtual LRESULT  OnDropEx(WPARAM pDropInfoClass, LPARAM lParm);
	virtual LRESULT OnDrop(WPARAM pDropInfoClass, LPARAM lParm);
	virtual LRESULT OnDragOver(WPARAM pDropInfoClass,LPARAM lParm);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPTREE_H__438EAF4E_0C41_421B_9EB4_9EFC452ADC08__INCLUDED_)
