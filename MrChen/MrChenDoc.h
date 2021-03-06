#ifndef CMrChenDoc_H
#define CMrChenDoc_H
// MrChenDoc.h: CMrChenDoc 类的接口
//


#pragma once

#include "Param.h"

class CMrChenDoc : public CDocument
{
protected: // 仅从序列化创建
	CMrChenDoc();
	DECLARE_DYNCREATE(CMrChenDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument(); //在启动时 会自动调用一次
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMrChenDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS


public:
	//保存在文件中的参数
	DeviParam  m_doc;

public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};

extern  CMrChenDoc * theDoc;
#endif