
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
public:
	afx_msg void OnIdsTime();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(IDS_TIME, &CAboutDlg::OnIdsTime)
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
	DDX_Control(pDX, IDC_PACKETLIST, m_PacketList);
	DDX_Control(pDX, IDC_PACKETDATA, m_PACKETDATA);
}

BEGIN_MESSAGE_MAP(CCapturerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDOK, &CCapturerDlg::OnBnClickedOk)
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
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_PACKETDATA, &CCapturerDlg::OnEnChangePacketdata)
	ON_NOTIFY(NM_CLICK, IDC_PACKETLIST, &CCapturerDlg::OnClickPacketlist)
	ON_NOTIFY(NM_DBLCLK, IDC_PACKETLIST, &CCapturerDlg::OnDblclkPacketlist)
	ON_NOTIFY(NM_RCLICK, IDC_PACKETLIST, &CCapturerDlg::OnRclickPacketlist)
	ON_NOTIFY(NM_HOVER, IDC_PACKETLIST, &CCapturerDlg::OnHoverPacketlist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PACKETLIST, &CCapturerDlg::OnLvnItemchangedPacketlist)
	ON_COMMAND(IDM_START, &CCapturerDlg::OnStart)
	ON_COMMAND(IDM_PAUSE, &CCapturerDlg::OnPause)
	ON_COMMAND(IDM_CONTINUE, &CCapturerDlg::OnContinue)
	ON_COMMAND(IDM_STOP, &CCapturerDlg::OnStop)
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


	m_winTip.Create(this); 
	//m_winTip.AddTool(GetDlgItem(IDOK), _T("你想要添加的提示信息")); //IDC_BUTTON为你要添加提示信息的LISTBOX的ID
	

	m_winTip.SetDelayTime(200); //设置延迟
	m_winTip.SetTipTextColor( RGB(0,0,255) ); //设置提示文本的颜色
	m_winTip.SetTipBkColor( RGB(255,255,255)); //设置提示框的背景颜色
	m_winTip.Activate(TRUE); //设置是否启用提示

	
	//创建状态栏
	static UINT BASED_CODE indicators[]=  
	{
		IDS_DIGEST,
		IDS_STATUS,
		IDS_PACKETS,
		IDS_TIME
	};  

	m_StatusBar.CreateEx(this, SBT_TOOLTIPS,/*WS_CHILD |*/ WS_VISIBLE | CBRS_BOTTOM,AFX_IDW_STATUS_BAR);
	m_StatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// m_StatusBar.GetStatusBarCtrl().SetBkColor(RGB(222,0,0));
	 //显示状态栏
	CRect rect;
	GetWindowRect(rect);
	m_StatusBar.SetPaneInfo(0,indicators[0], SBPS_NORMAL, 70);//rect.Width()/3);
	m_StatusBar.SetPaneInfo(1,indicators[1], SBPS_STRETCH, 0);
	m_StatusBar.SetPaneInfo(2,indicators[2], SBPS_NORMAL, 150);
	m_StatusBar.SetPaneInfo(3,indicators[3], SBPS_NORMAL, 70);

	m_StatusBar.SetPaneText(0,_T("摘要"));
	m_StatusBar.SetPaneText(1,_T("状态"));
	m_StatusBar.SetPaneText(2,_T("000"));

	// m_StatusBar.SetPaneStyle(0, RGB(0,64,128));//SetPaneBackgroundColor(0,RGB(0,64,128));
	CTime t1;
    t1=CTime::GetCurrentTime();
    m_StatusBar.SetPaneText(3,t1.Format("%H:%M:%S"));

	// m_StatusBar.GetStatusBarCtrl().SetBkColor(RGB(180,20,180));//设置背景
	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	SetTimer(1,1000,NULL);
	
		//SetBKColor(RGB(180,180,180));
	// packets list
	 //CRect rect;   
  
    // 获取列表视图控件的位置和大小   
    m_PacketList.GetClientRect(&rect);   
	//m_PacketList.SetExtendedStyle(LVS_EX_TRACKSELECT|LVS_EX_ONECLICKACTIVATE );
    // 为列表视图控件添加全行选中和栅格风格   
    m_PacketList.SetExtendedStyle(m_PacketList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
  
	UINT nWidth = rect.Width() - 17;
    // 为列表视图控件添加三列   
    m_PacketList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 80, 0);   
    m_PacketList.InsertColumn(1, _T("时间"), LVCFMT_CENTER, 140, 1);   
    m_PacketList.InsertColumn(2, _T("长度"), LVCFMT_CENTER, 100, 2);
	m_PacketList.InsertColumn(3, _T("源地址"), LVCFMT_CENTER, 200, 3);
	m_PacketList.InsertColumn(4, _T("目的地址"), LVCFMT_CENTER, 200, 4);
	m_PacketList.InsertColumn(5, _T("协议"), LVCFMT_CENTER, 143, 5);
	
	// 查看主机可用适配器
	m_capturer.findHostAdapter();
	m_capturer.openAdapter(0);
	m_capturer.bindListCtrl(&m_PacketList);
	m_capturer.bindDlg(this);
	//m_capturer.start();

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


