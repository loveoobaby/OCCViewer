#pragma once

//TKernal
 //--Standard
#include <Standard.hxx> 
#include <Standard_ErrorHandler.hxx>
#include <Standard_GUID.hxx> 
#include <Standard_MMgrRoot.hxx>
#include <Standard_MMgrOpt.hxx>
#include <Standard_MMgrRaw.hxx>
#include <Standard_Persistent.hxx>
#include <Standard_SStream.hxx>
#include <Standard_Transient.hxx>
#include <Standard_Failure.hxx>
#include <Standard_AbortiveTransaction.hxx> 
#include <Standard_DomainError.hxx>
#include <Standard_ConstructionError.hxx> 
#include <Standard_DimensionError.hxx>
#include <Standard_DimensionMismatch.hxx> 
#include <Standard_ImmutableObject.hxx>
#include <Standard_MultiplyDefined.hxx>
#include <Standard_NoMoreObject.hxx>
#include <Standard_NoSuchObject.hxx>
#include <Standard_NullObject.hxx>
#include <Standard_RangeError.hxx>
#include <Standard_NegativeValue.hxx> 
#include <Standard_NullValue.hxx>
#include <Standard_OutOfRange.hxx> 
#include <Standard_TypeMismatch.hxx> 
#include <Standard_LicenseError.hxx>
#include <Standard_LicenseNotFound.hxx> 
#include <Standard_TooManyUsers.hxx>
#include <Standard_NumericError.hxx>
#include <Standard_DivideByZero.hxx>
#include <Standard_Overflow.hxx>
#include <Standard_Underflow.hxx>
#include <Standard_ProgramError.hxx> 
#include <Standard_NotImplemented.hxx> 
#include <Standard_OutOfMemory.hxx>
#include <Standard_Type.hxx>
#include <Standard_Boolean.hxx>
#include <Standard_Version.hxx>
#include <Standard_DefineHandle.hxx>
#include <Standard_Macro.hxx>

//--Quantity
#include <Quantity_Array1OfColor.hxx>
#include <Quantity_Array2OfColor.hxx>
#include <Quantity_Color.hxx>
#include <Quantity_Date.hxx>
#include <Quantity_Period.hxx> 
#include <Quantity_HArray1OfColor.hxx> 
#include <Units_Quantity.hxx>
#include <Quantity_DateDefinitionError.hxx> 
#include <Quantity_PeriodDefinitionError.hxx>

#include <UnitsAPI.hxx>
#include <ElCLib.hxx>
#include <ElSLib.hxx> 

//collections
#include <TCollection_ExtendedString.hxx>
#include <TCollection_AsciiString.hxx>
#include <TCollection_AsciiString.hxx>

