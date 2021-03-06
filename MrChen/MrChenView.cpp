
// MrChenView.cpp: CMrChenView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MrChen.h"
#endif
#include "Param.h"
#include "MrChenDoc.h"
#include "MrChenView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMrChenView

IMPLEMENT_DYNCREATE(CMrChenView, CView)

BEGIN_MESSAGE_MAP(CMrChenView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMrChenView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DEVICE_NEW, &CMrChenView::OnDeviceNew)
	ON_MESSAGE(WM_SWITCH_VIEW,&CMrChenView::OnChanegView)
	//ON_MESSAGE(WM_SIZE_CHANGE,&CMrChenView::OnChangeSize)
	//ON_MESSAGE(WM_UPDATE_UI, &CMrChenView::OnUpdateView)

	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMrChenView 构造/析构

CMrChenView::CMrChenView()
{
	// TODO: 在此处添加构造代码

}

CMrChenView::~CMrChenView()
{
}

BOOL CMrChenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMrChenView 绘图

void CMrChenView::OnDraw(CDC* pDC)
{
	CMrChenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CPaintDC dc(this);
	CRect   rect;
	GetClientRect(&rect);



	//CDC   MemDC;
	//CBitmap   MemBmp;
	//MemDC.CreateCompatibleDC(&dc);
	//MemBmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	//MemDC.SelectObject(&MemBmp);

	//DefWindowProc(WM_PAINT, (WPARAM)MemDC.m_hDC, (LPARAM)0); //将所有的WM_PAINT 绘制的东西放入memdc 中

	//dc.BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
	//MemDC.DeleteDC();
	//MemBmp.DeleteObject();

	// TODO: 在此处为本机数据添加绘制代码
}


// CMrChenView 打印


void CMrChenView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMrChenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMrChenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMrChenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMrChenView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMrChenView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

LRESULT CMrChenView::OnChanegView(WPARAM wParam, LPARAM lParam)
{
	UINT nID = (UINT)wParam;
	m_wndMain.ShowPane(nID == IDW_WND_MAIN);
	m_wndConfig.ShowPane(nID == IDW_WND_CONFIG);
	return LRESULT(0);
}

LRESULT CMrChenView::OnChangeSize(WPARAM wParm, LPARAM lParam)
{
	AdjustLayout();
	return LRESULT(0);
}

LRESULT CMrChenView::OnUpdateView(WPARAM wParm, LPARAM lParam)
{
	return LRESULT();
}


// CMrChenView 诊断

#ifdef _DEBUG
void CMrChenView::AssertValid() const
{
	CView::AssertValid();
}

void CMrChenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMrChenDoc* CMrChenView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMrChenDoc)));
	return (CMrChenDoc*)m_pDocument;
}
#endif //_DEBUG


// CMrChenView 消息处理程序


void CMrChenView::OnDeviceNew()
{
	// TODO: 在此添加命令处理程序代码
	OnChanegView(IDW_WND_CONFIG, 0);
}


int CMrChenView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO:  在此添加您专用的创建代码

	
	//BOOL  bl = m_wndMain.Create(WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, CRect(0, 0, 560, 40), this, IDW_WND_MAIN);
	
	byte  by;

	//m_selTest.Create(_T("测试"), by, WS_CHILD | WS_VISIBLE, CRect(100, 100, 430, 150), this, 0);

	m_Actlist.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_THICKFRAME, CRect(400, 10, 800, 300), this, 0);
	return 0;
}



void CMrChenView::AdjustLayout()
{
	if (m_wndMain.GetSafeHwnd() == nullptr)
	{
		return;
	}
	
	CRect rectClient;
	GetClientRect(rectClient);
	m_wndMain.MoveWindow(rectClient);

}


void CMrChenView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CView::OnPaint()
	//AdjustLayout();
	
}
