
// MrChen.h: MrChen 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "CFindFile.h"
#include "Param.h"

// CMrChenApp:
// 有关此类的实现，请参阅 MrChen.cpp
//

class CMrChenApp : public CWinAppEx
{
public:
	CMrChenApp();
public:
	static PPARAM  m_param;
	static CString  m_strAppPath;
	PDEVIPARAM    m_curDevi;

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	BOOL  LoadConfig();
	BOOL  SaveConfig();
// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	//afx_msg void OnFileNew();
	virtual BOOL OnIdle(LONG lCount);
private:
	void InitilizationApp();
private:
	
	CFile    m_iniFile;
	
};

extern CMrChenApp theApp;
