#include "ToolBarEx.h"
#include "StatusBarEx.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "PacketCapturer.h"
// CapturerDlg.h : ͷ�ļ�
//
#define IDD_CAPTURERANALYZER_DIALOG 102
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
	CStatusBarEx m_StatusBar;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeEdit2();
protected:
	CListCtrl m_PacketList;
public:
	afx_msg void OnEnChangePacketdata();
	afx_msg void OnClickPacketlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkPacketlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickPacketlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHoverPacketlist(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_PACKETDATA;
	afx_msg void OnLvnItemchangedPacketlist(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	CPacketCapturer m_capturer;
public:
	afx_msg void OnStart();
	afx_msg void OnPause();
	afx_msg void OnContinue();
	afx_msg void OnStop();
};
