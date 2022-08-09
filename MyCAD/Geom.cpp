#include "pch.h"
#include "framework.h"

#include "MyCADDoc.h"
#include "MyCADView.h"

//================================================================================================
// Geometry functions
//================================================================================================

void CMyCADDoc::Create2DGeometry()
{
	bIs2d = true;

	// Co-ordinates
	gp_Pnt2d Cnt1(20, 20);
	gp_Pnt2d Cnt2(120, 25);
	gp_Pnt2d Cnt3(120, 115);
	gp_Pnt2d Cnt4(20, 120);

	gp_Pnt2d P1(20, 0);
	gp_Pnt2d P2(120, 0);
	gp_Pnt2d P3(170, 25);
	gp_Pnt2d P4(170, 115);

	gp_Pnt2d P5(120, 140);
	gp_Pnt2d P6(20, 140);
	gp_Pnt2d P7(0, 120);
	gp_Pnt2d P8(0, 20);

	// Lines
	Handle(Geom2d_TrimmedCurve) L1 = GCE2d_MakeSegment(P1, P2).Value();
	Handle(Geom2d_TrimmedCurve) L2 = GCE2d_MakeSegment(P3, P4).Value();
	Handle(Geom2d_TrimmedCurve) L3 = GCE2d_MakeSegment(P5, P6).Value();
	Handle(Geom2d_TrimmedCurve) L4 = GCE2d_MakeSegment(P7, P8).Value();

	// Arcs
	gp_Dir2d D(1, 0);

	// first circular arc
	gp_Ax2d Ax1(Cnt1, D);
	gp_Circ2d gC1(Ax1, 20);
	Handle(Geom2d_TrimmedCurve) C1 = GCE2d_MakeArcOfCircle(gC1, P8, P1).Value();

	// Second circular arc
	gp_Ax2d Ax2(Cnt4, D);
	gp_Circ2d gC2(Ax2, 20);
	Handle(Geom2d_TrimmedCurve) C2 = GCE2d_MakeArcOfCircle(gC2, P6, P7).Value();

	// first elliptical arc
	gp_Ax2d Ax3(Cnt2, D);
	gp_Elips2d gE1(Ax3, 50, 25);
	Handle(Geom2d_TrimmedCurve) E1 = GCE2d_MakeArcOfEllipse(gE1, P2, P3).Value();

	// Second elliptical arc
	gp_Ax2d Ax4(Cnt3, D);
	gp_Elips2d gE2(Ax4, 50, 25);
	Handle(Geom2d_TrimmedCurve) E2 = GCE2d_MakeArcOfEllipse(gE2, P4, P5).Value();

	// Save curves
	// Save curves in anticlockwise sequence
	Curves2d.Resize(1, 8, false);
	Curves2d.SetValue(1, L1);
	Curves2d.SetValue(2, E1);
	Curves2d.SetValue(3, L2);
	Curves2d.SetValue(4, E2);
	Curves2d.SetValue(5, L3);
	Curves2d.SetValue(6, C2);
	Curves2d.SetValue(7, L4);
	Curves2d.SetValue(8, C1);

	Pnts2d.Resize(1, 12, false);
	Pnts2d.SetValue(1, P1);
	Pnts2d.SetValue(2, P2);
	Pnts2d.SetValue(3, P3);
	Pnts2d.SetValue(4, P4);
	Pnts2d.SetValue(5, P5);
	Pnts2d.SetValue(6, P6);
	Pnts2d.SetValue(7, P7);
	Pnts2d.SetValue(8, P8);
	Pnts2d.SetValue(9, Cnt1);
	Pnts2d.SetValue(10, Cnt2);
	Pnts2d.SetValue(11, Cnt3);
	Pnts2d.SetValue(12, Cnt4);
}

