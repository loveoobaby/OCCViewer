#include "pch.h"
#include "AISCurve.h"
#include <StdPrs_PoleCurve.hxx>
#include <StdPrs_Curve.hxx>

IMPLEMENT_STANDARD_RTTIEXT(AISCurve, AIS_InteractiveObject)

AISCurve::AISCurve(const Handle(Geom_Curve)& theCurve,
	const Aspect_TypeOfLine aTypeOfline,
	const Standard_Integer aWidthOfLine,
	const Quantity_Color theColor)
{
	myGeom3dCurve = theCurve;
	myTypeOfLine = aTypeOfline;
	myWidthOfLine = aWidthOfLine;
	myDisplayPole = Standard_False;
	myDiscretisation = 20;
	myradiusmax = 10;
	myradiusratio = 1;
	myColor = theColor;
	Is2d = Standard_False;
}

AISCurve::AISCurve(const Handle(Geom2d_Curve)& theCurve2d,
	const Aspect_TypeOfLine aTypeOfline,
	const Standard_Integer aWidthOfLine,
	const Quantity_Color theColor)
{
	myGeom2dCurve = theCurve2d;
	myTypeOfLine = aTypeOfline;
	myWidthOfLine = aWidthOfLine;
	myDisplayPole = Standard_False;
	myDiscretisation = 20;
	myradiusmax = 10;
	myradiusratio = 1;
	myColor = theColor;
	Is2d = Standard_True;
}

void AISCurve::Compute(const Handle(PrsMgr_PresentationManager)& aPresentationManager,
	const Handle(Prs3d_Presentation)& thePrs,
	const Standard_Integer aMode)
{
	if (Is2d)
	{
		Build2DCurve(aPresentationManager, thePrs, aMode);
	}
	else
	{
		Build3DCurve(aPresentationManager, thePrs, aMode);
	}
}

void AISCurve::Build3DCurve(const Handle(PrsMgr_PresentationManager)& aPresentationManager,
	const Handle(Prs3d_Presentation)& thePrs,
	const Standard_Integer aMode)
{

	myDrawer->LineAspect()->Aspect()->SetColor(myColor);
	myDrawer->PointAspect()->Aspect()->SetColor(myColor);
	myDrawer->PointAspect()->Aspect()->SetLineWidth(myWidthOfLine);

	GeomAdaptor_Curve anAdaptorCurve(myGeom3dCurve);
	switch (aMode)
	{
	case 1:
	{
		Handle(Prs3d_Drawer) aPoleDrawer = new Prs3d_Drawer();
		aPoleDrawer->SetLineAspect(new Prs3d_LineAspect(Quantity_NOC_RED, Aspect_TOL_SOLID, 1.0));
		StdPrs_PoleCurve::Add(thePrs, anAdaptorCurve, aPoleDrawer);
	}
	case 0:
	{
		StdPrs_Curve::Add(thePrs, anAdaptorCurve, myDrawer);
		break;
	}
	}
}

void AISCurve::Build2DCurve(const Handle(PrsMgr_PresentationManager)& aPresentationManager,
	const Handle(Prs3d_Presentation)& thePrs,
	const Standard_Integer)
{

	Handle(Graphic3d_Group) aPrsGroup = thePrs->CurrentGroup();

	myDrawer->LineAspect()->Aspect()->SetColor(myColor);
	myDrawer->PointAspect()->Aspect()->SetColor(myColor);
	myDrawer->PointAspect()->Aspect()->SetLineWidth(myWidthOfLine);

	aPrsGroup->SetGroupPrimitivesAspect(myDrawer->LineAspect()->Aspect());
	aPrsGroup->SetGroupPrimitivesAspect(myDrawer->PointAspect()->Aspect());

	Geom2dAdaptor_Curve anAdaptor(myGeom2dCurve);
	GCPnts_QuasiUniformDeflection anEdgeDistrib(anAdaptor, 1.e-2);

	if (anEdgeDistrib.IsDone())
	{
		Handle(Graphic3d_ArrayOfPolylines) aCurve =
			new Graphic3d_ArrayOfPolylines(anEdgeDistrib.NbPoints());
		for (Standard_Integer i = 1; i <= anEdgeDistrib.NbPoints(); ++i)
			aCurve->AddVertex(anEdgeDistrib.Value(i));

		aPrsGroup->AddPrimitiveArray(aCurve);
	}

	if (myDisplayPole)
	{
		if (anAdaptor.GetType() == GeomAbs_BezierCurve)
		{
			Handle(Geom2d_BezierCurve) aBezier = anAdaptor.Bezier();
			Handle(Graphic3d_ArrayOfPolylines) anArrayOfVertex = new Graphic3d_ArrayOfPolylines(aBezier->NbPoles());
			for (int i = 1; i <= aBezier->NbPoles(); i++)
			{
				gp_Pnt2d CurrentPoint = aBezier->Pole(i);
				anArrayOfVertex->AddVertex(CurrentPoint.X(), CurrentPoint.Y(), 0.);
			}
			aPrsGroup->AddPrimitiveArray(anArrayOfVertex);
		}

		if (anAdaptor.GetType() == GeomAbs_BSplineCurve)
		{
			Handle(Geom2d_BSplineCurve) aBSpline = anAdaptor.BSpline();

			Handle(Graphic3d_ArrayOfPolylines) anArrayOfVertex =
				new Graphic3d_ArrayOfPolylines(aBSpline->NbPoles());

			for (int i = 1; i <= aBSpline->NbPoles(); i++)
			{
				gp_Pnt2d CurrentPoint = aBSpline->Pole(i);
				anArrayOfVertex->AddVertex(CurrentPoint.X(), CurrentPoint.Y(), 0.);
			}
			aPrsGroup->AddPrimitiveArray(anArrayOfVertex);
		}
	}

}
