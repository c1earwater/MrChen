#pragma once

#include "CWndBase.h"
#include "MrChenDoc.h"
#include "MainFrm.h"
#include "CWndCtrl.h" 

class CWndMain : public CWndBase
{
	DECLARE_DYNAMIC(CWndMain)

public:
	CWndMain();
	virtual ~CWndMain();

	BOOL  Create(DWORD dwStyle, const RECT & rect, CWnd * pParentWnd, UINT nID);

	void ShowPane(bool bShow);
	
protected:
	DECLARE_MESSAGE_MAP()


	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMybuttonClk(UINT nID);
private:
	CWndMySelBox  m_selTest;
	CWndMyEditCell m_editTest;
	CWndMyBtnCell  m_btnTest;
public:
	afx_msg void OnPaint();

	
};