//--gp
#include <gp.hxx> 
#include <gp_Ax1.hxx> 
#include <gp_Ax2.hxx>
#include <gp_Ax22d.hxx> 
#include <gp_Ax2d.hxx>
#include <gp_Ax3.hxx>
#include <gp_Circ.hxx>
#include <gp_Circ2d.hxx> 
#include <gp_Cone.hxx>
#include <gp_Cylinder.hxx> 
#include <gp_Dir.hxx>
#include <gp_Dir2d.hxx> 
#include <gp_Elips.hxx>
#include <gp_Elips2d.hxx> 
#include <gp_GTrsf.hxx>
#include <gp_GTrsf2d.hxx> 
#include <gp_Hypr.hxx>
#include <gp_Hypr2d.hxx> 
#include <gp_Lin.hxx>
#include <gp_Lin2d.hxx> 
#include <gp_Mat.hxx>
#include <gp_Mat2d.hxx> 
#include <gp_Parab.hxx>
#include <gp_Parab2d.hxx> 
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx> 
#include <gp_Sphere.hxx> 
#include <gp_Torus.hxx>
#include <gp_Trsf.hxx>
#include <gp_Trsf2d.hxx> 
#include <gp_Vec.hxx>
#include <gp_Vec2d.hxx> 
#include <gp_XY.hxx>
#include <gp_XYZ.hxx>
#include <TColgp_HArray1OfCirc2d.hxx> 
#include <TColgp_HArray1OfDir.hxx>
#include <TColgp_HArray1OfDir2d.hxx> 
#include <TColgp_HArray1OfLin2d.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColgp_HArray1OfPnt2d.hxx> 
#include <TColgp_HArray1OfVec.hxx>
#include <TColgp_HArray1OfVec2d.hxx> 
#include <TColgp_HArray1OfXY.hxx>
#include <TColgp_HArray1OfXYZ.hxx>
#include <TColgp_HArray2OfCirc2d.hxx> 
#include <TColgp_HArray2OfDir.hxx>
#include <TColgp_HArray2OfDir2d.hxx> 
#include <TColgp_HArray2OfLin2d.hxx>
#include <TColgp_HArray2OfPnt2d.hxx> 
#include <TColgp_HArray2OfVec.hxx>
#include <TColgp_HArray2OfVec2d.hxx> 
#include <TColgp_HArray2OfXY.hxx>
#include <TColgp_HSequenceOfDir2d.hxx> 
#include <TColgp_HSequenceOfPnt.hxx>
#include <TColgp_HSequenceOfPnt2d.hxx> 
#include <TColgp_HSequenceOfVec.hxx>
#include <TColgp_HSequenceOfVec2d.hxx> 
#include <TColgp_HSequenceOfXY.hxx>
#include <TColgp_HSequenceOfXYZ.hxx>
#include <gp_VectorWithNullMagnitude.hxx>
#include <TColgp_Array1OfCirc2d.hxx>
#include <TColgp_Array1OfDir.hxx>
#include <TColgp_Array1OfDir2d.hxx> 
#include <TColgp_Array1OfLin2d.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array1OfPnt2d.hxx> 
#include <TColgp_Array1OfVec.hxx>
#include <TColgp_Array1OfXY.hxx>
#include <TColgp_Array1OfXYZ.hxx> 
#include <TColgp_Array2OfCirc2d.hxx> 
#include <TColgp_Array2OfDir.hxx>
#include <TColgp_Array2OfDir2d.hxx> 
#include <TColgp_Array2OfLin2d.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColgp_Array2OfPnt2d.hxx> 
#include <TColgp_Array2OfVec.hxx>
#include <TColgp_Array2OfVec2d.hxx> 
#include <TColgp_Array2OfXY.hxx>
#include <TColgp_Array2OfXYZ.hxx> 
#include <TColgp_SequenceOfDir.hxx> 
#include <TColgp_SequenceOfDir2d.hxx>
#include <TColgp_SequenceOfPnt.hxx>
#include <TColgp_SequenceOfPnt2d.hxx> 
#include <TColgp_SequenceOfVec.hxx>
#include <TColgp_SequenceOfVec2d.hxx> 
#include <TColgp_SequenceOfXY.hxx>
#include <TColgp_SequenceOfXYZ.hxx> 
#include <TopLoc_Datum3D.hxx>
#include <TopLoc_IndexedMapOfLocation.hxx>
#include <TopLoc_MapOfLocation.hxx>
#include <TopLoc_MapIteratorOfMapOfLocation.hxx> 
#include <TopLoc_ItemLocation.hxx>
#include <TopLoc_Location.hxx>
#include <TopLoc_MapLocationHasher.hxx> 
#include <TopLoc_SListOfItemLocation.hxx>

