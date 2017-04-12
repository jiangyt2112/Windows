// StatusBarEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CapturerAnalyzer.h"
#include "StatusBarEx.h"


// CStatusBarEx

IMPLEMENT_DYNAMIC(CStatusBarEx, CStatusBar)

CStatusBarEx::CStatusBarEx()
{

}

CStatusBarEx::~CStatusBarEx()
{
}


BEGIN_MESSAGE_MAP(CStatusBarEx, CStatusBar)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CStatusBarEx ��Ϣ�������




BOOL CStatusBarEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CRect rect;

	//GetClientRect(&rect);
	//GetItemRect(0, &rect);
	//pDC->FillSolidRect(rect, RGB(180, 180, 180));

	//return TRUE;
	return CStatusBar::OnEraseBkgnd(pDC);
}


void CStatusBarEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	RECT rect;
	GetItemRect(0, &rect);
	wchar_t buf[32];
	wsprintf(buf, _T("ͳ����Ϣ����"));//, rect.top, rect.bottom, rect.left, rect.right, point.x, point.y);
	if (point.x <= rect.right && point.x >= rect.left && point.y <= rect.bottom && point.y >= rect.top)
	{
		CWnd* hwnd = GetParent();
		::MessageBox(hwnd->m_hWnd, buf, buf, IDOK);
	}
	//::MessageBox(NULL, buf, buf, IDOK);

	CStatusBar::OnLButtonDown(nFlags, point);
}
