
// DragTestDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "DropTree.h"
#include "DropEdit.h"
#include "afxwin.h"


// CDragTestDlg dialog
class CDragTestDlg : public CDialogEx
{
// Construction
public:
	CDragTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DRAGTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDropTree m_DropTree;
	CDropTree m_DropTree2;
	CDropEdit m_Edit1;
	CDropEdit m_Edit2;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSave();
};
