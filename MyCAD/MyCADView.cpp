
// OCCViewerView.cpp : implementation of the COCCViewerView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyCAD.h"
#endif


#include "MyCADView.h"
#include "AISCurve.h"


// COCCViewerView

IMPLEMENT_DYNCREATE(CMyCADView, CView)

BEGIN_MESSAGE_MAP(CMyCADView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_STARDERVIEW_FRONT, &CMyCADView::OnStarderviewFront)
	ON_COMMAND(ID_STARDERVIEW_BACK, &CMyCADView::OnStarderviewBack)
	ON_COMMAND(ID_STARDERVIEW_TOP, &CMyCADView::OnStarderviewTop)
	ON_COMMAND(ID_STARDERVIEW_BOTTOM, &CMyCADView::OnStarderviewBottom)
	ON_COMMAND(ID_STARDERVIEW_LEFT, &CMyCADView::OnStarderviewLeft)
	ON_COMMAND(ID_STARDERVIEW_RIGHT, &CMyCADView::OnStarderviewRight)
	ON_COMMAND(ID_Menu, &CMyCADView::OnStanderViewIso)
END_MESSAGE_MAP()

// COCCViewerView construction/destruction

CMyCADView::CMyCADView() noexcept
	: myUpdateRequests(0),
	myCurZoom(0.0),
	myCurrentMode(CurAction3d_Nothing)
{
	// TODO: add construction code here	
	myGraphicDevice = NULL;
	myViewer = NULL;
	myView = NULL;
	myAISContext = NULL;
	myDefaultGestures = myMouseGestureMap;
}

CMyCADView::~CMyCADView()
{
	if (!myView.IsNull())
	{
		myView->Remove();
		myView.Nullify();
	}
}

BOOL CMyCADView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COCCViewerView drawing

void CMyCADView::OnDraw(CDC* /*pDC*/)
{
	// TODO: add draw code for native data here
	if (!myView.IsNull())
	{
		myView->InvalidateImmediate();
		FlushViewEvents(GetAISContext(), myView, true);
	}
}

void CMyCADView::UpdateOCCView()
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

void CMyCADView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COCCViewerView diagnostics

#ifdef _DEBUG
void CMyCADView::AssertValid() const
{
	CView::AssertValid();
}

void CMyCADView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyCADDoc* CMyCADView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCADDoc)));
	return (CMyCADDoc*)m_pDocument;
}
#endif //_DEBUG


// COCCViewerView message handlers


int CMyCADView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if (!CreateView())
		return -1;

	return 0;
}


void CMyCADView::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
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


void CMyCADView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class

	SetUpMouseGestures();
}

// ================================================================
// Function : CreateView
// Purpose  :
// ================================================================
bool CMyCADView::CreateView()
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

// ================================================================
// Function : handleViewRedraw
// Purpose  :
// ================================================================
void CMyCADView::handleViewRedraw(const Handle(AIS_InteractiveContext)& theCtx,
	const Handle(V3d_View)& theView)
{
	myUpdateRequests = 0;
	AIS_ViewController::handleViewRedraw(theCtx, theView);
}

// ================================================================
// Function : Mouse Message Handlers
// Purpose  :
// ================================================================

void CMyCADView::OnLButtonDown(UINT nFlags, CPoint point)
{
	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	PressMouseButton(Graphic3d_Vec2i(point.x, point.y), Aspect_VKeyMouse_LeftButton, aFlags, false);
	UpdateOCCView();
}


void CMyCADView::OnLButtonUp(UINT nFlags, CPoint point)
{
	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	ReleaseMouseButton(Graphic3d_Vec2i(point.x, point.y), Aspect_VKeyMouse_LeftButton, aFlags, false);
	UpdateOCCView();

	if (myCurrentMode != CurAction3d_Nothing)
	{
		setCurrentAction(CurAction3d_Nothing);
	}
}


