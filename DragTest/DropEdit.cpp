// DropEdit.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
//#include "dropexdemo.h"
#include "DropEdit.h"
#include "DragTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropEdit

CDropEdit::CDropEdit()
{
	m_bDraging = FALSE;
}

CDropEdit::~CDropEdit()
{
}


BEGIN_MESSAGE_MAP(CDropEdit, CEdit)
	//{{AFX_MSG_MAP(CDropEdit)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(DROPM_DRAGOVER,OnDragOver)
	ON_MESSAGE(DROPM_DROPEX,OnDropEx)
	ON_MESSAGE(DROPM_DROP,OnDrop)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropEdit message handlers

BOOL CDropEdit::Register()
{
	return m_dropEx.Register( this );
}

LRESULT CDropEdit::OnDragOver(WPARAM pDropInfoClass, LPARAM lParm)
{
	COleDropInfo* pInfo = (COleDropInfo* )pDropInfoClass;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(COleDropInfo)));

	if( pInfo->m_pDataObject->IsDataAvailable( CF_TEXT ) )
		return DROPEFFECT_COPY;
	else
		return DROPEFFECT_NONE;
}

LRESULT CDropEdit::OnDropEx(WPARAM pDropInfoClass, LPARAM lParm)
{
	return (DROPEFFECT)-1;
}

LRESULT CDropEdit::OnDrop(WPARAM pDropInfoClass, LPARAM lParm)
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
			CString strText;
			GetWindowText(strText);
			CString str = lp;
			CString str2;
			if (strText !="")
			{
				str2=(strText+"\r\n")+str;
			}
			else
				str2 = str + strText;
			SetWindowText( str2);
		}
		GlobalUnlock( hMem );//unlock source
		return TRUE;
	}
	else
		return FALSE;
}

void CDropEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CEdit::OnLButtonDown(nFlags, point);

	//确信要拖动,而不是随便点击
	//按下左键250ms则认为要拖动
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
	if( msg.message==WM_LBUTTONUP || posBefore!=posAfter )//增加判断
		return;

	CString sContens;
	GetWindowText( sContens );
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
