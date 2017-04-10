#pragma once
#include "afxext.h"
class CToolBarEx :
	public CToolBar
{
	DECLARE_DYNAMIC(CToolBarEx)
public:
	CToolBarEx(void);
	~CToolBarEx(void);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