void CMyCADView::OnMButtonUp(UINT nFlags, CPoint point)
{
	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	ReleaseMouseButton(Graphic3d_Vec2i(point.x, point.y), Aspect_VKeyMouse_MiddleButton, aFlags, false);
	UpdateOCCView();

	if (myCurrentMode != CurAction3d_Nothing)
	{
		setCurrentAction(CurAction3d_Nothing);
	}
}


void CMyCADView::OnMButtonDown(UINT nFlags, CPoint point)
{
	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	PressMouseButton(Graphic3d_Vec2i(point.x, point.y), Aspect_VKeyMouse_MiddleButton, aFlags, false);
	UpdateOCCView();
}

void CMyCADView::OnRButtonDown(UINT nFlags, CPoint point)
{
	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	PressMouseButton(Graphic3d_Vec2i(point.x, point.y), Aspect_VKeyMouse_RightButton, aFlags, false);
	UpdateOCCView();
	myClickPos.SetValues(point.x, point.y);
}

void CMyCADView::OnRButtonUp(UINT nFlags, CPoint point)
{
	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	ReleaseMouseButton(Graphic3d_Vec2i(point.x, point.y), Aspect_VKeyMouse_RightButton, aFlags, false);
	UpdateOCCView();

	if (myCurrentMode != CurAction3d_Nothing)
	{
		setCurrentAction(CurAction3d_Nothing);
	}

	if (aFlags == Aspect_VKeyFlags_NONE
		&& (myClickPos - Graphic3d_Vec2i(point.x, point.y)).cwiseAbs().maxComp() <= 4)
	{
		DoMousePopup(point.x, point.y, myView);
	}
}


void CMyCADView::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT aMouseEvent;          // for WM_MOUSELEAVE
	aMouseEvent.cbSize = sizeof(aMouseEvent);
	aMouseEvent.dwFlags = TME_LEAVE;
	aMouseEvent.hwndTrack = m_hWnd;
	aMouseEvent.dwHoverTime = HOVER_DEFAULT;
	if (!::_TrackMouseEvent(&aMouseEvent)) { TRACE("Track ERROR!\n"); }

	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	if (UpdateMousePosition(Graphic3d_Vec2i(point.x, point.y), PressedMouseButtons(), aFlags, false))
	{
		UpdateOCCView();
	}
}


BOOL CMyCADView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	const Standard_Real aDeltaF = Standard_Real(zDelta) / Standard_Real(WHEEL_DELTA);
	CPoint aCursorPnt = pt;
	ScreenToClient(&aCursorPnt);
	const Graphic3d_Vec2i  aPos(aCursorPnt.x, aCursorPnt.y);
	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	if (UpdateMouseScroll(Aspect_ScrollDelta(aPos, aDeltaF, aFlags)))
	{
		UpdateOCCView();
	}

	return true;
}

// ================================================================
// Function : Mouse Gesture
// Purpose  :
// ================================================================

void CMyCADView::SetUpMouseGestures()
{
	if (bUseDefaultMouseGestures)
	{
		myMouseGestureMap = myDefaultGestures;
		return;
	}

	myMouseGestureMap.Clear();
	myMouseGestures.Clear();

	myMouseGestures.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_SelectRectangle);
	myMouseGestures.Bind(Aspect_VKeyMouse_LeftButton | Aspect_VKeyFlags_CTRL, AIS_MouseGesture_Zoom);
	myMouseGestures.Bind(Aspect_VKeyMouse_LeftButton | Aspect_VKeyFlags_SHIFT, AIS_MouseGesture_Pan);

	myMouseGestures.Bind(Aspect_VKeyMouse_RightButton, AIS_MouseGesture_Zoom);

	myMouseGestures.Bind(Aspect_VKeyMouse_MiddleButton, AIS_MouseGesture_RotateOrbit);
	myMouseGestures.Bind(Aspect_VKeyMouse_MiddleButton | Aspect_VKeyFlags_CTRL, AIS_MouseGesture_Pan);

	myMouseGestureMap = myMouseGestures;
}