//Geom
#include <Geom_Geometry.hxx>
#include <Geom_AxisPlacement.hxx> 
#include <Geom_Axis1Placement.hxx> 
#include <Geom_Axis2Placement.hxx>
#include <Geom_Curve.hxx>
#include <Geom_BoundedCurve.hxx> 
#include <Geom_BezierCurve.hxx>
#include <Geom_BSplineCurve.hxx> 
#include <Geom_TrimmedCurve.hxx> 
#include <Geom_Conic.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Ellipse.hxx> 
#include <Geom_Parabola.hxx>
#include <Geom_Line.hxx>
#include <Geom_OffsetCurve.hxx> 
#include <Geom_Point.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BoundedSurface.hxx> 
#include <Geom_BezierSurface.hxx>
#include <Geom_BSplineSurface.hxx> 
#include <Geom_RectangularTrimmedSurface.hxx> 
#include <Geom_ElementarySurface.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom_CylindricalSurface.hxx> 
#include <Geom_Plane.hxx>
#include <Geom_SphericalSurface.hxx> 
#include <Geom_ToroidalSurface.hxx>
#include <Geom_OffsetSurface.hxx>
#include <Geom_SweptSurface.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx> 
#include <Geom_SurfaceOfRevolution.hxx>
#include <Geom_Vector.hxx>
#include <Geom_Direction.hxx> 
#include <Geom_VectorWithMagnitude.hxx> 
#include <Geom_HSequenceOfBSplineSurface.hxx> 
#include <Geom_OsculatingSurface.hxx>
#include <Geom_SequenceOfBSplineSurface.hxx>
#include <Geom_Transformation.hxx>
#include <Geom_UndefinedDerivative.hxx> 
#include <Geom_UndefinedValue.hxx>
#include <GeomAdaptor.hxx>
#include <GeomConvert.hxx>
#include <GeomConvert_ApproxCurve.hxx> 
#include <GeomConvert_ApproxSurface.hxx> 
#include <GeomConvert_BSplineCurveKnotSplitting.hxx> 
#include <GeomConvert_BSplineCurveToBezierCurve.hxx> 
#include <GeomConvert_BSplineSurfaceKnotSplitting.hxx>
#include <GeomConvert_BSplineSurfaceToBezierSurface.hxx> 
#include <GeomConvert_CompBezierSurfacesToBSplineSurface.hxx> 
#include <GeomConvert_CompCurveToBSplineCurve.hxx>
#include <GeomLib.hxx>
#include <GeomLib_Array1OfMat.hxx> 
#include <GeomLib_Check2dBSplineCurve.hxx> 
#include <GeomLib_CheckBSplineCurve.hxx> 
#include <GeomLib_DenominatorMultiplier.hxx> 
#include <GeomLib_Interpolate.hxx>
#include <GeomLib_IsPlanarSurface.hxx> 
#include <GeomLib_LogSample.hxx>
#include <GeomLib_MakeCurvefromApprox.hxx> 
#include <GeomLib_PolyFunc.hxx>
#include <GeomLib_Tool.hxx>
#include <GeomLProp.hxx>
#include <GeomLProp_CLProps.hxx> 
#include <GeomLProp_CurveTool.hxx> 
#include <GeomLProp_SLProps.hxx>
#include <GeomLProp_SurfaceTool.hxx> 
#include <GeomProjLib.hxx>
#include <GeomTools.hxx>
#include <GeomTools_Curve2dSet.hxx> 
#include <GeomTools_CurveSet.hxx>
#include <GeomTools_SurfaceSet.hxx> 
#include <GeomTools_UndefinedTypeHandler.hxx> 
#include <Geom2dLProp_CurAndInf2d.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_Line.hxx>



#include <TColGeom2d_Array1OfBezierCurve.hxx> 
#include <TColGeom2d_Array1OfBSplineCurve.hxx>
#include <TColGeom2d_Array1OfCurve.hxx>
#include <TColGeom2d_HArray1OfBezierCurve.hxx> 
#include <TColGeom2d_HArray1OfBSplineCurve.hxx> 
#include <TColGeom2d_HArray1OfCurve.hxx>
#include <TColGeom2d_SequenceOfCurve.hxx>
#include <TColGeom2d_SequenceOfGeometry.hxx> 
#include <TColGeom_Array1OfBezierCurve.hxx>
#include <TColGeom_Array1OfBSplineCurve.hxx>
#include <TColGeom_Array1OfCurve.hxx> 
#include <TColGeom_Array2OfSurface.hxx>
#include <TColGeom_HArray1OfBezierCurve.hxx> 
#include <TColGeom_HArray1OfBSplineCurve.hxx>
#include <TColGeom_HArray1OfCurve.hxx>
#include <TColGeom_HArray1OfSurface.hxx>
#include <TColGeom_HArray2OfSurface.hxx>
#include <TColGeom_HSequenceOfBoundedCurve.hxx> 
#include <TColGeom_HSequenceOfCurve.hxx>
#include <TColGeom_SequenceOfBoundedCurve.hxx>
#include <TColGeom_SequenceOfCurve.hxx>


