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
//��ʾ�ɽ����϶��ı༭�ؼ�

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
//����OnDropEx��Ϣ�Ǳ���ģ�����OnDrop�������ᱻִ��
//��ȻҲ������OnDropEx�����д�������
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