void CMyCADView::ActivateMouseGestures()
{
	myMouseGestureMap.Clear();
	AIS_MouseGesture aRot = AIS_MouseGesture_RotateOrbit;
	switch (myCurrentMode)
	{
	case CurAction3d_Nothing:
	{
		if (bUseDefaultMouseGestures)
		{
			myMouseGestureMap = myDefaultGestures;
		}
		else
		{
			myMouseGestureMap = myMouseGestures;
		}
		break;
	}
	case CurAction3d_DynamicZooming:
	{
		myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_Zoom);
		break;
	}
	case CurAction3d_GlobalPanning:
	{
		break;
	}
	case CurAction3d_WindowZooming:
	{
		myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_ZoomWindow);
		break;
	}
	case CurAction3d_DynamicPanning:
	{
		myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_Pan);
		break;
	}
	case CurAction3d_DynamicRotation:
	{
		myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, aRot);
		break;
	}
	}
}

// =======================================================================
// function : SetOrientation
// purpose  :
// =======================================================================
void CMyCADView::SetOrientation(ViewOrientation aOrient)
{
	switch (aOrient)
	{
	case Top:
	{
		if (!myView.IsNull())
		{
			myView->SetProj(V3d_Ypos, Standard_True);
		}
		break;
	}
	case Bottom:
	{
		if (!myView.IsNull())
			myView->SetProj(V3d_Yneg, Standard_True);
		break;
	}
	case Right:
	{
		if (!myView.IsNull())
			myView->SetProj(V3d_Xpos, Standard_True);
		break;
	}
	case Left:
	{
		if (!myView.IsNull())
			myView->SetProj(V3d_Xneg, Standard_True);
		break;
	}
	case Front:
	{
		if (!myView.IsNull())
			myView->SetProj(V3d_Zpos, Standard_True);
		break;
	}
	case Back:
	{
		if (!myView.IsNull())
			myView->SetProj(V3d_Zneg, Standard_True);
		break;
	}
	case Isometric:
	{
		if (!myView.IsNull())
			myView->SetProj(V3d_XposYposZpos, Standard_True);
		break;
	}
	}
	if (!myView.IsNull())
		FitAll();
}

void CMyCADView::OnStandardviewsFront()
{
	// TODO: Add your command handler code here
	SetOrientation(ViewOrientation::Front);
}


void CMyCADView::OnStandardviewsBack()
{
	// TODO: Add your command handler code here
	SetOrientation(ViewOrientation::Back);
}


void CMyCADView::OnStandardviewsTop()
{
	// TODO: Add your command handler code here
	SetOrientation(ViewOrientation::Top);
}


void CMyCADView::OnStandardviewsBottom()
{
	// TODO: Add your command handler code here
	SetOrientation(ViewOrientation::Bottom);
}


void CMyCADView::OnStandardviewsLeft()
{
	// TODO: Add your command handler code here
	SetOrientation(ViewOrientation::Left);
}


void CMyCADView::OnStandardviewsRight()
{
	// TODO: Add your command handler code here
	SetOrientation(ViewOrientation::Right);
}


void CMyCADView::OnStandardviewsIsometric()
{
	// TODO: Add your command handler code here
	SetOrientation(ViewOrientation::Isometric);
}

// =======================================================================
// function : Background
// purpose  :
// =======================================================================

void CMyCADView::InitializeBackgroundColors()
{
	m_GradientBackGround = true;

	m_BackGroundColor = RGB(192, 192, 192);
	m_TopGradientC = RGB(10.0f, 128.0f, 200.0f);
	m_BottomGradientC = RGB(255.0f, 255.0f, 255.0f);

	R1 = GetRValue(m_TopGradientC) / 255.;
	G1 = GetGValue(m_TopGradientC) / 255.;
	B1 = GetBValue(m_TopGradientC) / 255.;

	R2 = GetRValue(m_BottomGradientC) / 255.;
	G2 = GetGValue(m_BottomGradientC) / 255.;
	B2 = GetBValue(m_BottomGradientC) / 255.;

	m_BackGroundColorDef = RGB(192, 192, 192);
	m_TopGradientCDef = RGB(10.0f, 128.0f, 200.0f);
	m_BottomGradientCDef = RGB(255.0f, 255.0f, 255.0f);
}