//Topods
#include <TopoDS.hxx> 
#include <TopoDS_Builder.hxx>  
#include <TopoDS_FrozenShape.hxx> 
#include <TopoDS_HShape.hxx> 
#include <TopoDS_Iterator.hxx>
#include <TopoDS_ListIteratorOfListOfShape.hxx> 
#include <TopoDS_ListOfShape.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx> 
#include <TopoDS_CompSolid.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx> 
#include <TopoDS_Wire.hxx>
#include <TopoDS_TShape.hxx> 
#include <TopoDS_TCompound.hxx> 
#include <TopoDS_TCompSolid.hxx>
#include <TopoDS_TFace.hxx>
#include <TopoDS_TShell.hxx>
#include <TopoDS_TSolid.hxx>
#include <TopoDS_TVertex.hxx> 
#include <TopoDS_TWire.hxx>
#include <TopoDS_UnCompatibleShapes.hxx>

//TopExp
#include <TopExp.hxx> 
#include <TopExp_Explorer.hxx> 


//Brep
#include <BRepAdaptor_Curve2d.hxx> 
#include <BRepAdaptor_HCurve2d.hxx> 
#include <BRepAdaptor_CompCurve.hxx> 
#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_HCompCurve.hxx> 
#include <BRepAdaptor_HSurface.hxx> 
#include <BRepAdaptor_Surface.hxx> 
#include <BRep_CurveRepresentation.hxx> 
#include <BRep_CurveOn2Surfaces.hxx>
#include <BRep_GCurve.hxx>
#include <BRep_Curve3D.hxx>
#include <BRep_CurveOnSurface.hxx>
#include <BRep_CurveOnClosedSurface.hxx> 
#include <BRep_Polygon3D.hxx>
#include <BRep_PolygonOnSurface.hxx> 
#include <BRep_PolygonOnClosedSurface.hxx> 
#include <BRep_PolygonOnTriangulation.hxx> 
#include <BRep_PolygonOnClosedTriangulation.hxx> 
#include <BRep_ListIteratorOfListOfCurveRepresentation.hxx> 
#include <BRep_ListIteratorOfListOfPointRepresentation.hxx>
#include <BRep_ListOfCurveRepresentation.hxx>
#include <BRep_ListOfPointRepresentation.hxx>
#include <BRep_PointRepresentation.hxx>
#include <BRep_PointOnCurve.hxx>
#include <BRep_PointsOnSurface.hxx> 
#include <BRep_PointOnCurveOnSurface.hxx> 
#include <BRep_PointOnSurface.hxx>
#include <BRep_Tool.hxx>
#include <BRepAdaptor_Array1OfCurve.hxx> 
#include <BRepAdaptor_HArray1OfCurve.hxx>
#include <BRepLProp.hxx>
#include <BRepLProp_CLProps.hxx>
#include <BRepLProp_CurveTool.hxx>
#include <BRepLProp_SLProps.hxx>
#include <BRepLProp_SurfaceTool.hxx>
#include <BRepTools.hxx>
#include <BRepTools_DataMapIteratorOfMapOfVertexPnt2d.hxx>
#include <BRepTools_MapOfVertexPnt2d.hxx>
#include <BRepTools_Modification.hxx>
#include <BRepTools_GTrsfModification.hxx>
#include <BRepTools_NurbsConvertModification.hxx>
#include <BRepTools_TrsfModification.hxx>
#include <BRepTools_Modifier.hxx>
#include <BRepTools_Quilt.hxx>
#include <BRepTools_ReShape.hxx>
#include <BRepTools_Substitution.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRep_Builder.hxx>
#include <BRep_TEdge.hxx>
#include <BRep_TFace.hxx>
#include <BRep_TVertex.hxx> 
#include <BRepTools_ShapeSet.hxx>


// BRepMesh
#include <BRepMesh_DiscretFactory.hxx>
#include <BRepMesh_DiscretRoot.hxx>
#include "BRepBuilderAPI_NurbsConvert.hxx"
#include "BRepMesh_IncrementalMesh.hxx"

// BRepBuilderAPI
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeShell.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>

//BrepPrim
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeHalfSpace.hxx>
#include <BRepPrimAPI_MakeOneAxis.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeRevolution.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeSweep.hxx> 
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepPrimAPI_MakeWedge.hxx> 

//BrepSweep
#include <BRepSweep_Builder.hxx>
#include <BRepSweep_Iterator.hxx>
#include <BRepSweep_NumLinearRegularSweep.hxx>
#include <BRepSweep_Trsf.hxx>
#include <BRepSweep_Rotation.hxx> 
#include <BRepSweep_Translation.hxx>
#include <BRepSweep_Prism.hxx>
#include <BRepSweep_Revol.hxx>
#include <BRepSweep_Tool.hxx>

