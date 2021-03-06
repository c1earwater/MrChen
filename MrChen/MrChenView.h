
// MrChenView.h: CMrChenView 类的接口
//

#pragma once

#include "MainFrm.h"

#include "CWndMain.h"
#include "CWndConfig.h"
#include "CWndCtrl.h"
#include "CWndMyListCell.h"
class CMrChenView : public CView
{
protected: // 仅从序列化创建
	CMrChenView();
	DECLARE_DYNCREATE(CMrChenView)

// 特性
public:
	CMrChenDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMrChenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CWndConfig  m_wndConfig;
	CWndMain    m_wndMain;

	CWndMyListCell  m_Actlist;


// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnChanegView(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChangeSize(WPARAM wParm, LPARAM lParam);
	afx_msg LRESULT OnUpdateView(WPARAM wParm, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDeviceNew();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	void AdjustLayout();
public:
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // MrChenView.cpp 中的调试版本
inline CMrChenDoc* CMrChenView::GetDocument() const
   { return reinterpret_cast<CMrChenDoc*>(m_pDocument); }
#endif