void CMyCADView::SetTopGradientColor(COLORREF TopGradientC)
{
	m_TopGradientC = TopGradientC;
	// Top Gradient
	R1 = GetRValue(m_TopGradientC) / 255.;
	G1 = GetGValue(m_TopGradientC) / 255.;
	B1 = GetBValue(m_TopGradientC) / 255.;
}

void CMyCADView::SetBottomGradientColor(COLORREF BottomGradientC)
{
	m_BottomGradientC = BottomGradientC;
	// Bottom Gradient
	R2 = GetRValue(m_BottomGradientC) / 255.;
	G2 = GetGValue(m_BottomGradientC) / 255.;
	B2 = GetBValue(m_BottomGradientC) / 255.;
}

void CMyCADView::SetBackGroundColor(COLORREF BackGroundColor)
{
	m_BackGroundColor = BackGroundColor;
}

void CMyCADView::DrawBackground()
{
	if (m_GradientBackGround)
	{
		myView->SetBgGradientStyle(Aspect_GradientFillMethod::Aspect_GFM_VER);

		myView->SetBgGradientColors(Quantity_Color(R1, G1, B1, Quantity_TOC_RGB), Quantity_Color(R2, G2, B2, Quantity_TOC_RGB), Aspect_GradientFillMethod::Aspect_GFM_VER);
		myView->Update();
		myView->Redraw();

	}
	else
	{

		myView->SetBgGradientStyle(Aspect_GradientFillMethod::Aspect_GFM_NONE);
		R1 = GetRValue(m_BackGroundColor) / 255.;
		G1 = GetGValue(m_BackGroundColor) / 255.;
		B1 = GetBValue(m_BackGroundColor) / 255.;

		myView->SetBackgroundColor(Quantity_TOC_RGB, R1, G1, B1);
		myView->Update();
		myView->Redraw();
	}
}


void CMyCADView::DisplayPlane(gp_Pln& aPlane)
{
	// Get Coordinate System of plane
	gp_Ax3 ax3 = aPlane.Position();
	gp_Ax2 ax2 = ax3.Ax2();

	// Geometric Plane
	Handle(Geom_Plane) aGPlane = GC_MakePlane(aPlane).Value();

	// AIS Plane
	Handle(AIS_Plane) aisPlane = new AIS_Plane(aGPlane);

	Display(aisPlane, Standard_False);
}

void CMyCADView::SetupCsys()
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

void CMyCADView::DisplayCSys(bool bOn, gp_Ax2 aCsys)
{

	if (bOn)
	{
		// Set new coordinate system
		aXPl = new Geom_Axis2Placement(aCsys);
		aXaxis->SetAxis2Placement(aXPl, AIS_TypeOfAxis::AIS_TOAX_XAxis);
		aYaxis->SetAxis2Placement(aXPl, AIS_TypeOfAxis::AIS_TOAX_YAxis);
		aZaxis->SetAxis2Placement(aXPl, AIS_TypeOfAxis::AIS_TOAX_ZAxis);

		if (GetAISContext()->IsDisplayed(aXaxis))
		{
			GetAISContext()->Redisplay(aXaxis, true);
			GetAISContext()->Redisplay(aYaxis, true);
			GetAISContext()->Redisplay(aZaxis, true);
		}
		else
		{
			GetAISContext()->Display(aXaxis, true);
			GetAISContext()->Display(aYaxis, true);
			GetAISContext()->Display(aZaxis, true);
		}

		GetAISContext()->UpdateCurrentViewer();
	}
	else
	{
		// Erase previous Csys
		GetAISContext()->Remove(aXaxis, true);
		GetAISContext()->Remove(aYaxis, true);
		GetAISContext()->Remove(aZaxis, true);
		GetAISContext()->UpdateCurrentViewer();
	}
}

