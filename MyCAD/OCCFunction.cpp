
#include "pch.h"
#include "framework.h"
#include "OccFunctions.h"

//=======================================================================
//Class    :	Geometry functions
//purpose  :	
//=======================================================================

gp_Pln GetPlane(gp_Pnt& P1, gp_Pnt& P2, gp_Pnt& P3)
{
	gp_Pln aPln = gce_MakePln(P1, P2, P3).Value();
	return aPln;
}

Handle(Geom_TrimmedCurve) CenterPointArc(gp_Pnt& start, gp_Pnt& center, gp_Pnt& end)
{
	// Radius of circle
	Standard_Real radius = center.Distance(start);

	// Create Plane from three points
	gp_Pln aPln = GetPlane(start, end, center);

	// Get Coordinate System of plane
	gp_Ax3 ax3 = aPln.Position();
	gp_Ax2 ax2 = ax3.Ax2();
	ax2.SetLocation(center);

	// Create circle with center 
	gp_Circ aCir(ax2, radius);

	// Parameters
	Standard_Real Alpha1, Alpha2;
	Standard_Boolean sense;

	Alpha1 = ElCLib::Parameter(aCir, start);
	Alpha2 = ElCLib::Parameter(aCir, end);
	sense = Standard_True;

	Handle(Geom_Circle) Circ = new Geom_Circle(aCir);
	Handle(Geom_TrimmedCurve) TheArc = new Geom_TrimmedCurve(Circ, Alpha1, Alpha2, sense);

	return TheArc;
}


Handle(Geom_TrimmedCurve) BuildArc(gp_Ax1 axis, gp_Pnt p1, gp_Pnt p2)
{
	gp_Pnt arcCenter = axis.Location();
	gp_Ax2 centerCoord;
	centerCoord.SetAxis(axis);

	Geom_Circle acirc(centerCoord, arcCenter.Distance(p1));
	Handle(Geom_TrimmedCurve) anArcOfCircle = GC_MakeArcOfCircle(acirc.Circ(), p1, p2, true);

	return anArcOfCircle;
}

Handle(Geom_BSplineCurve) GetBSplineCurve(TColgp_Array1OfPnt& pPoints)
{
	GeomAPI_PointsToBSpline PTBS1(pPoints);
	Handle(Geom_BSplineCurve) C1 = PTBS1.Curve();
	return C1;
}

Handle(Geom_Curve) GetCurve(gp_Circ& C)
{
	Handle(Geom_Circle) aCir = new Geom_Circle(C);
	return aCir;
}

Handle(Geom_TrimmedCurve) CreateLine(gp_Pnt& P1, gp_Pnt& P2)
{
	Handle(Geom_TrimmedCurve) Line = GC_MakeSegment(P1, P2).Value();
	return Line;
}

TopoDS_Wire CreateRectangle(gp_Ax2& Plane, gp_Pnt2d& Pos, Standard_Real Length, Standard_Real Width)
{
	// Points
	Standard_Real xp = Pos.X();
	Standard_Real yp = Pos.Y();

	// Create 2d Sketch on x-y plane
	gp_Pnt2d P1(xp, yp);
	gp_Pnt2d P2(xp + Length, yp);
	gp_Pnt2d P3(xp + Length, yp + Width);
	gp_Pnt2d P4(xp, yp + Width);

	// Create 2D Lines
	Handle(Geom2d_TrimmedCurve) L1 = GCE2d_MakeSegment(P1, P2).Value();
	Handle(Geom2d_TrimmedCurve) L2 = GCE2d_MakeSegment(P2, P3).Value();
	Handle(Geom2d_TrimmedCurve) L3 = GCE2d_MakeSegment(P3, P4).Value();
	Handle(Geom2d_TrimmedCurve) L4 = GCE2d_MakeSegment(P4, P1).Value();

	// Convert 2d curves to 3d
	Handle(Geom_Curve) C3d1 = GeomLib::To3d(Plane, L1);
	Handle(Geom_Curve) C3d2 = GeomLib::To3d(Plane, L2);
	Handle(Geom_Curve) C3d3 = GeomLib::To3d(Plane, L3);
	Handle(Geom_Curve) C3d4 = GeomLib::To3d(Plane, L4);

	TColGeom_Array1OfCurve Curves(1, 4);
	Curves.SetValue(1, C3d1);
	Curves.SetValue(2, C3d2);
	Curves.SetValue(3, C3d3);
	Curves.SetValue(4, C3d4);

	TopoDS_Wire W = CreateWire(Curves);

	return W;
}

