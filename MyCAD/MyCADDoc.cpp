
// MyCADDoc.cpp: CMyCADDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyCAD.h"
#endif

#include "MyCADDoc.h"

#include <propkey.h>

#include "MyCADView.h"


// CMyCADDoc

IMPLEMENT_DYNCREATE(CMyCADDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyCADDoc, CDocument)
	ON_COMMAND(ID_CREATE2DGEOM_2DSTRACTH, &CMyCADDoc::OnCreate2dgeom2dstracth)
END_MESSAGE_MAP()


// CMyCADDoc 构造/析构

CMyCADDoc::CMyCADDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CMyCADDoc::~CMyCADDoc()
{
}

BOOL CMyCADDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMyCADDoc 序列化

void CMyCADDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMyCADDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMyCADDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMyCADDoc::SetSearchContent(const CString& value)
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

// CMyCADDoc 诊断

#ifdef _DEBUG
void CMyCADDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyCADDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyCADDoc 命令

CMyCADView* CMyCADDoc::GetView()
{
	POSITION pos = GetFirstViewPosition();
	return (CMyCADView*)GetNextView(pos);
}

void CMyCADDoc::OnCreate2dgeom2dstracth()
{
	// TODO: 在此添加命令处理程序代码
    GetView()->ClearContext(true);
	Create2DGeometry();
	DisplaySketch();
}

void CMyCADDoc::DisplaySketch()
{
	if (bIs2d)
	{
		// Display 2d Curves
		for (int i = Curves2d.Lower(); i <= Curves2d.Upper(); i++)
		{
			Handle(Geom2d_Curve) L = Curves2d.Value(i);
			GetView()->DisplayCurve(L, Aspect_TOL_SOLID, Aspect_WOL_VERYTHICK, Quantity_NOC_DARKGREEN, Standard_False);
		}

		// Display 2d Points
		int cnt = 1;
		for (int i = Pnts2d.Lower(); i <= Pnts2d.Upper(); i++)
		{
			gp_Pnt2d P = Pnts2d.Value(i);
			GetView()->DisplayPoint(P);
			std::string PointName = "P" + std::to_string(cnt);
			GetView()->DisplayText(P, PointName.c_str());
			cnt += 1;
		}
	}
	else
	{
		// Display 3d Curves
		for (int i = Curves3d.Lower(); i <= Curves3d.Upper(); i++)
		{
			Handle(Geom_Curve) L = Curves3d.Value(i);
			GetView()->DisplayCurve(L, Quantity_NOC_DARKSLATEBLUE, Standard_False);
		}

		// Display 3d Points
		int cnt = 1;
		for (int i = Pnts3d.Lower(); i <= Pnts3d.Upper(); i++)
		{
			gp_Pnt P = Pnts3d.Value(i);
			GetView()->DisplayPoint(P);
			std::string PointName = "P" + std::to_string(cnt);
			GetView()->DisplayText(P, PointName.c_str());
			cnt += 1;
		}
	}
}
