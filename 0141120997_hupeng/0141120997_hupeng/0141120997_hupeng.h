
// 0141120997_hupeng.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy0141120997_hupengApp:
// �йش����ʵ�֣������ 0141120997_hupeng.cpp
//

class CMy0141120997_hupengApp : public CWinApp
{
public:
	CMy0141120997_hupengApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy0141120997_hupengApp theApp;