//BrepAlgoApi
#include <BRepAlgoAPI_BooleanOperation.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx> 
#include <BRepAlgoAPI_Section.hxx> 
#include <BRepAlgoAPI_Defeaturing.hxx>

//BrepFill
#include <BRepFilletAPI_LocalOperation.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeFillet2d.hxx>
#include <BRepFill.hxx>

#include <BRepProj_Projection.hxx> 

//Healing
#include <ShapeBuild.hxx> 
#include <ShapeBuild_Edge.hxx>
#include <ShapeBuild_ReShape.hxx>
#include <ShapeBuild_Vertex.hxx>
#include <ShapeFix.hxx>
#include <ShapeFix_DataMapIteratorOfDataMapOfShapeBox2d.hxx>
#include <ShapeFix_DataMapOfShapeBox2d.hxx>
#include <ShapeFix_Edge.hxx>
#include <ShapeFix_EdgeConnect.hxx>
#include <ShapeFix_EdgeProjAux.hxx>
#include <ShapeFix_FaceConnect.hxx>
#include <ShapeFix_FreeBounds.hxx>
#include <ShapeFix_IntersectionTool.hxx>
#include <ShapeFix_Root.hxx>
#include <ShapeFix_ComposeShell.hxx>
#include <ShapeFix_Face.hxx>
#include <ShapeFix_FixSmallFace.hxx>
#include <ShapeFix_Shape.hxx>
#include <ShapeFix_Shell.hxx>
#include <ShapeFix_Solid.hxx>
#include <ShapeFix_SplitCommonVertex.hxx>
#include <ShapeFix_Wire.hxx>
#include <ShapeFix_Wireframe.hxx>
#include <ShapeFix_SequenceOfWireSegment.hxx>
#include <ShapeFix_ShapeTolerance.hxx>
#include <ShapeFix_SplitTool.hxx>
#include <ShapeFix_WireSegment.hxx>
#include <ShapeFix_WireVertex.hxx>
#include <ShapeAnalysis.hxx>
#include <ShapeAnalysis_CheckSmallFace.hxx>
#include <ShapeAnalysis_Curve.hxx>
#include <ShapeAnalysis_DataMapIteratorOfDataMapOfShapeListOfReal.hxx>
#include <ShapeAnalysis_DataMapOfShapeListOfReal.hxx>
#include <ShapeAnalysis_Edge.hxx>
#include <ShapeAnalysis_FreeBoundData.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <ShapeAnalysis_FreeBoundsProperties.hxx>
#include <ShapeAnalysis_Geom.hxx>
#include <ShapeAnalysis_HSequenceOfFreeBounds.hxx>
#include <ShapeAnalysis_SequenceOfFreeBounds.hxx>
#include <ShapeAnalysis_ShapeContents.hxx>
#include <ShapeAnalysis_ShapeTolerance.hxx> 
#include <ShapeAnalysis_Shell.hxx>
#include <ShapeAnalysis_Surface.hxx>
#include <ShapeAnalysis_TransferParameters.hxx>
#include <ShapeAnalysis_TransferParametersProj.hxx>
#include <ShapeAnalysis_Wire.hxx>
#include <ShapeAnalysis_WireOrder.hxx>
#include <ShapeAnalysis_WireVertex.hxx>
#include <ShapeAlgo.hxx>
#include <ShapeAlgo_AlgoContainer.hxx>
#include <ShapeAlgo_ToolContainer.hxx>
#include <ShapeProcess.hxx>
#include <ShapeProcess_Context.hxx>
#include <ShapeProcess_ShapeContext.hxx>
#include <ShapeProcess_Operator.hxx>
#include <ShapeProcess_UOperator.hxx>
#include <ShapeProcess_OperLibrary.hxx>
#include <ShapeProcessAPI_ApplySequence.hxx>
#include <ShapeProcessAPI_ApplySequence.hxx>

#include <ShapeConstruct_MakeTriangulation.hxx> 
#include <ShapeConstruct.hxx>
#include <ShapeConstruct_Curve.hxx>
#include <ShapeConstruct_ProjectCurveOnSurface.hxx>

