#include "OleDropTargetEx.h"

#if !defined(AFX_DROPEDIT_H__)
#define AFX_DROPEDIT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DropEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDropEdit window
//演示可接收拖动的编辑控件

class CDropEdit : public CEdit
{
// Construction
public:
	CDropEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bDraging;
	virtual BOOL Register();
	virtual ~CDropEdit();

	// Generated message map functions
protected:
	COleDropTargetEx m_dropEx;
//处理OnDropEx消息是必须的，否则OnDrop函数不会被执行
//当然也可以在OnDropEx函数中处理数据
	virtual LRESULT OnDrop(WPARAM pDropInfoClass, LPARAM lParm);
	virtual LRESULT OnDropEx(WPARAM pDropInfoClass, LPARAM lParm);
	virtual LRESULT OnDragOver(WPARAM pDropInfoClass,LPARAM lParm);
	//{{AFX_MSG(CDropEdit)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPEDIT_H__)
