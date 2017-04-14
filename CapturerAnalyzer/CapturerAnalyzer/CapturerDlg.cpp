
// CapturerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CapturerAnalyzer.h"
#include "CapturerDlg.h"
#include "afxdialogex.h"
#include "AnalyzerDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCapturerDlg �Ի���



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


// CCapturerDlg ��Ϣ�������

BOOL CCapturerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_winImageList.Create(18, 18, ILC_COLOR24 | ILC_MASK, 1, 1);           //����ͼ���б�


	m_winImageList.Add(AfxGetApp()->LoadIconW(IDI_START));                 //��ͼ���б������ͼ��  
	m_winImageList.Add(AfxGetApp()->LoadIconW(IDI_PAUSE));  
	m_winImageList.Add(AfxGetApp()->LoadIconW(IDI_CONTINUE));  
	m_winImageList.Add(AfxGetApp()->LoadIconW(IDI_STOP));  
	m_winImageList.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	UINT array[4];															//��������  
	
	array[0] = IDM_START;//IDM_START;													//Ϊ����Ԫ�ظ�ֵ  
	array[1] = IDM_PAUSE;
	array[2] = IDM_CONTINUE;
	array[3] = IDM_STOP;

	m_winToolBar.CreateEx(this, CCS_TOP|WS_CHILD|WS_VISIBLE|CCS_ADJUSTABLE|CBRS_TOOLTIPS);		                                         //��������������  
	

	m_winToolBar.SetButtons(array, 4);										//���ù�������ť������  
	m_winToolBar.SetSizes(CSize(34, 26), CSize(18, 18));	                //���ð�ť��ͼ���С  

	
	m_winToolBar.EnableToolTips(TRUE);
	m_winToolBar.GetToolBarCtrl().SetImageList(&m_winImageList);              //����ͼ���б�  
	

	m_winToolBar.ShowWindow(SW_SHOW);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);    //��ʾ������  


	m_winTip.Create(this); 
	//m_winTip.AddTool(GetDlgItem(IDOK), _T("����Ҫ��ӵ���ʾ��Ϣ")); //IDC_BUTTONΪ��Ҫ�����ʾ��Ϣ��LISTBOX��ID
	

	m_winTip.SetDelayTime(200); //�����ӳ�
	m_winTip.SetTipTextColor( RGB(0,0,255) ); //������ʾ�ı�����ɫ
	m_winTip.SetTipBkColor( RGB(255,255,255)); //������ʾ��ı�����ɫ
	m_winTip.Activate(TRUE); //�����Ƿ�������ʾ

	
	//����״̬��
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
	 //��ʾ״̬��
	CRect rect;
	GetWindowRect(rect);
	m_StatusBar.SetPaneInfo(0,indicators[0], SBPS_NORMAL, 70);//rect.Width()/3);
	m_StatusBar.SetPaneInfo(1,indicators[1], SBPS_STRETCH, 0);
	m_StatusBar.SetPaneInfo(2,indicators[2], SBPS_NORMAL, 150);
	m_StatusBar.SetPaneInfo(3,indicators[3], SBPS_NORMAL, 70);

	m_StatusBar.SetPaneText(0,_T("ժҪ"));
	m_StatusBar.SetPaneText(1,_T("״̬"));
	m_StatusBar.SetPaneText(2,_T("000"));

	// m_StatusBar.SetPaneStyle(0, RGB(0,64,128));//SetPaneBackgroundColor(0,RGB(0,64,128));
	CTime t1;
    t1=CTime::GetCurrentTime();
    m_StatusBar.SetPaneText(3,t1.Format("%H:%M:%S"));

	// m_StatusBar.GetStatusBarCtrl().SetBkColor(RGB(180,20,180));//���ñ���
	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	SetTimer(1,1000,NULL);
	
		//SetBKColor(RGB(180,180,180));
	// packets list
	 //CRect rect;   
  
    // ��ȡ�б���ͼ�ؼ���λ�úʹ�С   
    m_PacketList.GetClientRect(&rect);   
	//m_PacketList.SetExtendedStyle(LVS_EX_TRACKSELECT|LVS_EX_ONECLICKACTIVATE );
    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
    m_PacketList.SetExtendedStyle(m_PacketList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
  
	UINT nWidth = rect.Width() - 17;
    // Ϊ�б���ͼ�ؼ��������   
    m_PacketList.InsertColumn(0, _T("���"), LVCFMT_CENTER, 80, 0);   
    m_PacketList.InsertColumn(1, _T("ʱ��"), LVCFMT_CENTER, 140, 1);   
    m_PacketList.InsertColumn(2, _T("����"), LVCFMT_CENTER, 100, 2);
	m_PacketList.InsertColumn(3, _T("Դ��ַ"), LVCFMT_CENTER, 200, 3);
	m_PacketList.InsertColumn(4, _T("Ŀ�ĵ�ַ"), LVCFMT_CENTER, 200, 4);
	m_PacketList.InsertColumn(5, _T("Э��"), LVCFMT_CENTER, 143, 5);
	
	// �鿴��������������
	m_capturer.findHostAdapter();
	m_capturer.openAdapter(0);
	m_capturer.bindListCtrl(&m_PacketList);
	m_capturer.bindDlg(this);
	//m_capturer.start();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCapturerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCapturerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
void CCapturerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CMenu menu;       // �˵����������˵������Ӳ˵���   
    CMenu *pSubMenu;  // �Ҽ��˵�   
  
    // ���ز˵���Դ��menu����   
    menu.LoadMenu(IDR_MENU_POPUP);   
    // ��Ϊ�Ҽ��˵��ǵ���ʽ�˵������������˵���������ȡ�Ӳ˵�   
    pSubMenu = menu.GetSubMenu(0);   
    // ������ֵ�ɿͻ�����ת��Ϊ��Ļ����   
    ClientToScreen(&point);   
    // �����Ҽ��˵����˵������point.x����ֵ����   
    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);  

	CDialogEx::OnRButtonUp(nFlags, point);
}


