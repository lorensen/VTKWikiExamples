PROJECT (InfoVis)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_INFOVIS)
  MESSAGE(FATAL_ERROR "VTKWikiExamples: Example ${PROJECT_NAME} requires VTK_USE_INFOVIS.")
ENDIF(NOT VTK_USE_INFOVIS)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkWidgets vtkRendering vtkHybrid vtkViews vtkInfovis)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)

if(NOT VTK_USE_PARALLEL)
  set(SKIP PKMeansClustering)
  message(STATUS "VTKWikiExamples: ${SKIP} requires VTK_PARALLEL and will not be built")
  string(REGEX REPLACE "[^;]*${SKIP}.cxx"
         "" ALL_FILES "${ALL_FILES}")
endif()

foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

# Testing
SET(KIT InfoVis)

SET(NEEDS_ARGS
DelimitedTextReader
DelimitedTextWriter
TreeMapView
XGMLReader
)
INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)
SET(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

ADD_TEST(${KIT}-DelimitedTextReader ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestDelimitedTextReader ${DATA}/DelimitedData.txt)

ADD_TEST(${KIT}-DelimitedTextWriter ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestDelimitedTextWriter ${TEMP}/foo.txt)

ADD_TEST(${KIT}-TreeMapView ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestTreeMapView ${DATA}/Infovis-XML-vtkclasses.xml ${DATA}/Infovis-XML-vtklibrary.xml)

ADD_TEST(${KIT}-XGMLReader ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestXGMLReader ${DATA}/fsm.gml)