void CMyCADView::SetupAISTrihedron()
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

void CMyCADView::ShowAISTrihedron(bool bOn)
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

void CMyCADView::InitializeViewCube()
{
	aVCube = new AIS_ViewCube();
	aVCube->SetYup(Standard_True);
	aVCube->SetDrawAxes(Standard_False);
	aVCube->SetSize(60);
	aVCube->SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_TriedronPers,
		Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i(70, 70)));
}

void CMyCADView::ShowCube(bool bOn)
{
	if (bOn)
	{
		bShowCube = true;
		myAISContext->Display(aVCube, Standard_True);
	}
	else
	{
		bShowCube = false;
		myAISContext->Erase(aVCube, Standard_True);
	}
}

void CMyCADView::ClearContext(bool All)
{
	AIS_ListOfInteractive aList;
	myAISContext->DisplayedObjects(aList);
	AIS_ListIteratorOfListOfInteractive aListIterator;
	for (aListIterator.Initialize(aList); aListIterator.More(); aListIterator.Next())
	{
		if (All)
		{
			myAISContext->Remove(aListIterator.Value(), Standard_True);
		}
		else
		{
			if (aListIterator.Value()->Type() == AIS_KindOfInteractive::AIS_KOI_Shape)
			{
				myAISContext->Remove(aListIterator.Value(), Standard_True);
			}
		}
	}

	// Redisplay AIS trihedron
	if (bShowAISTrihedron)
	{
		ShowAISTrihedron(bShowAISTrihedron);
	}

	// Redisplay
	if (bShowCube)
	{
		ShowCube(bShowCube);
	}
}

AIS_ListOfInteractive CMyCADView::GetListofBodies()
{
	// Initialize list
	AIS_ListOfInteractive m_ShapeList;	// List of only shapes
	AIS_ListOfInteractive aList;		// List of all interactive objects
	m_ShapeList.Clear();

	// Get objects from context
	myAISContext->ObjectsInside(aList);

	// Iterate on the list to get shape objects
	if (aList.Size() > 0)
	{
		for (AIS_ListIteratorOfListOfInteractive aLI(aList); aLI.More(); aLI.Next())
		{
			if (aLI.Value()->Type() == AIS_KindOfInteractive::AIS_KOI_Shape)
			{
				m_ShapeList.Append(aLI.Value());
			}
		}
	}

	return m_ShapeList;
}

void CMyCADView::OnShaded()
{
	// Set shaded display mode
	myAISContext->SetDisplayMode(AIS_Shaded, Standard_True);

	// Turn off edges
	Handle(Prs3d_Drawer) defdrawer = myAISContext->DefaultDrawer();
	defdrawer->SetFaceBoundaryDraw(false);

	// Redisplay objects
	AIS_ListOfInteractive aList;
	myAISContext->ObjectsInside(aList);
	for (AIS_ListIteratorOfListOfInteractive aLI(aList); aLI.More(); aLI.Next())
	{
		myAISContext->ClearPrs(aLI.Value(), 1, Standard_False);
		myAISContext->RecomputePrsOnly(aLI.Value(), Standard_False);
		myAISContext->SetDisplayMode(aLI.Value(), 1, Standard_False);
		myAISContext->Redisplay(aLI.Value(), 1, true);
	}

	myAISContext->UpdateCurrentViewer();
}

void CMyCADView::OnShadedEdges()
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

