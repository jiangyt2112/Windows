#include "stdafx.h"
#include "ToolBarEx.h"

IMPLEMENT_DYNAMIC(CToolBarEx, CToolBar)

CToolBarEx::CToolBarEx(void)
{
}


CToolBarEx::~CToolBarEx(void)
{
}
BEGIN_MESSAGE_MAP(CToolBarEx, CToolBar)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CToolBarEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rectClient;  
	GetClientRect(rectClient);  
	pDC->FillSolidRect(rectClient, 0xCBCBCB);//RGB(205,205,0));
	//return CToolBar::OnEraseBkgnd(pDC);
	return true;
}
