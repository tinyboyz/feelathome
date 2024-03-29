
// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "feelathome.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMainDlg 对话框



CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_COMMAND(ID_FILE_OPEN, &CMainDlg::OnFileOpen)
    ON_COMMAND(ID_DIRECTORY_OPEN, &CMainDlg::OnDirectoryOpen)
    ON_COMMAND(ID_CLEAR_LIST, &CMainDlg::OnClearList)
    ON_COMMAND(ID_ANALYSE, &CMainDlg::OnAnalyse)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialogEx::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
    CRect ClientRect;
    GetClientRect(&ClientRect);
    if (!m_lcexMain.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT, ClientRect, this, 10001))
    {
        return -1;
    }
    return 0;
}


void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    if (m_lcexMain.m_hWnd != NULL)
    {
        m_lcexMain.Resize(cx, cy);
    }
}


void CMainDlg::OnFileOpen()
{
    // TODO: 在此添加命令处理程序代码
    CFileDialog dlg(TRUE, _T("Feel At Home"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("MS Word Documents (*.doc)|*.doc|"));
    if (dlg.DoModal() == IDOK)
    {
        m_recruitExpert.AddSingleResume(dlg.GetFileName(), dlg.GetFolderPath());
        m_lcexMain.UpdateResumes(m_recruitExpert.GetAllResumes());
    }
}


void CMainDlg::OnDirectoryOpen()
{
    // TODO: 在此添加命令处理程序代码
    CFolderDialog dlg(_T("从文件夹导入"), _T("C:\\"), this);
    if (dlg.DoModal() == IDOK)
    {
        m_recruitExpert.ImportResumes(dlg.GetFolderPath());
        m_lcexMain.UpdateResumes(m_recruitExpert.GetAllResumes());
    } 
}


void CMainDlg::OnClearList()
{
    // TODO: 在此添加命令处理程序代码
    m_recruitExpert.ClearResumes();
    m_lcexMain.DeleteAllItems();
}


void CMainDlg::OnAnalyse()
{
    // TODO: 在此添加命令处理程序代码
}
