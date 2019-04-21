
// MrChenDoc.cpp: CMrChenDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MrChen.h"
#endif

#include "MrChenDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMrChenDoc

IMPLEMENT_DYNCREATE(CMrChenDoc, CDocument)

BEGIN_MESSAGE_MAP(CMrChenDoc, CDocument)
END_MESSAGE_MAP()


// CMrChenDoc 构造/析构

CMrChenDoc::CMrChenDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMrChenDoc::~CMrChenDoc()
{
}

BOOL CMrChenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMrChenDoc 序列化

void CMrChenDoc::Serialize(CArchive& ar)
{
	theApp.m_curDevi = &m_doc;

	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		ar << CMrChenApp::m_param->m_VerNum;
		ar << m_doc.nType;


	}
	else //从文档中读取
	{
		// TODO: 在此添加加载代码

		//PDEVIPARAM  pDoc = new DeviParam();
		int nVer ;
		ar >> nVer;
		if (nVer > CMrChenApp::m_param->m_VerNum)
		{
			AfxMessageBox(_T("打开文档版本不符"));
			return;
		}
		INT a;
		ar >> a;//(DeviParam::eDeviType)m_doc.nType;

	}

	
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMrChenDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMrChenDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMrChenDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMrChenDoc 诊断

#ifdef _DEBUG
void CMrChenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMrChenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMrChenDoc 命令

BOOL CMrChenDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码

	

	return TRUE;
}


BOOL CMrChenDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDocument::OnSaveDocument(lpszPathName);
}
