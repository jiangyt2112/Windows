#pragma once


// CAnalyzerDlg �Ի���

class CAnalyzerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnalyzerDlg)

public:
	CAnalyzerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAnalyzerDlg();

// �Ի�������
	enum { IDD = IDD_ANALYZER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	HICON m_hIcon;
};