void CMyCADDoc::Create3DGeometry()
{
	bIs2d = false;

	// Create Points
	gp_Pnt P1(0, 0, 0);
	gp_Pnt P2(75, 0, 0);
	gp_Pnt P3(95, 0, 20);
	gp_Pnt P4(95, 0, 115);
	gp_Pnt P5(75, 0, 135);
	gp_Pnt P6(-15, 0, 135);
	gp_Pnt P7(-35, 20, 135);
	gp_Pnt P8(-35, 95, 135);
	gp_Pnt P9(-55, 115, 135);
	gp_Pnt P10(-135, 115, 135);
	gp_Pnt P11(-155, 95, 135);
	gp_Pnt P12(-155, 20, 135);
	gp_Pnt P13(-155, 0, 155);
	gp_Pnt P14(-155, 0, 210);

	gp_Pnt Cnt1(75, 0, 20);
	gp_Pnt Cnt2(75, 0, 115);
	gp_Pnt Cnt3(-15, 20, 135);
	gp_Pnt Cnt4(-55, 95, 135);
	gp_Pnt Cnt5(-135, 95, 135);
	gp_Pnt Cnt6(-155, 20, 155);

	// Lines
	Handle(Geom_TrimmedCurve) L1 = GC_MakeSegment(P1, P2).Value();
	Handle(Geom_TrimmedCurve) L2 = GC_MakeSegment(P3, P4).Value();
	Handle(Geom_TrimmedCurve) L3 = GC_MakeSegment(P5, P6).Value();
	Handle(Geom_TrimmedCurve) L4 = GC_MakeSegment(P7, P8).Value();
	Handle(Geom_TrimmedCurve) L5 = GC_MakeSegment(P9, P10).Value();
	Handle(Geom_TrimmedCurve) L6 = GC_MakeSegment(P11, P12).Value();
	Handle(Geom_TrimmedCurve) L7 = GC_MakeSegment(P13, P14).Value();

	// Arcs
	gp_Dir D(0, 1, 0);

	// first circular arc
	gp_Ax2 Ax1(Cnt1, D);
	gp_Circ gC1(Ax1, 20);
	Handle(Geom_TrimmedCurve) C1 = GC_MakeArcOfCircle(gC1, P3, P2, true).Value();

	gp_Ax2 Ax2(Cnt2, D);
	gp_Circ gC2(Ax2, 20);
	Handle(Geom_TrimmedCurve) C2 = GC_MakeArcOfCircle(gC2, P5, P4, true).Value();

	gp_Dir D2(0, 0, 1);
	gp_Ax2 Ax3(Cnt3, D2);
	gp_Circ gC3(Ax3, 20);
	Handle(Geom_TrimmedCurve) C3 = GC_MakeArcOfCircle(gC3, P7, P6, true).Value();

	gp_Ax2 Ax4(Cnt4, D2);
	gp_Circ gC4(Ax4, 20);
	Handle(Geom_TrimmedCurve) C4 = GC_MakeArcOfCircle(gC4, P8, P9, true).Value();

	gp_Ax2 Ax5(Cnt5, D2);
	gp_Circ gC5(Ax5, 20);
	Handle(Geom_TrimmedCurve) C5 = GC_MakeArcOfCircle(gC5, P10, P11, true).Value();

	gp_Dir D3(1, 0, 0);
	gp_Ax2 Ax6(Cnt6, D3);
	gp_Circ gC6(Ax6, 20);
	Handle(Geom_TrimmedCurve) C6 = GC_MakeArcOfCircle(gC6, P13, P12, true).Value();

	Curves3d.Resize(1, 13, false);
	Curves3d.SetValue(1, L1);
	Curves3d.SetValue(2, C1);
	Curves3d.SetValue(3, L2);
	Curves3d.SetValue(4, C2);
	Curves3d.SetValue(5, L3);
	Curves3d.SetValue(6, C3);
	Curves3d.SetValue(7, L4);
	Curves3d.SetValue(8, C4);
	Curves3d.SetValue(9, L5);
	Curves3d.SetValue(10, C5);
	Curves3d.SetValue(11, L6);
	Curves3d.SetValue(12, C6);
	Curves3d.SetValue(13, L7);

	Pnts3d.Resize(1, 14, false);
	Pnts3d.SetValue(1, P1);
	Pnts3d.SetValue(2, P2);
	Pnts3d.SetValue(3, P3);
	Pnts3d.SetValue(4, P4);
	Pnts3d.SetValue(5, P5);
	Pnts3d.SetValue(6, P6);
	Pnts3d.SetValue(7, P7);
	Pnts3d.SetValue(8, P8);
	Pnts3d.SetValue(9, P9);
	Pnts3d.SetValue(10, P10);
	Pnts3d.SetValue(11, P11);
	Pnts3d.SetValue(12, P12);
	Pnts3d.SetValue(13, P13);
	Pnts3d.SetValue(14, P14);

}

void CMyCADDoc::CreateBSplineCurve()
{
	bIs2d = false;

	// Create Points
	gp_Pnt P1(40, 0, 0);
	gp_Pnt P2(41, 5, 0);
	gp_Pnt P3(37, 11, 0);
	gp_Pnt P4(42, 17, 0);
	gp_Pnt P5(43, 22, 0);
	gp_Pnt P6(39, 27, 0);
	gp_Pnt P7(45, 33, 0);
	gp_Pnt P8(46, 38, 0);
	gp_Pnt P9(42, 44, 0);
	gp_Pnt P10(48, 50, 0);
	gp_Pnt P11(50, 55, 0);
	gp_Pnt P12(46, 61, 0);
	gp_Pnt P13(52, 67, 0);
	//gp_Pnt P14(53, 70, 0);

	Pnts3d.Resize(1, 12, false);
	//Pnts3d.SetValue(1, P1);
	Pnts3d.SetValue(1, P2);
	Pnts3d.SetValue(2, P3);
	Pnts3d.SetValue(3, P4);
	Pnts3d.SetValue(4, P5);
	Pnts3d.SetValue(5, P6);
	Pnts3d.SetValue(6, P7);
	Pnts3d.SetValue(7, P8);
	Pnts3d.SetValue(8, P9);
	Pnts3d.SetValue(9, P10);
	Pnts3d.SetValue(10, P11);
	Pnts3d.SetValue(11, P12);
	Pnts3d.SetValue(12, P13);
	//Pnts3d.SetValue(14, P14);

	aBSCrv = GetBSplineCurve(Pnts3d);
	Curves3d.Resize(1, 1, false);
	Curves3d.SetValue(1, aBSCrv);

}

void CMyCADDoc::Create2DTO3DSketch()
{

	// Create 2D Sketch
	Create2DGeometry();

	bIs2d = false;

	// Create Plane defined by plane normal and local x-axis direction

	gp_Dir N(1, 0, 0);	    // x-axis in global CS
	gp_Dir Vx(0, 0, -1);	// z-axis in global CS
	gp_Pnt P(0, 0, 170);

	gp_Ax2 Plane(P, N, Vx);	// Right hand coordinate system

	GetView()->DisplayCSys(true, Plane);

	// Convert 2D curves to 3D on the defined plane
	int lower = Curves2d.Lower();
	int upper = Curves2d.Upper();

	Curves3d.Resize(lower, upper, false);
	for (int i = Curves2d.Lower(); i <= Curves2d.Upper(); i++)
	{
		Handle(Geom2d_Curve) C2d = Curves2d.Value(i);
		Handle(Geom_Curve) C3d = GeomLib::To3d(Plane, C2d);
		if (!C3d.IsNull())
		{
			Curves3d.SetValue(i, C3d);
		}
	}
}