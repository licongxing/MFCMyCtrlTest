
// MFCMyCtrlTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCMyCtrlTestApp:
// �йش����ʵ�֣������ MFCMyCtrlTest.cpp
//

class CMFCMyCtrlTestApp : public CWinApp
{
public:
	CMFCMyCtrlTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCMyCtrlTestApp theApp;