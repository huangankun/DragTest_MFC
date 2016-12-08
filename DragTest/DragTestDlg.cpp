
// DragTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DragTest.h"
#include "DragTestDlg.h"
#include "afxdialogex.h"
#include "CommandWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDragTestDlg dialog




CDragTestDlg::CDragTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDragTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDragTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_DropTree);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX,IDC_TREE2,m_DropTree2);
}

BEGIN_MESSAGE_MAP(CDragTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CDragTestDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDragTestDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CDragTestDlg message handlers

BOOL CDragTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if( !m_Edit1.Register() )
		TRACE("register drop edit faile");

	if( !m_Edit2.Register() )
		TRACE("register drop edit faile");

	if( !m_DropTree.Register() )
		TRACE("register drop listbox faile");

	if( !m_DropTree2.Register() )
		TRACE("register drop listbox faile");
	// TODO: Add extra initialization here
	//HTREEITEM hroot= m_DropTree.InsertItem("���ؼ�");
	//m_DropTree.InsertItem("�ӽڵ�",hroot);
	HTREEITEM root0=m_DropTree.InsertItem(_T("����"),0,1,TVI_ROOT,TVI_LAST);
	HTREEITEM root1=m_DropTree.InsertItem(_T("����"),0,1,TVI_ROOT,TVI_LAST);
	HTREEITEM root2=m_DropTree.InsertItem(_T("ѭ��"),0,1,TVI_ROOT,TVI_LAST);
	//һ���ӽڵ�
	HTREEITEM sub_son10=m_DropTree.InsertItem(_T("���� 1-1"),0,1,root0,TVI_LAST);
	HTREEITEM sub_son11=m_DropTree.InsertItem(_T("���� 1-2"),0,1,root0,TVI_LAST);
	HTREEITEM sub_son12=m_DropTree.InsertItem(_T("���� 1-3"),0,1,root0,TVI_LAST);
	HTREEITEM sub_son1=m_DropTree.InsertItem(_T("���� 2-1"),0,1,root1,TVI_LAST);

	HTREEITEM root20=m_DropTree2.InsertItem(_T("���� 1-1"),0,1,TVI_ROOT,TVI_LAST);
	HTREEITEM root21=m_DropTree2.InsertItem(_T("���� 2-1"),0,1,TVI_ROOT,TVI_LAST);
	HTREEITEM root22=m_DropTree2.InsertItem(_T("ѭ��"),0,1,TVI_ROOT,TVI_LAST);


	m_DropTree.Expand(root0,TVE_EXPAND);
	m_DropTree2.Expand(root0,TVE_EXPAND);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDragTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDragTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDragTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDragTestDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//------------------------------------------------------------------------------
	// CFileDialog�������⣺http://baike.baidu.com/view/1298552.htm
	//------------------------------------------------------------------------------
	CFileDialog fDlg(TRUE, _TEXT("txt"), NULL, 4|2,
		_TEXT("�ı��ļ�(*.txt,*.ini,*.log)|*.txt;*.ini;*.log|ȫ���ļ�(*.*)|*.*||"));

	// ���� DoModal() �������򿪶Ի���
	if (fDlg.DoModal() == IDOK)
	{
		// ���ñ༭��1������Ϊѡ���ļ���·��
		// GetPathName() --> ����ѡ���ļ�������·��
		SetDlgItemText(IDC_EDIT_FILEPATH,fDlg.GetPathName());

		//------------------------------------------------------------------------------
		// CFile�������⣺http://baike.baidu.com/view/994710.htm
		//------------------------------------------------------------------------------
		CFile fFile(fDlg.GetPathName(),CFile::modeRead);

		// ��Ϊ��Windows�³��õ��ı��������ΪANSI
		// ���������ڵ���ѡ���ʱ��ѡ����Unicode����
		// ������Ҫʹ��CStringA���͵ı�����
		// CStringA������⣺http://baike.baidu.com/view/998109.htm
		CStringA strFile ;

		// ��ȡ���ļ�����
		// ��һ����������ȡ���ݵĻ�������
		// �ڶ�����������ȡ���ݵĳ���
		fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()),fFile.GetLength());

		// �ر��ļ����
		fFile.Close();

		int length_buffer=0;
		CString charStr = CString(strFile);
		charStr.Replace("\n","");
		charStr.Replace("\r","");
		length_buffer = charStr.GetLength();
		int arrayCount=0;
		CString str1;
		CArray <CommandWizard,CommandWizard&> myArray;
		myArray.SetSize(length_buffer/8,8);
		while(charStr !="")
		{
			str1 = charStr.Left(8);
			charStr.Delete(0,8);
			CString strCmd;
			int pri1=0;
			int pri2=0;
			strCmd = str1.Left(4);
			str1.Delete(0,5);
			pri1 = atoi(str1.Left(1));
			str1.Delete(0,2);
			pri2=atoi(str1.Left(1));
			CommandWizard cmdBuf(strCmd,pri1,pri2);
			myArray.SetAtGrow(arrayCount,cmdBuf);
			arrayCount++;
		}
		// �ͷŻ�������
		m_DropTree.DeleteAllItems();
		HTREEITEM root0=m_DropTree.InsertItem(_T("����"),0,1,TVI_ROOT,TVI_LAST);
		HTREEITEM root1=m_DropTree.InsertItem(_T("����"),0,1,TVI_ROOT,TVI_LAST);
		HTREEITEM root2=m_DropTree.InsertItem(_T("ѭ��"),0,1,TVI_ROOT,TVI_LAST);
		strFile.ReleaseBuffer();
		for(int i = 0 ; i < myArray.GetSize();i++)
		{
			for(int j = i+1 ; j<myArray.GetSize() ; j++)
			{
				if ((myArray.GetAt(i).getCmdName() == myArray.GetAt(j).getCmdName())
					&& (myArray.GetAt(i).getPara_1() == myArray.GetAt(j).getPara_1())
					&&(myArray.GetAt(i).getPara_2() == myArray.GetAt(j).getPara_2()))
				{
					myArray.RemoveAt(j);
					j--;
				}
			}
		}
		for (int i = 0 ; i<myArray.GetSize();i++)
		{
			if (myArray.GetAt(i).getCmdName() =="����")
			{
				CString str,str1,str2;
				str1.Format(_T("%d"),myArray.GetAt(i).getPara_1());
				str2.Format(_T("%d"),myArray.GetAt(i).getPara_2());
				str=myArray.GetAt(i).getCmdName()+" "+str1+"-"+str2;
				HTREEITEM sub_son=m_DropTree.InsertItem(str,0,1,root0,TVI_LAST);
			}
			else if(myArray.GetAt(i).getCmdName() == "����")
			{
				CString str,str1,str2;
				str1.Format(_T("%d"),myArray.GetAt(i).getPara_1());
				str2.Format(_T("%d"),myArray.GetAt(i).getPara_2());
				str=myArray.GetAt(i).getCmdName()+" "+str1+"-"+str2;
				HTREEITEM sub_son=m_DropTree.InsertItem(str,0,1,root1,TVI_LAST);
			}
		}
		// �򻷾�ΪUnicdoe��ԭ��CStringA������ֱ����ʾ������ؼ���
		// ����ʹ��CStringת��ΪUnicdoe�ַ�
		SetDlgItemText(IDC_EDIT2,CString(strFile));
	}
}