void CMyCADView::OnWireFrame()
{
	// Set wireframe display mode
	myAISContext->SetDisplayMode(AIS_WireFrame, Standard_True);
	myView->SetComputedMode(Standard_False);

	// Redisplay objects
	AIS_ListOfInteractive aList;
	myAISContext->ObjectsInside(aList);
	for (AIS_ListIteratorOfListOfInteractive aLI(aList); aLI.More(); aLI.Next())
	{
		myAISContext->ClearPrs(aLI.Value(), 1, Standard_False);
		myAISContext->RecomputePrsOnly(aLI.Value(), Standard_False);
		myAISContext->SetDisplayMode(aLI.Value(), 0, Standard_False);
		myAISContext->Redisplay(aLI.Value(), 1, true);
	}

	myAISContext->UpdateCurrentViewer();
}

void CMyCADView::OnTransparency()
{
	if (bSetTransparent)
	{
		for (myAISContext->InitSelected();
			myAISContext->MoreSelected();
			myAISContext->NextSelected())
		{
			myAISContext->SetTransparency(myAISContext->SelectedInteractive(), 0.5, Standard_False);
		}
	}
	else
	{
		for (myAISContext->InitSelected();
			myAISContext->MoreSelected();
			myAISContext->NextSelected())
		{
			myAISContext->SetTransparency(myAISContext->SelectedInteractive(), 0, Standard_False);
		}
	}
}

void CMyCADView::Display(const Handle(AIS_InteractiveObject)& theObj,
	Standard_Boolean theToUpdateViewer)
{
	myAISContext->Display(theObj, theToUpdateViewer);
	myView->FitAll();
}

void CMyCADView::DisplayShape(TopoDS_Shape& aShape)
{
	// Initialize shape object
	Handle(AIS_Shape) aisShape = new AIS_Shape(aShape);

	// Set Display mode
	aisShape->SetDisplayMode((int)AIS_DisplayMode::AIS_Shaded);

	// Set Edge Color
	aisShape->Attributes()->SetFaceBoundaryAspect(aEdgeAspt);

	Display(aisShape, true);
}

void CMyCADView::DisplayShape(TopoDS_Shape& aShape, Quantity_Color theColor)
{
	// Initialize shape object
	Handle(AIS_Shape) aisShape = new AIS_Shape(aShape);

	// Set Color
	aisShape->SetColor(theColor);

	// Set Display mode
	aisShape->SetDisplayMode((int)AIS_DisplayMode::AIS_Shaded);

	// Set Edge Color
	aisShape->Attributes()->SetFaceBoundaryAspect(aEdgeAspt);

	Display(aisShape, true);
}

void CMyCADView::DisplayText(gp_Pnt2d& thePoint, const char* theText, Standard_Real theXoffset, Standard_Real theYoffset, Standard_Real theTextScale)
{
	Handle(AIS_TextLabel) aLabel = new AIS_TextLabel();
	aLabel->SetText(theText);
	aLabel->SetPosition(gp_Pnt(thePoint.X() + theXoffset, thePoint.Y() + theYoffset, 0.0));
	aLabel->SetHeight(theTextScale);
	aLabel->SetColor(Quantity_NOC_BLACK);
	//(void)theTextScale;
	Display(aLabel, true);
}

void CMyCADView::DisplayText(gp_Pnt& thePoint, const char* theText,
	Standard_Real theXoffset, Standard_Real theYoffset, Standard_Real theZoffset, Standard_Real theTextScale)
{
	Handle(AIS_TextLabel) aLabel = new AIS_TextLabel();
	aLabel->SetText(theText);
	aLabel->SetPosition(gp_Pnt(thePoint.X() + theXoffset, thePoint.Y() + theYoffset, thePoint.Z() + theZoffset));
	aLabel->SetHeight(theTextScale);
	aLabel->SetColor(Quantity_NOC_BLACK);
	Display(aLabel, true);
}

void CMyCADView::DisplayPoint(gp_Pnt2d& thePoint)
{
	gp_Pnt P(thePoint.X(), thePoint.Y(), 0.0);
	DisplayPoint(P);
}