//=======================================================================
//Class    :	Topology functions
//purpose  :	
//=======================================================================
// 

TopoDS_Vertex CreateVertex(gp_Pnt P1)
{
	TopoDS_Vertex V = BRepBuilderAPI_MakeVertex(P1);
	return V;
}

TopoDS_Edge CreateEdge(gp_Pnt P1, gp_Pnt P2)
{
	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(P1, P2);
	return E;
}

TopoDS_Edge CreateEdge(TopoDS_Vertex& V1, TopoDS_Vertex& V2)
{
	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(V1, V2);
	return E;
}

TopoDS_Edge CreateEdge(Handle(Geom_Curve)& L)
{
	TopoDS_Edge E = BRepBuilderAPI_MakeEdge(L);
	return E;
}

TopoDS_Wire CreateWire(Handle(Geom_Curve)& L)
{
	TopoDS_Edge E = CreateEdge(L);
	TopoDS_Wire aWire = CreateWire(E);

	return aWire;
}

TopoDS_Wire CreateWire(TopoDS_Edge& E)
{
	BRepBuilderAPI_MakeWire MP;
	MP.Add(E);
	TopoDS_Wire aWire;

	if (MP.IsDone())
	{
		aWire = MP.Wire();
	}

	return aWire;
}

TopoDS_Wire CreateWire(TopTools_Array1OfShape& Edges)
{
	BRepBuilderAPI_MakeWire MP;

	for (int i = Edges.Lower(); i <= Edges.Upper(); i++)
	{
		MP.Add(TopoDS::Edge(Edges.Value(i)));
	}

	TopoDS_Wire aWire;

	if (MP.IsDone())
	{
		aWire = MP.Wire();
	}

	return aWire;
}

TopoDS_Wire CreateWire(TColGeom_Array1OfCurve& Curves)
{
	int lower = Curves.Lower();
	int upper = Curves.Upper();

	TopTools_Array1OfShape aEdges(lower, upper);

	for (int i = Curves.Lower(); i <= Curves.Upper(); i++)
	{
		Handle(Geom_Curve) C3d = Curves.Value(i);
		TopoDS_Edge E = CreateEdge(C3d);
		if (!E.IsNull())
		{
			aEdges.SetValue(i, E);
		}
	}

	TopoDS_Wire aWire = CreateWire(aEdges);
	return aWire;
}

// Face Creation Functions
TopoDS_Face CreateFace(TopoDS_Wire& Wire)
{
	TopoDS_Face aFace = BRepBuilderAPI_MakeFace(Wire, false);
	return aFace;
}

TopoDS_Face CreateFace(TColgp_Array1OfPnt& pPoints)
{
	BRepBuilderAPI_MakePolygon MP;

	for (int i = pPoints.Lower(); i <= pPoints.Upper(); i++)
	{
		MP.Add(pPoints.Value(i));
	}

	MP.Close();

	TopoDS_Wire aWire = MP.Wire();

	TopoDS_Face aFace = CreateFace(aWire);
	return aFace;
}

TopoDS_Face CreateFace(TopTools_Array1OfShape& Edges)
{
	BRepBuilderAPI_MakeWire MP;

	for (int i = Edges.Lower(); i <= Edges.Upper(); i++)
	{
		MP.Add(TopoDS::Edge(Edges.Value(i)));
	}

	TopoDS_Wire aWire = MP.Wire();

	TopoDS_Face aFace = CreateFace(aWire);
	return aFace;
}

TopoDS_Face CreateFace(TColGeom_Array1OfCurve& Curves)
{
	int lower = Curves.Lower();
	int upper = Curves.Upper();

	TopTools_Array1OfShape aEdges(lower, upper);

	for (int i = Curves.Lower(); i <= Curves.Upper(); i++)
	{
		Handle(Geom_Curve) C3d = Curves.Value(i);
		TopoDS_Edge E = CreateEdge(C3d);
		if (!E.IsNull())
		{
			aEdges.SetValue(i, E);
		}
	}

	TopoDS_Face aFace = CreateFace(aEdges);
	return aFace;
}

TopoDS_Face CreateFace(Handle(Geom_Curve)& L)
{
	TopoDS_Wire W = CreateWire(L);
	TopoDS_Face aFace = CreateFace(W);
	return aFace;
}

