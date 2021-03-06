
#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList 窗口

#ifdef _DEBUG
#define LIST_MAX_NUM  10
#else
#define LIST_MAX_NUM   10 
#endif
class COutputList : public CListBox
{

// 构造
public:
	COutputList();

// 实现
public:
	virtual ~COutputList();

	virtual int AddString(LPCTSTR lpszItem); //重载
	
public:
	
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnViewOutput();
	afx_msg void OnEditClear();
	
	//清除最开始的30
	void  ClearEdit(int  num = 0);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnCtrlPause();
private:
	int m_nCount;
	bool m_bPause;
public:
	afx_msg void OnCtrlClear();
	afx_msg void OnCtrlGoon();
	afx_msg void OnUpdateCtrlState(CCmdUI *pCmdUI);
};

class COutputWnd : public CDockablePane
{
// 构造
public:
	COutputWnd();

	void UpdateFonts();
	void AddStringToBuildWindow(CString str);
	void ClearBuildWindow();

// 特性
protected:
	CMFCTabCtrl	m_wndTabs;
	
	COutputList m_wndOutputBuild;
//	COutputList m_wndOutputDebug; // 调栈
//	COutputList m_wndOutputFind; //查找
	
protected:

	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();

	void AdjustHorzScroll(CListBox& wndListBox);

// 实现
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
private:

public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};

