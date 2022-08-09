#pragma once

#include "OccFunctions.h"

class AISCurve : public AIS_InteractiveObject
{
	DEFINE_STANDARD_RTTIEXT(AISCurve, AIS_InteractiveObject)

public:
	AISCurve(const Handle(Geom_Curve)& theCurve,
		const Aspect_TypeOfLine aTypeOfline = Aspect_TOL_SOLID,
		const Standard_Integer aWidthOfLine = 1.0,
		const Quantity_Color theColor = Quantity_NOC_BLUE);

	AISCurve(const Handle(Geom2d_Curve)& theCurve2d,
		const Aspect_TypeOfLine aTypeOfline = Aspect_TOL_SOLID,
		const Standard_Integer aWidthOfLine = 1.0,
		const Quantity_Color theColor = Quantity_NOC_BLUE);

	virtual ~AISCurve() {}

public:
	inline   Aspect_TypeOfLine  GetTypeOfLine() const;
	inline   void SetTypeOfLine(const Aspect_TypeOfLine aNewTypeOfLine);

	inline   Standard_Integer GetWidthOfLine() const;
	inline   void SetWidthOfLine(const Standard_Integer aNewWidthOfLine);

	inline   Standard_Integer GetColorIndex() const;
	inline   void SetColorIndex(const Standard_Integer aNewColorIndex);

	inline   Standard_Boolean GetDisplayPole() const;
	inline   void SetDisplayPole(const Standard_Boolean aNewDisplayPole);

	inline   Standard_Real GetDiscretisation() const;
	inline   void SetDiscretisation(const Standard_Real aNewDiscretisation);

private:

	Standard_EXPORT virtual  void Compute(const Handle(PrsMgr_PresentationManager)& aPresentationManager, const Handle(Prs3d_Presentation)& aPresentation, const Standard_Integer aMode = 0);
	virtual void ComputeSelection(const Handle(SelectMgr_Selection)&, const Standard_Integer) {}

	void Build3DCurve(const Handle(PrsMgr_PresentationManager)& aPresentationManager,
		const Handle(Prs3d_Presentation)& thePrs,
		const Standard_Integer aMode);
	void Build2DCurve(const Handle(PrsMgr_PresentationManager)& aPresentationManager,
		const Handle(Prs3d_Presentation)& thePrs,
		const Standard_Integer aMode);

private:
	Handle(Geom_Curve)   myGeom3dCurve;
	Handle(Geom2d_Curve) myGeom2dCurve;
	Aspect_TypeOfLine   myTypeOfLine;
	Standard_Integer    myWidthOfLine;
	Standard_Integer    myColorIndex;
	Standard_Boolean    myDisplayPole;
	Standard_Real       myDiscretisation;
	Standard_Real       myradiusmax;
	Standard_Real       myradiusratio;
	Quantity_Color      myColor;
	Standard_Boolean    Is2d;

};

//


inline  Aspect_TypeOfLine AISCurve::GetTypeOfLine() const
{
	return myTypeOfLine;
}

inline  void AISCurve::SetTypeOfLine(const Aspect_TypeOfLine aNewTypeOfLine)
{
	myTypeOfLine = aNewTypeOfLine;
}

inline  Standard_Integer AISCurve::GetWidthOfLine() const
{
	return myWidthOfLine;
}

inline  void AISCurve::SetWidthOfLine(const Standard_Integer aNewWidthOfLine)
{
	myWidthOfLine = aNewWidthOfLine;
}

inline  Standard_Integer AISCurve::GetColorIndex() const
{
	return myColorIndex;
}

inline  void AISCurve::SetColorIndex(const Standard_Integer aNewColorIndex)
{
	myColorIndex = aNewColorIndex;
}

inline   Standard_Boolean  AISCurve::GetDisplayPole
() const
{
	return myDisplayPole;
}

inline   void  AISCurve::SetDisplayPole
(const Standard_Boolean aNewDisplayPole)
{
	myDisplayPole = aNewDisplayPole;
}

inline   Standard_Real  AISCurve::GetDiscretisation
() const
{
	return myDiscretisation;
}

inline   void               AISCurve::SetDiscretisation
(const Standard_Real aNewDiscretisation)
{
	myDiscretisation = aNewDiscretisation;
}