TopoDS_Face CreateFaceWithHole(TopoDS_Wire& OuterWire, TopoDS_Wire& InnerWire)
{
	// Face with outer wire
	TopoDS_Face aFace = CreateFace(OuterWire);

	//Init brep builder utility
	BRep_Builder aBuilder;

	//Add inner bound. Must be reversed
	aBuilder.Add(aFace, InnerWire.Reversed());

	return aFace;
}

TopoDS_Face CreateFaceWithHole(TopoDS_Wire& OuterWire, TopTools_Array1OfShape& InnerWires)
{
	// Face with outer wire
	TopoDS_Face aFace = CreateFace(OuterWire);

	//Init brep builder utility
	BRep_Builder aBuilder;

	for (int i = InnerWires.Lower(); i <= InnerWires.Upper(); i++)
	{
		TopoDS_Wire W = TopoDS::Wire(InnerWires.Value(i));
		aBuilder.Add(aFace, W.Reversed());
	}

	return aFace;
}

TopoDS_Shell CreateShell(Handle(Geom_Surface)& S)
{
	BRepBuilderAPI_MakeShell MS(S);
	TopoDS_Shell aShell = MS.Shell();
	return aShell;
}

TopoDS_Solid CreateSolid(TopTools_Array1OfShape& Shells)
{
	BRepBuilderAPI_MakeSolid MS;
	TopoDS_Solid aSolid;

	for (int i = Shells.Lower(); i <= Shells.Upper(); i++)
	{
		MS.Add(TopoDS::Shell(Shells.Value(i)));
	}

	if (MS.IsDone())
	{
		aSolid = MS.Solid();
	}

	return aSolid;
}

//=======================================================================
//Class    :	Topology Operation functions
//purpose  :	
//=======================================================================

TopoDS_Shape Extrude(TopoDS_Face& skface, TopoDS_Shape& abase, Standard_Real height, Standard_Boolean bMidplane, gp_Vec avec)
{
	TopoDS_Shape shape;

	if (height > 0)
	{
		gp_Dir adir = ExtractDirection(skface);
		gp_Vec anvec(adir);

		if (bMidplane)
		{
			anvec.Multiply(height * 0.5);
		}
		else
		{
			anvec.Multiply(height);
		}

		if (abase.IsNull())
		{
			if (bMidplane)
			{
				TopoDS_Shape S1 = BRepPrimAPI_MakePrism(skface, anvec);
				anvec.Reverse();
				TopoDS_Shape S2 = BRepPrimAPI_MakePrism(skface, anvec);
				shape = BooleanAdd(S1, S2);
			}
			else
			{
				shape = BRepPrimAPI_MakePrism(skface, anvec);
			}

		}
		else
		{
			BRepFeat_MakePrism thePrism(abase, skface, TopoDS_Face(), adir, Standard_True, Standard_True);
			thePrism.Perform(height);
			if (thePrism.IsDone())
			{
				shape = thePrism;
			}
		}
	}
	else
	{
		if (abase.IsNull())
		{
			shape = BRepPrimAPI_MakePrism(skface, avec);
		}
		else
		{

		}
	}

	return shape;
}

TopoDS_Shape ExtrudeCut(TopoDS_Face& skface, TopoDS_Shape& abase, Standard_Real height)
{
	if (abase.IsNull())
		return TopoDS_Shape();

	TopoDS_Shape shape;

	if (height > 0)
	{
		gp_Dir adir = ExtractDirection(skface);
		adir.Reverse();

		BRepFeat_MakePrism thePrism(abase, skface, TopoDS_Face(), adir, Standard_False, Standard_True);
		thePrism.Perform(height);
		if (thePrism.IsDone())
		{
			shape = thePrism;
		}
	}

	return shape;
}

TopoDS_Shape Revolve(TopoDS_Shape& rshape, gp_Ax1 axis, double angleRad)
{
	TopoDS_Shape aRevShp = BRepPrimAPI_MakeRevol(rshape, axis, angleRad);
	return aRevShp;
}

TopoDS_Face AddFilletToFace(TopoDS_Face& skFace, gp_Pnt aPnt, Standard_Real Radius)
{
	BRepFilletAPI_MakeFillet2d builder(skFace);
	TopoDS_Vertex aV = GetVertex(skFace, aPnt);
	builder.AddFillet(aV, Radius);
	TopoDS_Face afilletFace = TopoDS::Face(builder.Shape());
	return afilletFace;
}

TopoDS_Shape Add3DFillet(TopoDS_Shape& aShape, TopTools_Array1OfShape& Edges, double radius)
{
	BRepFilletAPI_MakeFillet builder(aShape);

	for (int i = Edges.Lower(); i <= Edges.Upper(); i++)
	{
		builder.Add(radius, TopoDS::Edge(Edges.Value(i)));
	}

	TopoDS_Shape filletedBody = builder.Shape();

	return filletedBody;
}

