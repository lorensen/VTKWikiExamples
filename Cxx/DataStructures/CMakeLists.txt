PROJECT (${WIKI}DataStructures)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 6.0)
  SET(KIT_LIBS vtkHybrid vtkRendering vtkWidgets vtkCharts)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()

#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)
foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(KIT DataStructures)
SET(NEEDS_ARGS
  DataStructureComparison
  VisualizeKDTree
  VisualizeOBBTree
  KDTreeTimingDemo
  ModifiedBSPTreeTimingDemo
  OBBTreeTimingDemo
  OctreeTimingDemo
  OctreeVisualize
)
INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)

ADD_TEST(${KIT}-DataStructureComparison ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestDataStructureComparison ${DATA}/Bunny.vtp -E 20)

ADD_TEST(${KIT}-VisualizeKDTree ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestVisualizeKDTree -E 40)
ADD_TEST(${KIT}-VisualizeOBBTree ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestVisualizeOBBTree -E 40)

# These tests will generate different output each time they run.
# To avoid regression failures, set the error tolerance to a large number. 
ADD_TEST(${KIT}-KDTreeTimingDemo ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestKDTreeTimingDemo -E 999999)
ADD_TEST(${KIT}-ModifiedBSPTreeTimingDemo ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestModifiedBSPTreeTimingDemo -E 999999)
ADD_TEST(${KIT}-OBBTreeTimingDemo ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestOBBTreeTimingDemo -E 999999)
ADD_TEST(${KIT}-OctreeTimingDemo ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestOctreeTimingDemo -E 999999)

ADD_TEST(${KIT}-OctreeVisualize ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestOctreeVisualize -E 40)

ADD_SUBDIRECTORY(ModifiedBSPTree)
endif()
