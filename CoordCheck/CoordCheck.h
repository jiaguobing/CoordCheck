
// CoordCheck.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCoordCheckApp: 
// �йش����ʵ�֣������ CoordCheck.cpp
//

class CCoordCheckApp : public CWinApp
{
public:
	CCoordCheckApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCoordCheckApp theApp;