
// CapturerAnalyzer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCapturerAnalyzerApp:
// �йش����ʵ�֣������ CapturerAnalyzer.cpp
//

class CCapturerAnalyzerApp : public CWinApp
{
public:
	CCapturerAnalyzerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCapturerAnalyzerApp theApp;