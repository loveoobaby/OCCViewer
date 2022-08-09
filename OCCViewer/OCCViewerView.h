
// OCCViewerView.h: COCCViewerView 类的接口
//

#pragma once
#include "Occheaders.h"

class COCCViewerView : public CView, public AIS_ViewController
{
protected: // 仅从序列化创建
	COCCViewerView() noexcept;
	DECLARE_DYNCREATE(COCCViewerView)

// 特性
public:
	COCCViewerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	Handle(AIS_InteractiveContext)& GetAISContext() { return myAISContext; };
	void UpdateOCCView();
protected:
	Handle(V3d_View)                myView;
	Handle(Graphic3d_GraphicDriver) myGraphicDevice;
	Handle(V3d_Viewer)              myViewer;
	Handle(AIS_InteractiveContext)  myAISContext;
	Aspect_TypeOfTriedronPosition   Position;
	double	                        m_TrihedronScale;
	Quantity_NameOfColor            Color;
	COLORREF                        m_BackGroundColor;
	unsigned int                    myUpdateRequests;

	// Create View
	bool CreateView();
	void OnShadedEdges();
	void SetupAISTrihedron();
	void ShowAISTrihedron(bool bOn);
	void SetupCsys();

// 实现
public:
	virtual ~COCCViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif



protected:
	bool bShowCube = false;
	bool bSetTransparent = false;
	bool bShowCsys = true;
	bool bShowAISTrihedron = true;

	Handle(AIS_ViewCube)        aVCube;
	Handle(Prs3d_LineAspect)    aEdgeAspt;		// Face boundary Aspect
	Handle(Geom_Axis2Placement) aXPl;
	Handle(AIS_Axis)            aXaxis, aYaxis, aZaxis;
	Handle(AIS_Trihedron)       aTrihedron;

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // OCCViewerView.cpp 中的调试版本
inline COCCViewerDoc* COCCViewerView::GetDocument() const
   { return reinterpret_cast<COCCViewerDoc*>(m_pDocument); }
#endif