// Visualization
#include <V3d.hxx>
#include <V3d_CircularGrid.hxx>
#include <V3d_RectangularGrid.hxx>
#include <V3d_Light.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_PositionLight.hxx>
#include <V3d_DirectionalLight.hxx>
#include <V3d_PositionalLight.hxx>
#include <V3d_SpotLight.hxx>
#include <V3d_Plane.hxx>
#include <V3d_UnMapped.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

// WNT
#include <WNT_Window.hxx>

// Graphic 3d
#include <Graphic3d_AspectFillArea3d.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <Graphic3d_AspectMarker3d.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <Graphic3d_ArrayOfPrimitives.hxx>
#include <Graphic3d_ArrayOfPoints.hxx>
#include <Graphic3d_ArrayOfPolygons.hxx>
#include <Graphic3d_ArrayOfPolylines.hxx>
#include <Graphic3d_ArrayOfQuadrangles.hxx>
#include <Graphic3d_ArrayOfQuadrangleStrips.hxx>
#include <Graphic3d_ArrayOfSegments.hxx>
#include <Graphic3d_ArrayOfTriangleFans.hxx>
#include <Graphic3d_ArrayOfTriangles.hxx>
#include <Graphic3d_ArrayOfTriangleStrips.hxx>
#include <Graphic3d_AspectText3d.hxx>
#include <Graphic3d_DataStructureManager.hxx>
#include <Graphic3d_Group.hxx>
#include <Graphic3d_GroupDefinitionError.hxx>
#include <Graphic3d_MapIteratorOfMapOfStructure.hxx>
#include <Graphic3d_MapOfStructure.hxx>
#include <Graphic3d_MaterialAspect.hxx>
#include <Graphic3d_MaterialDefinitionError.hxx>
#include <Graphic3d_PriorityDefinitionError.hxx>
#include <Graphic3d_SequenceOfGroup.hxx>
#include <Graphic3d_SequenceOfStructure.hxx>
#include <Graphic3d_Structure.hxx>
#include <Graphic3d_StructureDefinitionError.hxx>
#include <Graphic3d_StructureManager.hxx>
#include <Graphic3d_TextureRoot.hxx>
#include <Graphic3d_TextureEnv.hxx>
#include <Graphic3d_TextureMap.hxx>
#include <Graphic3d_Texture1D.hxx>
#include <Graphic3d_Texture1Dmanual.hxx>
#include <Graphic3d_Texture1Dsegment.hxx>
#include <Graphic3d_Texture2D.hxx>
#include <Graphic3d_Texture2Dmanual.hxx>
#include <Graphic3d_Texture2Dplane.hxx>
#include <Graphic3d_TransformError.hxx>
#include <Graphic3d_Vertex.hxx>

// OpenGl
#include <OpenGl_GraphicDriver.hxx>

#include <Prs3d_Presentation.hxx>
#include <Prs3d.hxx>
#include <Prs3d_BasicAspect.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_IsoAspect.hxx>
#include <Prs3d_PointAspect.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <Prs3d_TextAspect.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <Prs3d_DatumAspect.hxx>
#include <Prs3d_PlaneAspect.hxx>
#include <Prs3d_Drawer.hxx>
#include <Prs3d_InvalidAngle.hxx>
#include <Prs3d_Root.hxx>
#include <Prs3d_Arrow.hxx>
#include <Prs3d_Text.hxx>
#include <Prs3d_ShapeTool.hxx>

