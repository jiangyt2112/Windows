// AnalyzerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CapturerAnalyzer.h"
#include "AnalyzerDlg.h"
#include "afxdialogex.h"


// CAnalyzerDlg �Ի���

IMPLEMENT_DYNAMIC(CAnalyzerDlg, CDialogEx)

CAnalyzerDlg::CAnalyzerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAnalyzerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ANALYZER);
}

CAnalyzerDlg::~CAnalyzerDlg()
{
}

void CAnalyzerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAnalyzerDlg, CDialogEx)
END_MESSAGE_MAP()


// CAnalyzerDlg ��Ϣ�������


BOOL CAnalyzerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  // return TRUE unless you set the focus to a control
}
