
// OCCViewerView.cpp: COCCViewerView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OCCViewer.h"
#endif

#include "OCCViewerDoc.h"
#include "OCCViewerView.h"



// COCCViewerView

IMPLEMENT_DYNCREATE(COCCViewerView, CView)

BEGIN_MESSAGE_MAP(COCCViewerView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// COCCViewerView 构造/析构

COCCViewerView::COCCViewerView() noexcept
{
	// TODO: 在此处添加构造代码

}

COCCViewerView::~COCCViewerView()
{
}

BOOL COCCViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

bool COCCViewerView::CreateView()
{
	try
	{
		// Graphic Connection
		Handle(Aspect_DisplayConnection) aDisplayConnection;
		myGraphicDevice = new OpenGl_GraphicDriver(aDisplayConnection);

		// Graphic Driver
		Handle(OpenGl_GraphicDriver) aDriver = Handle(OpenGl_GraphicDriver)::DownCast(myGraphicDevice);

		// Viewer
		myViewer = new V3d_Viewer(aDriver);
		myViewer->SetDefaultLights();
		myViewer->SetLightOn();
		myViewer->SetDefaultViewProj(V3d_XposYposZpos);
		myViewer->SetDefaultLights();
		myViewer->SetLightOn();

		// View
		myView = myViewer->CreateView();
		Handle(WNT_Window) aWNTWindow = new WNT_Window(GetSafeHwnd());
		myView->SetWindow(aWNTWindow);
		myView->Camera()->SetProjectionType(aDriver->Options().contextStereo
			? Graphic3d_Camera::Projection_Stereo
			: Graphic3d_Camera::Projection_Orthographic);

		if (!aWNTWindow->IsMapped())
		{
			aWNTWindow->Map();
		}

		myView->SetProj(V3d_XposYposZpos, Standard_True);

		// Background color
		m_BackGroundColor = RGB(192, 192, 192);
		Standard_Real R1 = GetRValue(m_BackGroundColor) / 255.;
		Standard_Real G1 = GetGValue(m_BackGroundColor) / 255.;
		Standard_Real B1 = GetBValue(m_BackGroundColor) / 255.;
		myView->SetBackgroundColor(Quantity_TOC_RGB, R1, G1, B1);

		// Interactive Context
		myAISContext = new AIS_InteractiveContext(myViewer);
		myAISContext->UpdateCurrentViewer();

		// Triedron
		Color = Quantity_NOC_BLACK;
		m_TrihedronScale = 0.12;
		Position = Aspect_TOTP_RIGHT_LOWER;
		myView->TriedronDisplay(Position, Color, m_TrihedronScale, V3d_ZBUFFER);

		UnitsAPI::SetLocalSystem(UnitsAPI_MDTV);

		// Other initializations
		aEdgeAspt = new Prs3d_LineAspect(Quantity_NOC_BLACK, Aspect_TypeOfLine::Aspect_TOL_SOLID, 1.2);

		// Set Shaded with edges
		OnShadedEdges();

		SetupCsys();

		SetupAISTrihedron();

		ShowAISTrihedron(true);

	}
	catch (Standard_Failure)
	{
		AfxMessageBox(L"Fatal Error in graphic initialisation");
		return false;
	}

	return true;
}







// COCCViewerView 绘图

void COCCViewerView::OnDraw(CDC* /*pDC*/)
{
	if (!myView.IsNull())
	{
		myView->InvalidateImmediate();
		FlushViewEvents(GetAISContext(), myView, true);
	}
}

void COCCViewerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COCCViewerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COCCViewerView 诊断

#ifdef _DEBUG
void COCCViewerView::AssertValid() const
{
	CView::AssertValid();
}

void COCCViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COCCViewerDoc* COCCViewerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COCCViewerDoc)));
	return (COCCViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// COCCViewerView 消息处理程序


int COCCViewerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!CreateView())
		return -1;

	return 0;
}


void COCCViewerView::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (cx != 0
		&& cy != 0
		&& !myView.IsNull())
	{
		myView->Window()->DoResize();
		myView->MustBeResized();
		myView->Invalidate();
		UpdateOCCView();
	}
}


void COCCViewerView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}

void COCCViewerView::UpdateOCCView()
{
	if (!myView.IsNull())
	{
		if (++myUpdateRequests == 1)
		{
			Invalidate(FALSE);
			UpdateWindow();
		}
	}
}

void COCCViewerView::OnShadedEdges()
{
	// Set shaded display mode
	myAISContext->SetDisplayMode(AIS_Shaded, Standard_True);

	// Turn on edges
	Handle(Prs3d_Drawer) defdrawer = myAISContext->DefaultDrawer();
	defdrawer->SetFaceBoundaryDraw(true);
	defdrawer->SetFaceBoundaryAspect(aEdgeAspt);

	// Redisplay objects
	AIS_ListOfInteractive aList;
	myAISContext->ObjectsInside(aList);
	for (AIS_ListIteratorOfListOfInteractive aLI(aList); aLI.More(); aLI.Next())
	{
		aLI.Value()->Attributes()->SetFaceBoundaryAspect(aEdgeAspt);
		myAISContext->ClearPrs(aLI.Value(), 1, Standard_False);
		myAISContext->RecomputePrsOnly(aLI.Value(), Standard_False);
		myAISContext->SetDisplayMode(aLI.Value(), 1, Standard_False);
		myAISContext->Redisplay(aLI.Value(), 1, true);
	}

	myAISContext->UpdateCurrentViewer();
}

void COCCViewerView::SetupAISTrihedron()
{
	// Axis position
	Handle(Geom_Axis2Placement) aTrihedronAxis = new Geom_Axis2Placement(gp::XOY());

	// Initialize trihedron
	aTrihedron = new AIS_Trihedron(aTrihedronAxis);

	// Display mode
	aTrihedron->SetDisplayMode((int)AIS_DisplayMode::AIS_Shaded);

	// Text color
	aTrihedron->SetTextColor(Quantity_NOC_BLACK);
}

void COCCViewerView::ShowAISTrihedron(bool bOn)
{
	if (bOn)
	{
		bShowAISTrihedron = true;
		myAISContext->Display(aTrihedron, Standard_True);
	}
	else
	{
		bShowAISTrihedron = false;
		myAISContext->Erase(aTrihedron, Standard_True);
	}
}

void COCCViewerView::SetupCsys()
{
	aXPl = new Geom_Axis2Placement(gp_Ax2());

	aXaxis = new AIS_Axis(aXPl, AIS_TypeOfAxis::AIS_TOAX_XAxis);
	aYaxis = new AIS_Axis(aXPl, AIS_TypeOfAxis::AIS_TOAX_YAxis);
	aZaxis = new AIS_Axis(aXPl, AIS_TypeOfAxis::AIS_TOAX_ZAxis);

	aXaxis->SetColor(Quantity_NOC_GREEN);
	aYaxis->SetColor(Quantity_NOC_RED);
	aZaxis->SetColor(Quantity_NOC_BLUE);

	aXaxis->Attributes()->DatumAspect()->SetAxisLength(50, 50, 50);
	aYaxis->Attributes()->DatumAspect()->SetAxisLength(50, 50, 50);
	aZaxis->Attributes()->DatumAspect()->SetAxisLength(50, 50, 50);
}