void CDragTestDlg::OnBnClickedButtonSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	/*C���Զ��ļ���ʹ�ò��õ��ǻ���ϵͳ���������ݱ������͵�����������������������ʱ��Ż����뵽���̵���*/
	//FILE *pFile = fopen("ReadMe.txt","w");
	//fwrite("http://www.sunxin.org",1,strlen("http://www.sunxin.org"),pFile); //д���ļ�
	//fclose(pFile);
	//fflush(pFile);


	// TODO: Add your control notification handler code here   
	// ���ù�����   
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Word�ļ�(*.doc)|*.doc|�����ļ�(*.*)|*.*||");   
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg(FALSE, _T("doc"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);   
	CString strFilePath;   

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg.DoModal())   
	{   
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����
		//�����ļ�,����Ѿ������ļ���Ḳ��֮ǰ������
		CFile file1;
		CFileException exp;
		BOOL bCreateFile = file1.Open(fileDlg.GetPathName(),CFile::modeCreate,&exp);
		file1.Close();
		CString strFileName,strBuf;
		int nodeCount = m_DropTree2.GetCount();
		HTREEITEM root_node = m_DropTree2.GetRootItem();
		m_DropTree2.ExpandTreeItems(m_DropTree2,root_node,fileDlg.GetPathName(),strBuf);
		GetDlgItemText(	IDC_TREE2,strFileName);
		//CStdioFile file2(fileDlg.GetPathName(),CFile::modeWrite);
		//MessageBox(strFileName);
		//file2.WriteString(strFileName);
		//file2.Flush();
		//file2.Close();
		strFilePath = fileDlg.GetPathName();   
		SetDlgItemText(IDC_EDIT1, strFilePath);   
	}   
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
