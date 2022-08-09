
// OCCViewerView.h : interface of the COCCViewerView class
//

#pragma once

#include "occheader.h"

#include "MyCADDoc.h"
// =======================================================================
// function : CurAction3d
// purpose  : Enum used for mouse gestures
// =======================================================================
enum CurAction3d
{
	CurAction3d_Nothing,
	CurAction3d_DynamicZooming,
	CurAction3d_WindowZooming,
	CurAction3d_DynamicPanning,
	CurAction3d_GlobalPanning,
	CurAction3d_DynamicRotation
};

// =======================================================================
// function : ViewOrientation
// purpose  : Enum used for view orientation
// =======================================================================
enum ViewOrientation
{
	Top,
	Bottom,
	Right,
	Left,
	Front,
	Back,
	Isometric
};

class CMyCADView : public CView, public AIS_ViewController
{
protected: // create from serialization only
	CMyCADView() noexcept;
	DECLARE_DYNCREATE(CMyCADView)

	// Attributes
public:
	CMyCADDoc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	// Implementation
public:
	virtual ~CMyCADView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

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

	// Update View
	void UpdateOCCView();

	//! Handle view redraw.
	virtual void handleViewRedraw(const Handle(AIS_InteractiveContext)& theCtx,
		const Handle(V3d_View)& theView) Standard_OVERRIDE;

	// Mouse Gestures
	AIS_MouseGestureMap myDefaultGestures;	//	AIS_ViewController Gestures
	AIS_MouseGestureMap myMouseGestures;	//  Modified Gestures
	Graphic3d_Vec2i     myClickPos;
	Standard_Real       myCurZoom;
	CurAction3d         myCurrentMode;
	gp_Pnt				myClickPnt3D;

public:
	Handle(AIS_InteractiveContext)& GetAISContext() { return myAISContext; };
	Handle(V3d_View)& GetView() { return myView; };

	void FitAll() { if (!myView.IsNull()) myView->FitAll();  myView->ZFitAll(); };
	void Redraw() { if (!myView.IsNull()) myView->Redraw(); };


	// Mouse Gestures
	bool bUseDefaultMouseGestures = false;
	void UseDefaultMouseGestures(bool bON) { bUseDefaultMouseGestures = bON; };
	void SetUpMouseGestures();

	//! Get current action.
	CurAction3d getCurrentAction() const { return myCurrentMode; }

	//! Activate mouse gestures.
	void ActivateMouseGestures();

	//! Set current action.
	void setCurrentAction(CurAction3d theAction)
	{
		myCurrentMode = theAction;
		ActivateMouseGestures();
	}

	// Override to provide context menu in the viewer
	virtual void DoMousePopup(const Standard_Integer theMouseX,
		const Standard_Integer theMouseY,
		const Handle(V3d_View)& theView) {};

	// View Orientation
	void SetOrientation(ViewOrientation aOrient);



	//===========================================================================================
	//	Additional functions 
	//	definition of all functions are in seperate source files.
	// 	   DisplayFunctions.cpp
	//	   SelectionFunctions.cpp
	//	   DatumFunctions.cpp
	//	   Clipping.cpp
	//	   Dimensions.cpp
	//===========================================================================================

public:

	// Background
	void SetTopGradientColor(COLORREF TopGradientC);
	void SetBottomGradientColor(COLORREF BottomGradientC);
	void SetBackGroundColor(COLORREF BackGroundColor);
	void bDrawGradientBackGround(bool GradientBackGround) { m_GradientBackGround = GradientBackGround; }
	void DrawBackground();

	//DisplayFunctions
	//--------------------------------	
	void ClearContext(bool All = false);
	void OnShaded();
	void OnShadedEdges();
	void OnWireFrame();
	void OnTransparency();

	void DisplayShape(TopoDS_Shape& aShape);
	void DisplayShape(TopoDS_Shape& aShape, Quantity_Color theColor);
	void Display(const Handle(AIS_InteractiveObject)& theObj, Standard_Boolean theToUpdateViewer);

	void DisplayText(gp_Pnt2d& thePoint, const char* theText,
		Standard_Real theXoffset = 0,
		Standard_Real theYoffset = 0,
		Standard_Real theTextScale = 0.05);
	void DisplayText(gp_Pnt& thePoint, const char* theText,
		Standard_Real theXoffset = 0,
		Standard_Real theYoffset = 0,
		Standard_Real theZoffset = 0,
		Standard_Real theTextScale = 0.05);
	void DisplayPoint(gp_Pnt2d& thePoint);
	void DisplayPoint(gp_Pnt& thePoint);