void CMyCADView::DisplayPoint(gp_Pnt& thePoint)
{
	Handle(AIS_Point) aGraphicPoint = new AIS_Point(new Geom_CartesianPoint(thePoint));
	aGraphicPoint->SetMarker(Aspect_TypeOfMarker::Aspect_TOM_O);
	aGraphicPoint->SetColor(Quantity_NOC_RED);
	Display(aGraphicPoint, Standard_False);
}

void CMyCADView::DisplayCurve(Handle(Geom_Curve) theCurve,
	Quantity_Color theColor,
	Standard_Boolean theToUpdateViewer)
{
	//Handle(AISCurve) aGraphicCurve = new AISCurve(theCurve, Aspect_TOL_SOLID, 1, theColor);
	//aGraphicCurve->SetDisplayMode(0);
	//Display(aGraphicCurve, theToUpdateViewer);
}

void CMyCADView::DisplayCurve(Handle(Geom2d_Curve) theCurve,
	const Aspect_TypeOfLine aTypeOfline,
	const Aspect_WidthOfLine aWidthOfLine,
	const Quantity_Color theColor,
	Standard_Boolean theToUpdateViewer)
{
	Handle(AISCurve) aGraphicCurve = new AISCurve(theCurve, aTypeOfline, aWidthOfLine, theColor);
	aGraphicCurve->SetDisplayMode(0);
	Display(aGraphicCurve, theToUpdateViewer);
}

void CMyCADView::DisplaySurface(Handle(Geom_Surface) theSurface,
	Quantity_Color aNameOfColor,
	Standard_Boolean theToUpdateViewer)
{
	//Handle(AISSurface) aAISSurface = new AISSurface(theSurface);
	//aAISSurface->SetColor(aNameOfColor);
	//Display(aAISSurface, theToUpdateViewer);
}

void CMyCADView::DisplayBoundingBox(Bnd_Box& theBox)
{
	Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
	theBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

	DisplayPoint(gp_Pnt(aXmin, aYmax, aZmin));
	DisplayPoint(gp_Pnt(aXmax, aYmax, aZmin));
	DisplayPoint(gp_Pnt(aXmin, aYmin, aZmin));
	DisplayPoint(gp_Pnt(aXmax, aYmin, aZmin));

	DisplayPoint(gp_Pnt(aXmin, aYmax, aZmax));
	DisplayPoint(gp_Pnt(aXmax, aYmax, aZmax));
	DisplayPoint(gp_Pnt(aXmin, aYmin, aZmax));
	DisplayPoint(gp_Pnt(aXmax, aYmin, aZmax));

	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmin, aYmax, aZmin),
		gp_Pnt(aXmax, aYmax, aZmin)).Value(), Quantity_NOC_RED); // X,Ymax,ZMin
	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmin, aYmin, aZmin),
		gp_Pnt(aXmax, aYmin, aZmin)).Value(), Quantity_NOC_RED); // X,Ymin,ZMin
	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmin, aYmin, aZmin),
		gp_Pnt(aXmin, aYmax, aZmin)).Value(), Quantity_NOC_RED); // Xmin,Y,ZMin
	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmax, aYmin, aZmin),
		gp_Pnt(aXmax, aYmax, aZmin)).Value(), Quantity_NOC_RED); // Xmax,Y,ZMin
	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmin, aYmax, aZmax),
		gp_Pnt(aXmax, aYmax, aZmax)).Value(), Quantity_NOC_RED); // X,Ymax,ZMax
	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmin, aYmin, aZmax),
		gp_Pnt(aXmax, aYmin, aZmax)).Value(), Quantity_NOC_RED); // X,Ymin,ZMax
	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmin, aYmin, aZmax),
		gp_Pnt(aXmin, aYmax, aZmax)).Value(), Quantity_NOC_RED); // Xmin,Y,ZMax
	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmax, aYmin, aZmax),
		gp_Pnt(aXmax, aYmax, aZmax)).Value(), Quantity_NOC_RED); // Xmax,Y,ZMax
	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmin, aYmin, aZmin),
		gp_Pnt(aXmin, aYmin, aZmax)).Value(), Quantity_NOC_RED); // Xmin,Ymin,Z
	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmax, aYmin, aZmin),
		gp_Pnt(aXmax, aYmin, aZmax)).Value(), Quantity_NOC_RED); // Xmax,Ymin,Z
	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmin, aYmax, aZmin),
		gp_Pnt(aXmin, aYmax, aZmax)).Value(), Quantity_NOC_RED); // Xmin,Ymax,Z
	DisplayCurve(GC_MakeSegment(gp_Pnt(aXmax, aYmax, aZmin),
		gp_Pnt(aXmax, aYmax, aZmax)).Value(), Quantity_NOC_RED); // Xmax,Ymax,Z

}

