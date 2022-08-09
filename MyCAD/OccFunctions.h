#pragma once

#pragma once

#include "occheader.h"
#include <afxstr.h>

//=======================================================================
//Class    :	Geometry functions
//purpose  :	
//=======================================================================

//extern gp_Circ GetCircle();

extern gp_Pln GetPlane(gp_Pnt& P1, gp_Pnt& P2, gp_Pnt& P3);

extern Handle(Geom_TrimmedCurve) CreateLine(gp_Pnt& P1, gp_Pnt& P2);
extern Handle(Geom_TrimmedCurve) CenterPointArc(gp_Pnt& start, gp_Pnt& center, gp_Pnt& end);
extern Handle(Geom_TrimmedCurve) BuildArc(gp_Ax1 axis, gp_Pnt p1, gp_Pnt p2);

extern Handle(Geom_BSplineCurve) GetBSplineCurve(TColgp_Array1OfPnt& pPoints);
extern Handle(Geom_Curve) GetCurve(gp_Circ& C);


extern TopoDS_Wire CreateRectangle(gp_Ax2& Plane, gp_Pnt2d& Pos, Standard_Real Length, Standard_Real Width);

//=======================================================================
//Class    :	Topology functions
//purpose  :	
//=======================================================================
// 

// Vertex
extern TopoDS_Vertex CreateVertex(gp_Pnt P1);

// Edge functions
extern TopoDS_Edge CreateEdge(gp_Pnt P1, gp_Pnt P2);
extern TopoDS_Edge CreateEdge(TopoDS_Vertex& V1, TopoDS_Vertex& V2);
extern TopoDS_Edge CreateEdge(Handle(Geom_Curve)& L);


// Wire
extern TopoDS_Wire CreateWire(Handle(Geom_Curve)& L);
extern TopoDS_Wire CreateWire(TopoDS_Edge& E);
extern TopoDS_Wire CreateWire(TopTools_Array1OfShape& Edges);
extern TopoDS_Wire CreateWire(TColGeom_Array1OfCurve& Curves);

// Face
extern TopoDS_Face CreateFace(TopoDS_Wire& Wire);
extern TopoDS_Face CreateFace(TColgp_Array1OfPnt& pPoints);
extern TopoDS_Face CreateFace(TopTools_Array1OfShape& Edges);
extern TopoDS_Face CreateFace(TColGeom_Array1OfCurve& Curves);
extern TopoDS_Face CreateFace(Handle(Geom_Curve)& L);

extern TopoDS_Face CreateFaceWithHole(TopoDS_Wire& OuterWire, TopoDS_Wire& InnerWire);
extern TopoDS_Face CreateFaceWithHole(TopoDS_Wire& OuterWire, TopTools_Array1OfShape& InnerWires);

// Shell
extern TopoDS_Shell CreateShell(Handle(Geom_Surface)& S);

// Solid
extern TopoDS_Solid CreateSolid(TopTools_Array1OfShape& Shells);

//=======================================================================
//Class    :	Topology Operation functions
//purpose  :	
//=======================================================================

extern TopoDS_Shape Extrude(TopoDS_Face& skface, TopoDS_Shape& abase, Standard_Real height, Standard_Boolean bMidplane, gp_Vec avec);
extern TopoDS_Shape ExtrudeCut(TopoDS_Face& skface, TopoDS_Shape& abase, Standard_Real height);
extern TopoDS_Shape Revolve(TopoDS_Shape& rshape, gp_Ax1 axis, double angleRad);

extern TopoDS_Face AddFilletToFace(TopoDS_Face& skFace, gp_Pnt aPnt, Standard_Real Radius);
extern TopoDS_Shape Add3DFillet(TopoDS_Shape& aShape, TopTools_Array1OfShape& Edges, double radius);
extern TopoDS_Shape Add3DChamfer(TopoDS_Shape& aShape, TopoDS_Edge& Edge, double dist1, double dist2, TopoDS_Face& Face);

//=======================================================================
//Class    :	Transformation functions
//purpose  :	
//=======================================================================

extern TopoDS_Shape RotatedShape(TopoDS_Shape& rshape, gp_Ax1 axis, double angle);
extern TopoDS_Shape TranslatedShape(TopoDS_Shape& tshape, gp_Vec vec);
extern TopoDS_Shape MirrorSketch(gp_Ax1& Axis, TopoDS_Wire& skWire);
extern TopoDS_Shape MirrorShape(TopoDS_Shape& mshape, gp_Pln aPlane);

//=======================================================================
//Class    :	Boolean functions
//purpose  :	
//=======================================================================
// 

extern TopoDS_Shape BooleanAdd(TopoDS_Shape& A, TopoDS_Shape& B);
extern TopoDS_Shape BooleanCut(TopoDS_Shape& A, TopoDS_Shape& B);
extern TopoDS_Shape BooleanCommon(TopoDS_Shape& A, TopoDS_Shape& B);


//=======================================================================
//Class    :	Utility functions
//purpose  :	
//=======================================================================

extern gp_Dir ExtractDirection(TopoDS_Face& face);
extern gp_Ax2 GetCoordinateSystem(TopoDS_Face& face);
extern gp_Pln GetPlaneFromFace(TopoDS_Face& face);
extern TopoDS_Face GetNearestFace(TopoDS_Shape& theShape, gp_Pnt P);
extern TopoDS_Edge GetNearestEdge(TopoDS_Shape& theShape, gp_Pnt P);
extern TopoDS_Vertex GetVertex(TopoDS_Face& aFace, gp_Pnt aPnt);

extern CString GetSurfaceType(TopoDS_Face& aFace);
extern Handle(Geom_Surface) GetSurface(TopoDS_Face& face);
extern Handle(Geom_Curve) GetCurve(TopoDS_Edge& aEdge);
extern bool IsPointOnCurve(Handle(Geom_Curve)& aCurve, gp_Pnt Point);
extern bool IsPointOnSurface(Handle(Geom_Surface)& aSurf, gp_Pnt Point);


