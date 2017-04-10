#include "ToolBarEx.h"
// CapturerDlg.h : 头文件
//

#pragma once

// CCapturerDlg 对话框
class CCapturerDlg : public CDialogEx
{
// 构造
public:
	CCapturerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CAPTURERANALYZER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	CImageList m_winImageList;             //列表视图对象  
	CToolTipCtrl     m_winTip;
	CReBar m_rebar;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
};
