// DropTree.cpp : implementation file
//

#include "stdafx.h"
//#include "dropexdemo.h"
#include "DropTree.h"

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
			//Set Windows title with Drop text 
			SetWindowText( lp );
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

	CPoint posBefore,posAfter;//!�ж��Ƿ�Ϊ�϶�ѡ���ı�
	::GetCursorPos( &posBefore );//!���ʱ���λ��
	Sleep(250);
	MSG msg;
	::PeekMessage(
		&msg,
		GetSafeHwnd(),
		WM_LBUTTONUP,
		WM_LBUTTONUP,
		PM_NOREMOVE
		);
	::GetCursorPos( &posAfter );//!�ж�ʱ���λ��
	//���������ѻ�ѡ���ı�(���λ�øı�),����
	if( msg.message==WM_LBUTTONUP  )//�����ж�
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

	m_bDraging = TRUE;	//��ʼ�϶�
	COleDataSource source;
	source.CacheGlobalData( CF_TEXT, hData );
	source.DoDragDrop( DROPEFFECT_COPY );
	GlobalFree( hData );
	m_bDraging = FALSE;	//����϶�
}