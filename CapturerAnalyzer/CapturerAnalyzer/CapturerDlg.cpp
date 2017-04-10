
// CapturerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CapturerAnalyzer.h"
#include "CapturerDlg.h"
#include "afxdialogex.h"
#include "AnalyzerDlg.h"


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


// CCapturerDlg 对话框



CCapturerDlg::CCapturerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCapturerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_CAPTURER);
	
}

void CCapturerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCapturerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCapturerDlg::OnBnClickedOk)
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_ABOUTBOX, &CCapturerDlg::OnAboutbox)
//	ON_COMMAND(IDM_CONFIG, &CCapturerDlg::OnConfig)
	ON_COMMAND(IDM_CONFIG_FILT, &CCapturerDlg::OnConfigFilt)
	ON_COMMAND(IDM_FILE_NEW, &CCapturerDlg::OnFileNew)
	ON_COMMAND(IDM_FILE_OPEN, &CCapturerDlg::OnFileOpen)
	ON_COMMAND(IDM_FILE_QUIT, &CCapturerDlg::OnFileQuit)
	ON_COMMAND(IDM_FILE_SAVE, &CCapturerDlg::OnFileSave)
	ON_COMMAND(IDM_FILE_SAVEAS, &CCapturerDlg::OnFileSaveas)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &CCapturerDlg::OnBnClickedCancel)
	ON_COMMAND(IDM_POPUP_ANA, &CCapturerDlg::OnPopupAna)
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,OnToolTipsNotify)
END_MESSAGE_MAP()


// CCapturerDlg 消息处理程序

BOOL CCapturerDlg::OnInitDialog()
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
	m_winImageList.Create(18, 18, ILC_COLOR24 | ILC_MASK, 1, 1);           //创建图像列表


	m_winImageList.Add(AfxGetApp()->LoadIconW(IDI_START));                 //向图像列表中添加图标  
	m_winImageList.Add(AfxGetApp()->LoadIconW(IDI_PAUSE));  
	m_winImageList.Add(AfxGetApp()->LoadIconW(IDI_CONTINUE));  
	m_winImageList.Add(AfxGetApp()->LoadIconW(IDI_STOP));  
	m_winImageList.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	UINT array[4];															//声明数组  
	
	array[0] = IDM_START;//IDM_START;													//为数组元素赋值  
	array[1] = IDM_PAUSE;
	array[2] = IDM_CONTINUE;
	array[3] = IDM_STOP;

	m_winToolBar.CreateEx(this, CCS_TOP|WS_CHILD|WS_VISIBLE|CCS_ADJUSTABLE|CBRS_TOOLTIPS);		                                         //创建工具栏窗口  
	

	m_winToolBar.SetButtons(array, 4);										//设置工具栏按钮的索引  
	m_winToolBar.SetSizes(CSize(34, 26), CSize(18, 18));	                //设置按钮和图标大小  

	
	m_winToolBar.EnableToolTips(TRUE);
	m_winToolBar.GetToolBarCtrl().SetImageList(&m_winImageList);              //关联图像列表  
	

	m_winToolBar.ShowWindow(SW_SHOW);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);    //显示工具栏  
	//m_winToolBar.MoveWindow(CRect(CPoint(1, 25), CSize(612, 45)));
	

	/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT,  WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS,
        CRect(4,4,4,4)) || !m_wndToolBar.LoadToolBar(IDR_TOOLBAR_MAIN))
    {
        TRACE0("failed to create toolbar\n");
        return FALSE;
    }
	// SIZE size = {24, 24};
	// m_wndToolBar.SetSizes(size, size);
    m_wndToolBar.ShowWindow(SW_SHOW);
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	*/

	m_winTip.Create(this); 
	m_winTip.AddTool(GetDlgItem(IDOK), _T("你想要添加的提示信息")); //IDC_BUTTON为你要添加提示信息的LISTBOX的ID
	
	m_winTip.SetDelayTime(200); //设置延迟
	m_winTip.SetTipTextColor( RGB(0,0,255) ); //设置提示文本的颜色
	m_winTip.SetTipBkColor( RGB(255,255,255)); //设置提示框的背景颜色
	m_winTip.Activate(TRUE); //设置是否启用提示

	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCapturerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCapturerDlg::OnPaint()
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
HCURSOR CCapturerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCapturerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CAnalyzerDlg* dlg = new CAnalyzerDlg();
	//dlg.DoModal();
	INT_PTR nResponse = dlg->Create(IDD_ANALYZER, GetDesktopWindow());
	dlg->ShowWindow(SW_NORMAL);
	//CDialogEx::OnOK();
	//IDOK;
}


void CCapturerDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CMenu menu;       // 菜单（包含主菜单栏和子菜单）   
    CMenu *pSubMenu;  // 右键菜单   
  
    // 加载菜单资源到menu对象   
    menu.LoadMenu(IDR_MENU_POPUP);   
    // 因为右键菜单是弹出式菜单，不包含主菜单栏，所以取子菜单   
    pSubMenu = menu.GetSubMenu(0);   
    // 将坐标值由客户坐标转换为屏幕坐标   
    ClientToScreen(&point);   
    // 弹出右键菜单，菜单左侧与point.x坐标值对齐   
    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);  

	CDialogEx::OnRButtonUp(nFlags, point);
}


void CCapturerDlg::OnAboutbox()
{
	// TODO: 在此添加命令处理程序代码
}


//void CCapturerDlg::OnConfig()
//{
//	// TODO: 在此添加命令处理程序代码
//}


void CCapturerDlg::OnConfigFilt()
{
	// TODO: 在此添加命令处理程序代码
}


void CCapturerDlg::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
}


void CCapturerDlg::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
}


void CCapturerDlg::OnFileQuit()
{
	// TODO: 在此添加命令处理程序代码
}


void CCapturerDlg::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
}


void CCapturerDlg::OnFileSaveas()
{
	// TODO: 在此添加命令处理程序代码
}


void CCapturerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
}


void CCapturerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CCapturerDlg::OnPopupAna()
{
	// TODO: 在此添加命令处理程序代码
	// 创建分析窗口

}


BOOL CCapturerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_MOUSEMOVE )
		m_winTip.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CCapturerDlg::OnToolTipsNotify(UINT id, NMHDR* pNMHDR,LRESULT* pResult)
{
	TOOLTIPTEXT*pT =(TOOLTIPTEXT*)pNMHDR ; //将pNMHDR转换成TOOLTIPTEXT指针类型数据

    UINT    nID =pNMHDR->idFrom ;  //获取工具条上按钮的ID

	switch(nID)  //如果nID是希望获取的ID,那么就设置相应提示信息到TOOLTIPTEXT结构体的lpszText中。
	{
	case IDM_START:
		pT->lpszText = _T("开始捕获");
		break;
	case IDM_PAUSE:
		pT->lpszText = _T("暂停捕获");
		break;
	case IDM_CONTINUE:
		pT->lpszText = _T("继续捕获");
		break;
	case IDM_STOP:
		pT->lpszText = _T("停止捕获");
		break;
	}
	return FALSE;
}