#include <AIS.hxx>
#include <AIS_GlobalStatus.hxx>
#include <AIS_GraphicTool.hxx>
#include <AIS_IndexedDataMapOfOwnerPrs.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_ListIteratorOfListOfInteractive.hxx>
#include <AIS_ListOfInteractive.hxx>
#include <AIS_MapIteratorOfMapOfInteractive.hxx>
#include <AIS_MapOfInteractive.hxx>
#include <AIS_Selection.hxx>
#include <AIS_SequenceOfInteractive.hxx>
#include <AIS_InteractiveObject.hxx>
#include <AIS_Axis.hxx>
#include <AIS_Circle.hxx>
#include <AIS_ConnectedInteractive.hxx>
#include <AIS_Line.hxx>
#include <AIS_MultipleConnectedInteractive.hxx>
#include <AIS_Plane.hxx>
#include <AIS_PlaneTrihedron.hxx>
#include <AIS_Relation.hxx>
#include <AIS_AngleDimension.hxx>
#include <AIS_Chamf2dDimension.hxx>
#include <AIS_ConcentricRelation.hxx>
#include <AIS_DiameterDimension.hxx>
#include <AIS_EllipseRadiusDimension.hxx>
#include <AIS_MaxRadiusDimension.hxx>
#include <AIS_MinRadiusDimension.hxx>
#include <AIS_EqualDistanceRelation.hxx> 
#include <AIS_EqualRadiusRelation.hxx>
#include <AIS_FixRelation.hxx>
#include <AIS_IdenticRelation.hxx> 
#include <AIS_LengthDimension.hxx>
#include <AIS_MidPointRelation.hxx>
#include <AIS_OffsetDimension.hxx>
#include <AIS_ParallelRelation.hxx>
#include <AIS_PerpendicularRelation.hxx>
#include <AIS_TangentRelation.hxx>
#include <AIS_Shape.hxx>
#include <AIS_TexturedShape.hxx>
#include <AIS_Trihedron.hxx>
#include <AIS_DimensionOwner.hxx>
#include <AIS_AttributeFilter.hxx>
#include <AIS_BadEdgeFilter.hxx>
#include <AIS_ExclusionFilter.hxx>
#include <AIS_TypeFilter.hxx>
#include <AIS_SignatureFilter.hxx>
#include <AIS_ColorScale.hxx>
#include "AIS_RubberBand.hxx"
#include <AIS_ColoredShape.hxx>
#include <AIS_Point.hxx>
#include <AIS_TextLabel.hxx>
#include <AIS_ViewController.hxx>
#include "AIS_ViewCube.hxx"
#include <AIS_Triangulation.hxx>

#include <TopTools_Array1OfShape.hxx>
#include <GProp_GProps.hxx>
#include <BRepGProp.hxx>


#include <StdPrs_WFShape.hxx>
#include <StdPrs_ShadedShape.hxx>
#include <StdPrs_HLRShape.hxx>
#include <StdPrs_HLRPolyShape.hxx>

#include <StdSelect_BRepSelectionTool.hxx>

#include "Poly_Triangulation.hxx"
#include <Poly_Connect.hxx>

#include "STEPControl_Controller.hxx"
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>
#include <XSControl_WorkSession.hxx>
#include <XSControl_TransferReader.hxx>
#include <STEPConstruct_Styles.hxx>
#include <TColStd_HSequenceOfTransient.hxx>
#include <STEPConstruct.hxx>
#include <StepVisual_StyledItem.hxx>
#include "Interface_Static.hxx"

#include "IGESControl_Reader.hxx"
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>

#include <TopTools_DataMapOfShapeInteger.hxx>

#include <ProjLib.hxx>

#include <RWStl.hxx>
#include <BRepBuilderAPI_Sewing.hxx>

#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeSegment.hxx>

#include <BRepFeat_MakePrism.hxx>
#include <BRepFeat_MakeRevol.hxx>

#include <GeomAPI_PointsToBSpline.hxx>

#include <STEPCAFControl_Reader.hxx>
#include <XCAFPrs_Style.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <TDF_Tool.hxx>
#include <XCAFPrs_AISObject.hxx>
#include <XCAFDoc_ColorTool.hxx>

#include <GCPnts_QuasiUniformDeflection.hxx>

#include <GCE2d_MakeSegment.hxx>
#include <GCE2d_MakeParabola.hxx>
#include <GCE2d_MakeEllipse.hxx>
#include <GCE2d_MakeArcOfCircle.hxx>
#include <GCE2d_MakeArcOfEllipse.hxx>
#include <GCE2d_MakeLine.hxx>
#include <Geom2d_TrimmedCurve.hxx>

#include <Aspect_WidthOfLine.hxx>

#include <GC_MakePlane.hxx>

#include <GeomFill_SectionGenerator.hxx>
#include <GeomFill_Line.hxx>
#include <GeomFill_AppSurf.hxx>
#include <GeomFill_SweepSectionGenerator.hxx>
#include <GeomFill_AppSweep.hxx>
#include <GeomFill_NSections.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <GeomFill_Pipe.hxx>

