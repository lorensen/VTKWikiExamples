PROJECT (${WIKI}PolyData)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkWidgets vtkHybrid vtkCharts)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)

set(VERSION_MIN "5.9.20111206")
Requires_Version(BooleanOperationPolyDataFilter ${VERSION_MIN} ALL_FILES)
Requires_Version(DistancePolyDataFilter ${VERSION_MIN} ALL_FILES)
Requires_Version(ImplicitPolyDataDistance ${VERSION_MIN} ALL_FILES)
Requires_Version(IntersectionPolyDataFilter ${VERSION_MIN} ALL_FILES)
Requires_Version(Curvatures "6.0.0" ALL_FILES)

foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(KIT PolyData)
SET(NEEDS_ARGS
  CellLocatorVisualization
  ColoredPoints
  DetermineArrayDataTypes
  DijkstraGraphGeodesicPath	
  ExternalContour
  GetMiscCellData
  GetMiscPointData
  GradientFilter
  GreedyTerrainDecimation
  HighlightBadCells
  Hull
  ImplicitModeller
  MiscPointData
  PointLocatorVisualization
  PolyDataIsoLines
  PolyDataPointSample
  RemoveVertices
  ThinPlateSplineTransform
  TriangleColoredPoints
  TriangleSolidColor
)
if(NOT ${VTK_VERSION} VERSION_LESS "6")
  list(APPEND NEEDS_ARGS Curvatures)
endif()

SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)
SET(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

ADD_TEST(${KIT}-CellLocatorVisualization ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestCellLocatorVisualization -E 50)

ADD_TEST(${KIT}-ColoredPoints ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestColoredPoints ${TEMP}/coloredpoints.vtp)

if(NOT ${VTK_VERSION} VERSION_LESS "6")
  ADD_TEST(${KIT}-Curvatures ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
    TestCurvatures ${DATA}/cowHead.vtp -20 20)
endif()

ADD_TEST(${KIT}-DijkstraGraphGeodesicPath ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestDijkstraGraphGeodesicPath	-E 20)

ADD_TEST(${KIT}-ExternalContour ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestExternalContour ${DATA}/Bunny.vtp -E 80 )

ADD_TEST(${KIT}-DetermineArrayDataTypes ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestDetermineArrayDataTypes ${DATA}/foilledContours.vtp)

ADD_TEST(${KIT}-GetMiscCellData ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestGetMiscCellData ${DATA}/SuperQuadric.vtp Nromals)

ADD_TEST(${KIT}-GetMiscPointData ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestGetMiscPointData ${DATA}/cowHead.vtp Gauss_Curvature)

ADD_TEST(${KIT}-GradientFilter ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestGradientFilter ${DATA}/uGridEx.vtk)

ADD_TEST(${KIT}-GreedyTerrainDecimation ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestGreedyTerrainDecimation -E 55)

ADD_TEST(${KIT}-Hull ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestHull ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-HighlightBadCells ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestHighlightBadCells -E 20)

ADD_TEST(${KIT}-ImplicitModeller ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImplicitModeller ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-MiscPointData ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestMiscPointData ${DATA}/cowHead.vtp)

ADD_TEST(${KIT}-PointLocatorVisualization ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestPointLocatorVisualization -E 50)

ADD_TEST(${KIT}-PolyDataIsoLines ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestPolyDataIsoLines ${DATA}/cowHead.vtp)

ADD_TEST(${KIT}-RemoveVertices ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestRemoveVertices ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-ThinPlateSplineTransform ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestThinPlateSplineTransform ${DATA}/masonry.bmp)

ADD_TEST(${KIT}-TriangleColoredPoints ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestTriangleColoredPoints -E 15)

ADD_TEST(${KIT}-TriangleSolidColor ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestTriangleSolidColor -E 25)

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