void CCapturerDlg::OnAboutbox()
{
	// TODO: �ڴ���������������
}


//void CCapturerDlg::OnConfig()
//{
//	// TODO: �ڴ���������������
//}


void CCapturerDlg::OnConfigFilt()
{
	// TODO: �ڴ���������������
}


void CCapturerDlg::OnFileNew()
{
	// TODO: �ڴ���������������
}


void CCapturerDlg::OnFileOpen()
{
	// TODO: �ڴ���������������
}


void CCapturerDlg::OnFileQuit()
{
	// TODO: �ڴ���������������
}


void CCapturerDlg::OnFileSave()
{
	// TODO: �ڴ���������������
}


void CCapturerDlg::OnFileSaveas()
{
	// TODO: �ڴ���������������
}


void CCapturerDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	INT_PTR nRet = MessageBox(_T("ȷ���رճ���"), _T("�ر�"), MB_OKCANCEL);
	if (nRet == IDOK)
	{
		m_capturer.stop();
		CDialogEx::OnClose();
	}
}


void CCapturerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CCapturerDlg::OnPopupAna()
{
	// TODO: �ڴ���������������
	// ������������

}


BOOL CCapturerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_MOUSEMOVE )
		m_winTip.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CCapturerDlg::OnToolTipsNotify(UINT id, NMHDR* pNMHDR,LRESULT* pResult)
{
	TOOLTIPTEXT*pT =(TOOLTIPTEXT*)pNMHDR ; //��pNMHDRת����TOOLTIPTEXTָ����������

    UINT    nID =pNMHDR->idFrom ;  //��ȡ�������ϰ�ť��ID

	switch(nID)  //���nID��ϣ����ȡ��ID,��ô��������Ӧ��ʾ��Ϣ��TOOLTIPTEXT�ṹ���lpszText�С�
	{
	case IDM_START:
		pT->lpszText = _T("��ʼ����");
		break;
	case IDM_PAUSE:
		pT->lpszText = _T("��ͣ����");
		break;
	case IDM_CONTINUE:
		pT->lpszText = _T("��������");
		break;
	case IDM_STOP:
		pT->lpszText = _T("ֹͣ����");
		break;
	
	}
	return FALSE;
}


void CCapturerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTime t1;
    t1=CTime::GetCurrentTime();
    m_StatusBar.SetPaneText(3,t1.Format("%H:%M:%S"));
	CDialogEx::OnTimer(nIDEvent);
}


void CAboutDlg::OnIdsTime()
{
	// TODO: �ڴ���������������
	
}


void CCapturerDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	//::MessageBox(NULL, _T("aaaa"), _T("aaa"), IDOK);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCapturerDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CCapturerDlg::OnEnChangePacketdata()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CCapturerDlg::OnClickPacketlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	
	*pResult = 0;

	CString strLangName;    // ѡ�����Ե������ַ���   
    NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;   
  
    if (-1 != pNMListView->iItem)        // ���iItem����-1����˵�����б��ѡ��   
    {   
        // ��ȡ��ѡ���б����һ��������ı�   
        strLangName = m_PacketList.GetItemText(pNMListView->iItem, 0);   
        // ��ѡ���������ʾ��༭����   
        SetDlgItemText(IDC_PACKETDATA, strLangName);
		//m_PacketList.SetTextColor(RGB(65,22,245));
    }
}


void CCapturerDlg::OnDblclkPacketlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	*pResult = 0;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCapturerDlg::OnRclickPacketlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	*pResult = 0;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCapturerDlg::OnHoverPacketlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	m_PacketList.SetHotItem(1);
}


void CCapturerDlg::OnLvnItemchangedPacketlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
		*pResult = 0;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCapturerDlg::OnStart()
{
	// TODO: �ڴ���������������
	m_capturer.start();
	m_StatusBar.SetPaneText(1,_T("������"));
	//m_StatusBar.SetPaneText(2,_T("10"));
}


void CCapturerDlg::OnPause()
{
	// TODO: �ڴ���������������
	m_capturer.pause();
	m_StatusBar.SetPaneText(1,_T("��ͣ"));
}



void CCapturerDlg::OnContinue()
{
	// TODO: �ڴ���������������
	m_capturer.conti();
	m_StatusBar.SetPaneText(1,_T("������"));
}


void CCapturerDlg::OnStop()
{
	// TODO: �ڴ���������������
	m_capturer.stop();
}
