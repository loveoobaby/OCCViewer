
// MyCADDoc.h: CMyCADDoc 类的接口
//


#pragma once
#include "OccFunctions.h"

class CMyCADView;

class CMyCADDoc : public CDocument
{
protected: // 仅从序列化创建
	CMyCADDoc() noexcept;
	DECLARE_DYNCREATE(CMyCADDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMyCADDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

protected:
	// Local Variables
	//==========================================================================
	bool bIs2d = true;

	TColgp_Array1OfPnt2d Pnts2d;			// Array of 2d points
	TColGeom2d_Array1OfCurve Curves2d;		// Array of 2d curves

	TColgp_Array1OfPnt Pnts3d;				// Array of 3d points
	TColGeom_Array1OfCurve Curves3d;		// Array of 3d curves
	Handle(Geom_BSplineCurve) aBSCrv;		// BSpline Curve

	TColGeom_Array1OfSurface Surf3D;		// Array of Surfaces	

	TopoDS_Shape Shape;						// Shape object

	CMyCADView* GetView();				// Viewer

	// General Display functions
	void DisplaySketch();
	void DisplaySurface();
	void DisplayPoints(TColgp_Array2OfPnt& Pnts);

public:

	// Modeling Functions
	//==========================================================================

	// 2D Geometry
	void Create2DGeometry();

	// 3D Geometry
	void Create3DGeometry();
	void CreateBSplineCurve();
	void Create2DTO3DSketch();

	// Topological Data structure
	void ExploreTopology();

	// 3D Modeling-I (Standard Topology)
	void CreatePrimitives();
	void CreateSketchFace();
	void CreateFaceWHoles();

	// 3D Modeling-II (Extrude/Revolve)
	void ExtrudeFace();
	void RevolveFace();

	void ExtrudeFeature();
	void ExtrudeCutFeature();

	void RevolveFeature();
	void RevolveCutFeature();

	// 3D Modeling-III (Sweep/Loft)
	void OffsetWire();
	void Sweep();
	void Loft();
	void ThickSolid();
	void Shelling();

	// 3D Modeling-IV Fillets / Chamfers
	void Fillet2D();
	void Chamfer2D();
	void Fillet3D();
	void Chamfer3D();

	// 3D Modeling-V Transformations
	void CreateBrg();
	void Translate();
	void Rotate();
	void Mirror();

	// 3D Modeling-VI Boolean Operations
	void CreateFlange();
	void CreatePipe();
	void AddBodies();
	void CutBody();

	// 3D Modeling-VII Surface Modelling - I
	void CylindricalSurface();
	void SphericalSurface();
	void PlaneSurface();

	void ExtrudeLinearSurface();
	void RevolveSurface();
	void LoftSurface();
	void ThickenSurface();

	void CreateBSplineSurface();

	// 3D Modeling-VIII Surface Modelling - II
	void CreateAppSurf();
	void CreateAppSweepSurf();
	void CreateLoftSurf();
	void CreateConstrainedSurface();
	void FillBSplineSurface();

	// 3D Modeling-IX Sewing
	void MakeSewedSolid();

	// 3D Model Properties
	void LinearProperties();
	void SurfaceProperties();
	void VolumeProperties();

	// 3D Model Bounding Boxes
	void BoundingBox();
	void OBBBoundingBox();

	// Visualization Functions
	//==========================================================================
	void ShowMesh();

	void LengthDimension();
	void RadiusDimension();
	void DiameterDimension();

	// Document Framework Functions
	//==========================================================================


	// Data Exchange Functions
	//==========================================================================
	void ImportStep();
	void ImportIGES();
	void ImportStl();

	void ExportStep();
	void ExportIGES();
	void ExportStl();


	afx_msg void On2dgeometry2dsketch();
	afx_msg void On3dgeometry3dsketch();
	afx_msg void On3dgeometryBsplinecurve();
	afx_msg void On3dgeometry2dto3d();
	afx_msg void OnTopologyExplore();
	afx_msg void OnTopologyPrimitives();
	afx_msg void OnTopologyCreateface();
	afx_msg void OnTopologyFacewithholes();
	afx_msg void On3dmodelingExtrudeface();
	afx_msg void On3dmodelingRevolveface();
	afx_msg void OnFeaturesExtrude();
	afx_msg void OnFeaturesExtrudecut();
	afx_msg void OnFeaturesRevolve();
	afx_msg void OnFeaturesRevolvecut();
	afx_msg void OnFeaturesOffset();
	afx_msg void OnFeaturesSweep();
	afx_msg void OnFeaturesLoft();
	afx_msg void OnFeaturesShell();
	afx_msg void On3dmodeling2dfillet();
	afx_msg void On3dmodeling2dchamfer();
	afx_msg void On3dmodeling3dfillet();
	afx_msg void On3dmodeling3dchamfer();
	afx_msg void OnTransformationsTranslate();
	afx_msg void OnTransformationsRotate();
	afx_msg void OnTransformationsMirror();
	afx_msg void OnBooleanoperationsAdd();
	afx_msg void OnBooleanoperationsCut();
	afx_msg void OnBoundingboxAxis();
	afx_msg void OnBoundingboxOriented();
	afx_msg void OnModelpropertiesLinearproperties();
	afx_msg void OnModelpropertiesSurfaceproperties();
	afx_msg void OnModelpropertiesVolumeproperties();
	afx_msg void OnElementaryCylinder();
	afx_msg void OnElementarySpherical();
	afx_msg void OnElementaryPlanar();
	afx_msg void OnSweptLinearextrusion();
	afx_msg void OnSweptRevolve();
	afx_msg void OnSweptLoft();
	afx_msg void OnSurfacemodelingThicken();
	afx_msg void OnSurfacemodelingBsplinesurface();
	afx_msg void OnAdvancedFillbsplines();
	afx_msg void OnAdvancedFillbsplinesurface();
	afx_msg void OnAdvancedFillbsplinesurface32836();
	afx_msg void OnAdvancedFillconstrainedsurface();
	afx_msg void OnAdvancedFillbsplinecurvesurface();
	afx_msg void OnSurfacemodelingSewsurfaces();
	afx_msg void OnDisplaymodeShaded();
	afx_msg void OnDisplaymodeWireframe();
	afx_msg void OnSelectionmodeVertex();
	afx_msg void OnSelectionmodeEdge();
	afx_msg void OnSelectionmodeFace();
	afx_msg void OnSelectionmodeSolid();
	afx_msg void OnFilterPlanarfaces();
	afx_msg void OnModelclippingNormalclipping();
	afx_msg void OnModelclippingClippingwithtexture();
	afx_msg void OnModelclippingClippingwithsection();
	afx_msg void OnVisualizationMesh();
	afx_msg void OnDimensionsLength();
	afx_msg void OnDimensionsRadius();
	afx_msg void OnDimensionsDiameter();
	afx_msg void OnImportIges();
	afx_msg void OnImportStep();
	afx_msg void OnImportStl();
	afx_msg void OnExportIges();
	afx_msg void OnExportStep();
	afx_msg void OnExportStl();




	afx_msg void OnCreate2dgeom2dstracth();
};
