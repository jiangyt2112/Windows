
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


// CCapturerDlg �Ի���



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
	m_winTip.AddTool(GetDlgItem(IDOK), _T("����Ҫ��ӵ���ʾ��Ϣ")); //IDC_BUTTONΪ��Ҫ�����ʾ��Ϣ��LISTBOX��ID
	
	m_winTip.SetDelayTime(200); //�����ӳ�
	m_winTip.SetTipTextColor( RGB(0,0,255) ); //������ʾ�ı�����ɫ
	m_winTip.SetTipBkColor( RGB(255,255,255)); //������ʾ��ı�����ɫ
	m_winTip.Activate(TRUE); //�����Ƿ�������ʾ

	

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

	//CDialogEx::OnClose();
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
