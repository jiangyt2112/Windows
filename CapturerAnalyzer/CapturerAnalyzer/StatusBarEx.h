#pragma once


// CStatusBarEx

class CStatusBarEx : public CStatusBar
{
	DECLARE_DYNAMIC(CStatusBarEx)

public:
	CStatusBarEx();
	virtual ~CStatusBarEx();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