TopoDS_Shape Add3DChamfer(TopoDS_Shape& aShape, TopoDS_Edge& Edge, double dist1, double dist2, TopoDS_Face& Face)
{
	BRepFilletAPI_MakeChamfer MC(aShape);
	MC.Add(dist1, dist2, Edge, Face);
	TopoDS_Shape chamferBody = MC.Shape();

	return MC.Shape();
}

//=======================================================================
//Class    :	Transformation functions
//purpose  :	
//=======================================================================

TopoDS_Shape TranslatedShape(TopoDS_Shape& tshape, gp_Vec vec)
{
	// Geometric transformation
	gp_Trsf m_TranslateTransform;

	// Set translation vector
	m_TranslateTransform.SetTranslation(vec);

	// Initiate transformation 
	BRepBuilderAPI_Transform m_shapeTrsf(tshape, m_TranslateTransform, false);

	// Get translated shape
	TopoDS_Shape TS = m_shapeTrsf.Shape();

	return TS;
}

TopoDS_Shape RotatedShape(TopoDS_Shape& rshape, gp_Ax1 axis, double angle)
{
	// Geometric transformation
	gp_Trsf m_RotTransform;

	// Set Rotation axis
	m_RotTransform.SetRotation(axis, angle);

	// Initiate transformation 
	BRepBuilderAPI_Transform m_shapeTrsf(rshape, m_RotTransform, false);

	// Get rotated shape
	TopoDS_Shape RS = m_shapeTrsf.Shape();

	return RS;
}

TopoDS_Shape MirrorSketch(gp_Ax1& Axis, TopoDS_Wire& skWire)
{
	// Mirror Sketch profile
	gp_Trsf aTrsf;
	aTrsf.SetMirror(Axis);
	BRepBuilderAPI_Transform aBRepTrsf(skWire, aTrsf);
	TopoDS_Shape aMirroredShape = aBRepTrsf.Shape();
	TopoDS_Wire aMirroredWire = TopoDS::Wire(aMirroredShape);

	BRepBuilderAPI_MakeWire mkWire;
	mkWire.Add(skWire);
	mkWire.Add(aMirroredWire);
	TopoDS_Wire myWireProfile = mkWire.Wire();

	return myWireProfile;
}

TopoDS_Shape MirrorShape(TopoDS_Shape& mshape, gp_Pln aPlane)
{
	// Get Coordinate System of plane
	gp_Ax3 ax3 = aPlane.Position();
	gp_Ax2 ax2 = ax3.Ax2();

	// Set Mirror Plane 
	gp_Trsf aMirrorTrsf;
	aMirrorTrsf.SetMirror(ax2);

	// Initiate transformation
	BRepBuilderAPI_Transform m_shapeTrsf(mshape, aMirrorTrsf, false);

	// Get mirror shape
	TopoDS_Shape MS = m_shapeTrsf.Shape();

	return MS;
}


//=======================================================================
//Class    :	Boolean functions
//purpose  :	
//=======================================================================

TopoDS_Shape BooleanAdd(TopoDS_Shape& A, TopoDS_Shape& B)
{
	TopoDS_Shape result = BRepAlgoAPI_Fuse(A, B);
	return result;
}

TopoDS_Shape BooleanCut(TopoDS_Shape& A, TopoDS_Shape& B)
{
	TopoDS_Shape result = BRepAlgoAPI_Cut(A, B);
	return result;
}

TopoDS_Shape BooleanCommon(TopoDS_Shape& A, TopoDS_Shape& B)
{
	TopoDS_Shape result = BRepAlgoAPI_Common(A, B);
	return result;
}

//=======================================================================
//Class    :	Utility functions
//purpose  :	
//=======================================================================

gp_Dir ExtractDirection(TopoDS_Face& face)
{
	Handle(Geom_Surface) surf = BRep_Tool::Surface(face);
	Handle(Geom_Plane) Pl = Handle(Geom_Plane)::DownCast(surf);
	gp_Pln P = Pl->Pln();
	if (face.Orientation() == TopAbs_Orientation::TopAbs_REVERSED)
	{
		return P.Axis().Direction().Reversed();
	}

	return P.Axis().Direction();
}

