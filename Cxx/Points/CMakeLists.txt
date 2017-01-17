PROJECT (${WIKI}Points)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkRendering vtkHybrid)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()

#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)
include(${WikiExamples_SOURCE_DIR}/CMake/RequiresModule.cmake)

set(VERSION_MIN "7.0")
Requires_Version(ExtractClusters ${VERSION_MIN} ALL_FILES)
Requires_Version(ExtractSurface ${VERSION_MIN} ALL_FILES)
Requires_Version(ExtractSurfaceDemo ${VERSION_MIN} ALL_FILES)
Requires_Version(FitImplicitSurface ${VERSION_MIN} ALL_FILES)
Requires_Module(ExtractClusters vtkFiltersPoints)
Requires_Module(ExtractSurface vtkFiltersPoints)
Requires_Module(ExtractSurfaceDemo vtkFiltersPoints)
Requires_Module(FitImplicitSurface vtkFiltersPoints)

foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(KIT Points)
SET(NEEDS_ARGS
  ExtractClusters
  ExtractSurface
  ExtractSurfaceDemo
)
SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)

if (vtkFiltersPoints_LOADED)
   ADD_TEST(${KIT}-ExtractClusters ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestExtractClusters ${DATA}/Armadillo.ply)
   ADD_TEST(${KIT}-ExtractSurface ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestExtractSurface ${DATA}/Armadillo.ply)
   ADD_TEST(${KIT}-ExtractSurfaceDemo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests
     TestExtractSurfaceDemo ${DATA}/Armadillo.ply)
endif()

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