	void DisplayCurve(Handle(Geom2d_Curve) aCurve,
		const Aspect_TypeOfLine aTypeOfline,
		const Aspect_WidthOfLine aWidthOfLine,
		const Quantity_Color theColor,
		Standard_Boolean UpdateViewer = Standard_False);

	void DisplayCurve(Handle(Geom_Curve) theCurve,
		Quantity_Color theColor,
		Standard_Boolean theToUpdateViewer = Standard_False);

	void DisplaySurface(Handle(Geom_Surface) aSurface,
		Quantity_Color aNameOfColor = Quantity_NOC_BLUE,
		Standard_Boolean UpdateViewer = Standard_False);

	void DisplayBoundingBox(Bnd_Box& theBox);
	void DisplayBoundingBox(Bnd_OBB& theBox);

	//// SelectionFunctions
	////--------------------------------
	//TopoDS_Shape GetSelectedShape();
	//TopoDS_Compound GetAllShapes();
	//Handle(AIS_InteractiveObject) GetSelectedObj();
	//Handle(TopTools_HSequenceOfShape)  GetSelectedShapeSeq();
	AIS_ListOfInteractive GetListofBodies();
	//v//oid SelectAllObjects();

	//void SetHighilightColor(Quantity_Color aNameOfColor);
	//void SetSelectionColor(Quantity_Color aNameOfColor);

	//void SetSelectionFilter(Standard_Integer theMode = 0);
	//void SetEdgeFilter(StdSelect_TypeOfEdge aTypeOfEdge);
	//void SetFaceFilter(StdSelect_TypeOfFace aTypeOfFace);
	//void RemoveAllFilters();


	// DatumFunctions
	//--------------------------------
	void DisplayCSys(bool bOn, gp_Ax2 aCsys);
	void DisplayPlane(gp_Pln& aPlane);
	void ShowAISTrihedron(bool bOn);
	void ShowCube(bool bOn);

	//// Dimensions
	////--------------------------------
	//void DisplayLengthDimension(gp_Pnt& P1, gp_Pnt& P2, gp_Pnt& P3, bool isText3D = false);
	//void DisplayLengthDimension(gp_Dir aDir, gp_Pnt& P1, gp_Pnt& P2, gp_Pnt& P3, bool isText3D = false);
	//void DisplayDiameterDimension(TopoDS_Edge& aCircularEdge);
	//void DisplayRadiusDimension(TopoDS_Edge& aCircularEdge);
	//void DisplayRadiusDimension(gp_Pnt& ancP, TopoDS_Edge& aCircularEdge);

	//// Clipping
	////--------------------------------
	//void EnableClipping(bool bON);
	//void SetCapping(bool showSec);
	//void SetCappingTex(bool showSec, CString TexturePath);
	//void AddClipPlane(const Handle(Graphic3d_ClipPlane)& thePlane);
	//void CreateClipSection(gp_Pln& aPlane);

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

	COLORREF m_TopGradientC;
	COLORREF m_BottomGradientC;
	bool m_GradientBackGround;

	COLORREF m_BackGroundColorDef;
	COLORREF m_TopGradientCDef;
	COLORREF m_BottomGradientCDef;

	//Top Color
	Standard_Real R1;
	Standard_Real G1;
	Standard_Real B1;

	//Bottom Color
	Standard_Real R2;
	Standard_Real G2;
	Standard_Real B2;

	void InitializeBackgroundColors();
	void InitializeViewCube();
	void SetupCsys();
	void SetupAISTrihedron();

	// Generated message map functions
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnStandardviewsFront();
	afx_msg void OnStandardviewsBack();
	afx_msg void OnStandardviewsTop();
	afx_msg void OnStandardviewsBottom();
	afx_msg void OnStandardviewsLeft();
	afx_msg void OnStandardviewsRight();
	afx_msg void OnStandardviewsIsometric();
	afx_msg void OnStarderviewFront();
	afx_msg void OnStarderviewBack();
	afx_msg void OnStarderviewTop();
	afx_msg void OnStarderviewBottom();
	afx_msg void OnStarderviewLeft();
	afx_msg void OnStarderviewRight();
	afx_msg void OnStanderViewIso();
};

#ifndef _DEBUG  // debug version in OCCViewerView.cpp
inline COCCViewerDoc* COCCViewerView::GetDocument() const
{
	return reinterpret_cast<COCCViewerDoc*>(m_pDocument);
}
#endif

