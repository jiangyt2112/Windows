#pragma once


// CAnalyzerDlg 对话框

class CAnalyzerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnalyzerDlg)

public:
	CAnalyzerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAnalyzerDlg();

// 对话框数据
	enum { IDD = IDD_ANALYZER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	HICON m_hIcon;
};