/*
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
*/

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
	INT_PTR nRet = MessageBox(_T("确定关闭程序？"), _T("关闭"), MB_OKCANCEL);
	if (nRet == IDOK)
	{
		m_capturer.stop();
		CDialogEx::OnClose();
	}
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


void CCapturerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime t1;
    t1=CTime::GetCurrentTime();
    m_StatusBar.SetPaneText(3,t1.Format("%H:%M:%S"));
	CDialogEx::OnTimer(nIDEvent);
}


void CAboutDlg::OnIdsTime()
{
	// TODO: 在此添加命令处理程序代码
	
}


void CCapturerDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RECT rect;
	m_StatusBar.GetStatusBarCtrl().GetRect(0, &rect);
	if (point.x <= rect.right && point.x >= rect.left && point.y >= rect.bottom && point.y <= rect.top)
	{
		::MessageBox(NULL, _T("aaaa"), _T("aaa"), IDOK);
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CCapturerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	//::MessageBox(NULL, _T("aaaa"), _T("aaa"), IDOK);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCapturerDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


	// TODO:  在此添加控件通知处理程序代码
}


void CCapturerDlg::OnEnChangePacketdata()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


	// TODO:  在此添加控件通知处理程序代码
}


void CCapturerDlg::OnClickPacketlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	
	*pResult = 0;

	CString strLangName;    // 选择语言的名称字符串   
    NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;   
  
    if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
    {   
        // 获取被选择列表项第一个子项的文本   
        strLangName = m_PacketList.GetItemText(pNMListView->iItem, 0);   
        // 将选择的语言显示与编辑框中   
        SetDlgItemText(IDC_PACKETDATA, strLangName);
		//m_PacketList.SetTextColor(RGB(65,22,245));
    }
}


void CCapturerDlg::OnDblclkPacketlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCapturerDlg::OnRclickPacketlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCapturerDlg::OnHoverPacketlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	m_PacketList.SetHotItem(1);
}


void CCapturerDlg::OnLvnItemchangedPacketlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
		*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCapturerDlg::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	m_capturer.start();
	m_StatusBar.SetPaneText(1,_T("捕获中"));
	//m_StatusBar.SetPaneText(2,_T("10"));
}


void CCapturerDlg::OnPause()
{
	// TODO: 在此添加命令处理程序代码
	m_capturer.pause();
	m_StatusBar.SetPaneText(1,_T("暂停"));
}



void CCapturerDlg::OnContinue()
{
	// TODO: 在此添加命令处理程序代码
	m_capturer.conti();
	m_StatusBar.SetPaneText(1,_T("捕获中"));
}


void CCapturerDlg::OnStop()
{
	// TODO: 在此添加命令处理程序代码
	m_capturer.stop();
}