void CMyCADView::DisplayBoundingBox(Bnd_OBB& theBox)
{
	gp_Pnt theP[8];
	theBox.GetVertex(theP);

	DisplayPoint(theP[0]);
	DisplayPoint(theP[1]);
	DisplayPoint(theP[2]);
	DisplayPoint(theP[3]);

	DisplayPoint(theP[4]);
	DisplayPoint(theP[5]);
	DisplayPoint(theP[6]);
	DisplayPoint(theP[7]);

	DisplayCurve(GC_MakeSegment(theP[0], theP[1]).Value(), Quantity_NOC_RED);
	DisplayCurve(GC_MakeSegment(theP[0], theP[2]).Value(), Quantity_NOC_RED);
	DisplayCurve(GC_MakeSegment(theP[2], theP[3]).Value(), Quantity_NOC_RED);
	DisplayCurve(GC_MakeSegment(theP[1], theP[3]).Value(), Quantity_NOC_RED);

	DisplayCurve(GC_MakeSegment(theP[4], theP[5]).Value(), Quantity_NOC_RED);
	DisplayCurve(GC_MakeSegment(theP[5], theP[7]).Value(), Quantity_NOC_RED);
	DisplayCurve(GC_MakeSegment(theP[7], theP[6]).Value(), Quantity_NOC_RED);
	DisplayCurve(GC_MakeSegment(theP[6], theP[4]).Value(), Quantity_NOC_RED);

	DisplayCurve(GC_MakeSegment(theP[3], theP[7]).Value(), Quantity_NOC_RED);
	DisplayCurve(GC_MakeSegment(theP[1], theP[5]).Value(), Quantity_NOC_RED);
	DisplayCurve(GC_MakeSegment(theP[2], theP[6]).Value(), Quantity_NOC_RED);
	DisplayCurve(GC_MakeSegment(theP[0], theP[4]).Value(), Quantity_NOC_RED);

}


void CMyCADView::OnStarderviewFront()
{
	// TODO: 在此添加命令处理程序代码
	SetOrientation(ViewOrientation::Front);
}


void CMyCADView::OnStarderviewBack()
{
	// TODO: 在此添加命令处理程序代码
	SetOrientation(ViewOrientation::Back);
}


void CMyCADView::OnStarderviewTop()
{
	// TODO: 在此添加命令处理程序代码
	SetOrientation(ViewOrientation::Top);
}


void CMyCADView::OnStarderviewBottom()
{
	// TODO: 在此添加命令处理程序代码
	SetOrientation(ViewOrientation::Bottom);
}


void CMyCADView::OnStarderviewLeft()
{
	// TODO: 在此添加命令处理程序代码
	SetOrientation(ViewOrientation::Left);
}


void CMyCADView::OnStarderviewRight()
{
	// TODO: 在此添加命令处理程序代码
	SetOrientation(ViewOrientation::Right);
}


void CMyCADView::OnStanderViewIso()
{
	// TODO: 在此添加命令处理程序代码
	SetOrientation(ViewOrientation::Isometric);
}
