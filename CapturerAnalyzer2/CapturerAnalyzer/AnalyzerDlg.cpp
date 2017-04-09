// AnalyzerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CapturerAnalyzer.h"
#include "AnalyzerDlg.h"
#include "afxdialogex.h"


// CAnalyzerDlg 对话框

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
	ON_BN_CLICKED(IDOK, &CAnalyzerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAnalyzerDlg 消息处理程序


BOOL CAnalyzerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	return TRUE;  // return TRUE unless you set the focus to a control

}


void CAnalyzerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