#include <GeomConvert.hxx>

#include <BRepOffsetAPI_MakeOffset.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>

#include <StdSelect_FaceFilter.hxx>
#include <StdSelect_EdgeFilter.hxx>

#include <StdPrs_ToolTriangulatedShape.hxx>
#include <Select3D_SensitiveBox.hxx>
#include <StdSelect.hxx>

#include <gce_MakePln.hxx>
#include <gce_MakeLin.hxx>

// OCAF document classes

#include <TDocStd_Application.hxx>
#include <TDocStd_Document.hxx>
#include <TDF_Label.hxx>
#include <TPrsStd_AISPresentation.hxx>
#include <TPrsStd_AISViewer.hxx>
#include <TNaming_NamedShape.hxx>
#include "TFunction_DriverTable.hxx"
#include <BinDrivers.hxx>
#include <XmlDrivers.hxx>
#include <TDF_Attribute.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Label.hxx>
#include <TDF_RelocationTable.hxx>
#include <TDataXtd_Presentation.hxx>
#include <TPrsStd_AISPresentation.hxx>
#include <TDataStd_Integer.hxx>
#include "TDataStd_Name.hxx"
#include "TFunction_Function.hxx"
#include "TFunction_DriverTable.hxx"
#include "TDF_Reference.hxx"
#include "TFunction_Logbook.hxx"
#include "TNaming_Builder.hxx"
#include <TDataStd_Real.hxx>
#include <TNaming_Tool.hxx>

#include <TPrsStd_Driver.hxx>
#include <TPrsStd_DriverTable.hxx>

#include <TDataXtd_Point.hxx>
#include <TDataXtd_Geometry.hxx>
#include <TFunction_Scope.hxx>
#include <TFunction_Iterator.hxx>
#include <TFunction_IFunction.hxx>

#include <StlAPI_Writer.hxx>
#include <STEPCAFControl_Writer.hxx>

#include <GeomAdaptor_HCurve.hxx>
#include <GeomFill_SimpleBound.hxx>
#include <GeomFill_ConstrainedFilling.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>

#include <PrsDim_RadiusDimension.hxx>

#include <BRepBndLib.hxx>
#include <Bnd_OBB.hxx>

// Import Libraries

#pragma comment(lib, "TKVCAF.lib")
#pragma comment(lib, "TKLCAF.lib")
#pragma comment(lib, "TKXCAF.lib")
#pragma comment(lib, "TKBin.lib")
#pragma comment(lib, "TKXml.lib")
#pragma comment(lib, "TKCAF.lib")
#pragma comment(lib, "TKCDF.lib")

#pragma comment(lib, "TKBrep.lib")
#pragma comment(lib, "TKernel.lib")
#pragma comment(lib, "TKG3D.lib")
#pragma comment(lib, "TKG2D.lib")
#pragma comment(lib, "TKGeomBase.lib")
#pragma comment(lib, "TKHLR.lib")
#pragma comment(lib, "TKMath.lib")
#pragma comment(lib, "TKSHHEALING.lib")
#pragma comment(lib, "TKTopAlgo.lib")
#pragma comment(lib, "TKBO.lib")
#pragma comment(lib, "TKBool.lib")
#pragma comment(lib, "TKGeomAlgo.lib")
#pragma comment(lib, "TKOffset.lib")
#pragma comment(lib, "TKFeat.lib")
#pragma comment(lib, "TKFillet.lib")
#pragma comment(lib, "TKPrim.lib")
#pragma comment(lib, "TKMesh.lib")
#pragma comment(lib, "TKOpenGl.lib")
#pragma comment(lib, "TKService.lib")
#pragma comment(lib, "TKV3d.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "odbccp32.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "TKSTEP.lib")
#pragma comment(lib, "TKSTEP209.lib")
#pragma comment(lib, "TKSTEPAttr.lib")
#pragma comment(lib, "TKSTEPBase.lib")
#pragma comment(lib, "TKIGES.lib")
#pragma comment(lib, "TKXSBase.lib")
#pragma comment(lib, "TKSTL.lib")
#pragma comment(lib, "TKXDESTEP.lib")

// typedefs

typedef NCollection_List< Handle(Geom_Curve) > 	TColGeom_ListOfCurve;
