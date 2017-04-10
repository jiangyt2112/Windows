#include "ToolBarEx.h"
// CapturerDlg.h : ͷ�ļ�
//

#pragma once

// CCapturerDlg �Ի���
class CCapturerDlg : public CDialogEx
{
// ����
public:
	CCapturerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CAPTURERANALYZER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAboutbox();
//	afx_msg void OnConfig();
	afx_msg void OnConfigFilt();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileQuit();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveas();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPopupAna();
	afx_msg BOOL OnToolTipsNotify(UINT id,NMHDR * pNMHDR,LRESULT* pResult);
protected:
	CToolBarEx  m_winToolBar;
	CImageList m_winImageList;             //�б���ͼ����  
	CToolTipCtrl     m_winTip;
	CReBar m_rebar;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
};
