
#pragma once

#include "ViewTree.h"

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// 构造
public:
	CFileView();

	void AdjustLayout();
	void OnChangeVisualStyle();

// 特性
protected:

	CViewTree m_wndFileView; //树结构
	CImageList m_FileViewImages; //图像视图
	CFileViewToolBar m_wndToolBar;//工具栏

protected:
	void FillFileView();

// 实现
public:
	virtual ~CFileView();
	HTREEITEM  InsertFileView(CString fileName, HTREEITEM hSrc = NULL);
	HTREEITEM  InsertNodeView(CString strName, HTREEITEM hSrc = NULL);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//afx_msg void OnLButtonDblClk();

	DECLARE_MESSAGE_MAP()
public:

private:
	HTREEITEM m_hRoot;//树的根目录
};