gp_Ax2 GetCoordinateSystem(TopoDS_Face& face)
{
	CString asurfType = GetSurfaceType(face);

	if (asurfType == "PLANAR")
	{
		Handle(Geom_Surface) surf = BRep_Tool::Surface(face);
		Handle(Geom_Plane) Pl = Handle(Geom_Plane)::DownCast(surf);
		gp_Pln P = Pl->Pln();
		gp_Ax3 Pos = P.Position();
		gp_Ax2 CSys = Pos.Ax2();
		return CSys;
	}

	return gp_Ax2();	// Null
}

TopoDS_Face GetNearestFace(TopoDS_Shape& theShape, gp_Pnt P)
{
	if (theShape.IsNull())
		return TopoDS_Face();

	if (theShape.ShapeType() != TopAbs_ShapeEnum::TopAbs_SOLID)
		return TopoDS_Face();

	TopExp_Explorer exp;
	for (exp.Init(theShape, TopAbs_FACE); exp.More(); exp.Next())
	{
		TopoDS_Face F = TopoDS::Face(exp.Current());
		Handle(Geom_Surface) aSurf = GetSurface(F);
		if (IsPointOnSurface(aSurf, P))
		{
			return F;
		}
	}

	return TopoDS_Face();
}

TopoDS_Edge GetNearestEdge(TopoDS_Shape& theShape, gp_Pnt P)
{
	if (theShape.IsNull())
		return TopoDS_Edge();

	TopExp_Explorer exp;
	for (exp.Init(theShape, TopAbs_EDGE); exp.More(); exp.Next())
	{
		TopoDS_Edge E = TopoDS::Edge(exp.Current());
		Handle(Geom_Curve) aCurve = GetCurve(E);
		if (IsPointOnCurve(aCurve, P))
		{
			return E;
		}
	}

	return TopoDS_Edge();
}

TopoDS_Vertex GetVertex(TopoDS_Face& aFace, gp_Pnt aPnt)
{
	TopoDS_Vertex aV;
	TopExp_Explorer ex1(aFace, TopAbs_VERTEX);
	while (ex1.More())
	{
		aV = TopoDS::Vertex(ex1.Current());
		gp_Pnt pnt = BRep_Tool::Pnt(aV);
		if (pnt.IsEqual(aPnt, 0.001))
		{
			return aV;
		}
		ex1.Next();
	}
	return aV;
}

CString GetSurfaceType(TopoDS_Face& aFace)
{
	CString asurfType;
	asurfType = "";

	BRepAdaptor_Surface surface = BRepAdaptor_Surface(aFace);

	double u = (surface.FirstUParameter() + surface.LastUParameter()) / 2.0;
	double v = (surface.FirstVParameter() + surface.LastVParameter()) / 2.0;

	BRepLProp_SLProps surfaceProps(surface, u, v, 2, gp::Resolution());
	if (surfaceProps.MeanCurvature() == 0.0)
	{
		// Surface is a plane
		asurfType = "PLANAR";
	}
	else
	{
		// Surface is not a plane
		asurfType = "NONPLANAR";
	}

	return asurfType;
}

gp_Pln GetPlaneFromFace(TopoDS_Face& face)
{
	CString asurfType = GetSurfaceType(face);

	if (asurfType == "PLANAR")
	{
		Handle(Geom_Surface) surf = BRep_Tool::Surface(face);
		Handle(Geom_Plane) Pl = Handle(Geom_Plane)::DownCast(surf);
		return Pl->Pln();
	}

	return gp_Pln();	// Null
}

Handle(Geom_Surface) GetSurface(TopoDS_Face& face)
{
	Handle(Geom_Surface) surf = BRep_Tool::Surface(face);
	return surf;
}

Handle(Geom_Curve) GetCurve(TopoDS_Edge& aEdge)
{
	Standard_Real first, last;
	Handle(Geom_Curve) aCurve = BRep_Tool::Curve(aEdge, first, last);
	return aCurve;
}

bool IsPointOnCurve(Handle(Geom_Curve)& aCurve, gp_Pnt Point)
{
	bool res = false;

	Standard_Real 	MaxDist = 0.0001;
	Standard_Real U;

	res = GeomLib_Tool::Parameter(aCurve, Point, MaxDist, U);

	return res;
}

bool IsPointOnSurface(Handle(Geom_Surface)& aSurf, gp_Pnt Point)
{
	bool res = false;

	Standard_Real 	MaxDist = 0.0001;
	Standard_Real U;
	Standard_Real V;

	res = GeomLib_Tool::Parameters(aSurf, Point, MaxDist, U, V);

	return res;
}

