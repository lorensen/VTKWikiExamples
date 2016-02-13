set(DOCUMENTATION "A collection of examples illustrating how to use VTK")

vtk_module( WikiExamples
  DEPENDS
  vtkFiltersFlowPaths
  vtkFiltersGeneric
  vtkFiltersGeometry
  vtkFiltersParallelStatistics
  vtkFiltersProgrammable
  vtkFiltersSelection
  vtkFiltersTexture
  vtkFiltersVerdict
  vtkIOExodus
  vtkIOExport
  vtkIOImport
  vtkIOInfovis
  vtkIOLSDyna
  vtkIOPLY
  vtkIOParallel
  vtkIOParallelXML
  vtkImagingMath
  vtkImagingMorphological
  vtkImagingStatistics
  vtkImagingStencil
  vtkInteractionImage
  vtkRenderingContext${VTK_RENDERING_BACKEND}
  vtkRenderingImage
  vtkRenderingLOD
  vtkRenderingQt
  vtkRenderingVolume${VTK_RENDERING_BACKEND}
  vtkRendering${VTK_RENDERING_BACKEND}
  vtkTestingGenericBridge
  vtkTestingRendering
  vtkViewsContext2D
  vtkViewsGeovis
  vtkViewsQt

  DESCRIPTION
    "${DOCUMENTATION}"
)
