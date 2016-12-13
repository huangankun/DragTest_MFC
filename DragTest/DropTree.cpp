// DropTree.cpp : implementation file
//

#include "stdafx.h"
//#include "dropexdemo.h"
#include "DropTree.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropTree

CDropTree::CDropTree()
{
	m_bDraging = FALSE;
}

CDropTree::~CDropTree()
{
}


BEGIN_MESSAGE_MAP(CDropTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CDropTree)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(DROPM_DRAGOVER,OnDragOver)
	ON_MESSAGE(DROPM_DROPEX,OnDropEx)
	ON_MESSAGE(DROPM_DROP,OnDrop)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropTree message handlers

LRESULT CDropTree::OnDragOver(WPARAM pDropInfoClass, LPARAM lParm)
{
	COleDropInfo* pInfo = (COleDropInfo* )pDropInfoClass;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(COleDropInfo)));

	if( pInfo->m_pDataObject->IsDataAvailable( CF_TEXT ) )
		return DROPEFFECT_COPY;
	else
		return DROPEFFECT_NONE;
}

LRESULT CDropTree::OnDrop(WPARAM pDropInfoClass, LPARAM lParm)
{
	COleDropInfo* pInfo = (COleDropInfo* )pDropInfoClass;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(COleDropInfo)));

	if( pInfo->m_pDataObject->IsDataAvailable( CF_TEXT ) )
	{
		HGLOBAL hMem = pInfo->m_pDataObject->GetGlobalData( CF_TEXT );
		char* lp = (char *)GlobalLock((HGLOBAL) hMem);//lock source
		if (lp != NULL)
		{
			CString str = lp;
			//Set Windows title with Drop text
			DWORD dwPos = ::GetMessagePos();
			CPoint pt(LOWORD(dwPos), HIWORD(dwPos));
			ScreenToClient(&pt);    //得到树形视图客户区坐标
			HTREEITEM hTreeItem=HitTest(pt);
			if (SelectItem(hTreeItem))
			{
				CString myStr = GetItemText(hTreeItem);
				if (myStr != "循环")
				{
					if (GetParentItem(hTreeItem) !=NULL)
						HTREEITEM sub_root = this->InsertItem(str,0,1,GetParentItem(hTreeItem),TVI_LAST);
					else
						HTREEITEM root = this->InsertItem(str,0,1,TVI_ROOT,TVI_LAST);
				}
				else
				{
					HTREEITEM root = this->InsertItem(str,0,1,hTreeItem,TVI_LAST);
				}	
			}
			else
				HTREEITEM sub_root = this->InsertItem(str,0,1,TVI_ROOT,TVI_LAST);
			this->Expand(hTreeItem,TVE_EXPAND);
			UpdateData(TRUE);
		}
		GlobalUnlock( hMem );//unlock source
		return TRUE;
	}
	else
		return FALSE;
}

LRESULT CDropTree::OnDropEx(WPARAM pDropInfoClass, LPARAM lParm)
{
	return (LRESULT)-1;
}

BOOL CDropTree::Register()
{
	return m_dropEx.Register( this );
}

void CDropTree::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	CTreeCtrl::OnLButtonDown(nFlags, point);

	CPoint posBefore,posAfter;//!判断是否为拖动选择文本
	::GetCursorPos( &posBefore );//!点击时鼠标位置
	Sleep(250);
	MSG msg;
	::PeekMessage(
		&msg,
		GetSafeHwnd(),
		WM_LBUTTONUP,
		WM_LBUTTONUP,
		PM_NOREMOVE
		);
	::GetCursorPos( &posAfter );//!判断时鼠标位置
	//随意点击而已或选择文本(鼠标位置改变),返回
	if( msg.message==WM_LBUTTONUP  )//增加判断
	{
		HTREEITEM tree = HitTest(point);
		if(tree==NULL)
		{
			PostMessage(WM_KILLFOCUS);
		}
		else
		{
			PostMessage(WM_SETFOCUS);
		}
		CTreeCtrl::OnLButtonDown(nFlags, point);
		return;
	}
	HTREEITEM tree = HitTest(point);

	//HTREEITEM tree = GetSelectedItem();
	CString sContens = GetItemText(tree);
	SelectItem(tree);

	HGLOBAL hData = GlobalAlloc(GHND|GMEM_SHARE, sContens.GetLength()+1 );
	char *pS = (char *)GlobalLock( hData );
	memcpy( pS, (LPCTSTR)sContens, sContens.GetLength()+1 );
	GlobalUnlock( hData );

	m_bDraging = TRUE;	//开始拖动
	COleDataSource source;
	source.CacheGlobalData( CF_TEXT, hData );
	source.DoDragDrop( DROPEFFECT_COPY );
	GlobalFree( hData );
	m_bDraging = FALSE;	//完成拖动
}
void   CDropTree::ExpandTreeItems(const   CTreeCtrl&   tree,HTREEITEM   hItem,CString filePathName,CString strBuf) 
{ 
	if (tree.GetItemText(hItem)== "循环")
	{
		HTREEITEM   hChildItem = tree.GetChildItem(hItem); 
		strBuf = strBuf + "\r\n";
		if ( NULL != hChildItem)
			ExpandTreeItems(tree,hChildItem,filePathName,strBuf);


		HTREEITEM hSib = tree.GetNextSiblingItem(hItem);
		if (hSib != NULL)
			ExpandTreeItems(tree,hSib,filePathName,strBuf);
	}
	AfxMessageBox( tree.GetItemText(hItem));
	CStdioFile file2(filePathName,CFile::modeWrite);
	file2.WriteString(tree.GetItemText(hItem));
	file2.Flush();
	file2.Close();

	HTREEITEM   hChildItem = tree.GetChildItem(hItem); 
	if ( NULL != hChildItem)
		ExpandTreeItems(tree,hChildItem,filePathName,strBuf);


	HTREEITEM hSib = tree.GetNextSiblingItem(hItem);
	if (hSib != NULL)
		ExpandTreeItems(tree,hSib,filePathName,strBuf);
}