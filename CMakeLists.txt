cmake_minimum_required(VERSION 2.6)

# Eliminate a warning when building in Windows that relates
# to static linking of Qt executables to qtmain.lib.
# This policy was introduced in CMake version 2.8.11.
# CMake version 2.8.11.2 warns when the policy is not set
# and uses OLD behavior.
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

PROJECT(WikiExamples)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
message(STATUS "VTKWikiExamples: VTK VERSION: ${VTK_VERSION}")

set(CMAKE_MODULE_PATH ${WikiExamples_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

if (BUILD_TESTING)
  ENABLE_TESTING()
  INCLUDE(CTest)
  CONFIGURE_FILE(
    ${WikiExamples_SOURCE_DIR}/CMake/SampleBuildTest.cmake.in
    ${WikiExamples_BINARY_DIR}/SampleBuildTest.cmake @ONLY)
endif ()

include(PlatformSpecificChecks)

#
# Mac specific
IF(APPLE)
  SET(EXECUTABLE_FLAG MACOSX_BUNDLE)
ENDIF(APPLE)

#-----------------------------------------------------------------------------
# Output directories.
IF(NOT LIBRARY_OUTPUT_PATH)
  SET (LIBRARY_OUTPUT_PATH ${WikiExamples_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
ENDIF(NOT LIBRARY_OUTPUT_PATH)
IF(NOT EXECUTABLE_OUTPUT_PATH)
  SET (EXECUTABLE_OUTPUT_PATH ${WikiExamples_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")
ENDIF(NOT EXECUTABLE_OUTPUT_PATH)
MARK_AS_ADVANCED(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

ADD_SUBDIRECTORY(Cxx/Animation)
IF(VTK_USE_MYSQL)
  ADD_SUBDIRECTORY(Cxx/Databases)
ENDIF(VTK_USE_MYSQL)
ADD_SUBDIRECTORY(Cxx/DataStructures)
#ADD_SUBDIRECTORY(Cxx/Developers)
ADD_SUBDIRECTORY(Cxx/Filtering)
ADD_SUBDIRECTORY(Cxx/GeometricObjects)
IF(VTK_USE_INFOVIS)
  IF(VTK_USE_BOOST)
    ADD_SUBDIRECTORY(Cxx/Graphs)
  ENDIF(VTK_USE_BOOST)
ENDIF(VTK_USE_INFOVIS)
ADD_SUBDIRECTORY(Cxx/ImageData)
  ADD_SUBDIRECTORY(Cxx/Geovis)
ADD_SUBDIRECTORY(Cxx/Images)
ADD_SUBDIRECTORY(Cxx/ImplicitFunctions)
ADD_SUBDIRECTORY(Cxx/InfoVis)
ADD_SUBDIRECTORY(Cxx/Interaction)
ADD_SUBDIRECTORY(Cxx/IO)
ADD_SUBDIRECTORY(Cxx/Lighting)
ADD_SUBDIRECTORY(Cxx/Math)
ADD_SUBDIRECTORY(Cxx/Medical)
ADD_SUBDIRECTORY(Cxx/Meshes)
ADD_SUBDIRECTORY(Cxx/Modelling)
IF(VTK_USE_PARALLEL)
  ADD_SUBDIRECTORY(Cxx/Parallel)
ENDIF(VTK_USE_PARALLEL)
ADD_SUBDIRECTORY(Cxx/Picking)
ADD_SUBDIRECTORY(Cxx/Plotting)
ADD_SUBDIRECTORY(Cxx/PolyData)
ADD_SUBDIRECTORY(Cxx/RectilinearGrid)
ADD_SUBDIRECTORY(Cxx/RenderMan)
ADD_SUBDIRECTORY(Cxx/SimpleOperations)
ADD_SUBDIRECTORY(Cxx/StructuredGrid)
IF(VTK_USE_TEXT_ANALYSIS)
  ADD_SUBDIRECTORY(Cxx/TextAnalysis)
ENDIF(VTK_USE_TEXT_ANALYSIS)
ADD_SUBDIRECTORY(Cxx/Texture)
ADD_SUBDIRECTORY(Cxx/Utilities)
ADD_SUBDIRECTORY(Cxx/Video)
IF(VTK_USE_VIEWS)
  ADD_SUBDIRECTORY(Cxx/Views)
ENDIF(VTK_USE_VIEWS)
ADD_SUBDIRECTORY(Cxx/Visualization)
ADD_SUBDIRECTORY(Cxx/VisualizationAlgorithms)
ADD_SUBDIRECTORY(Cxx/VolumeRendering)
ADD_SUBDIRECTORY(Cxx/Widgets)

# ADD_SUBDIRECTORY(Python/GeometricObjects)

if(vtkGUISupportQt_LOADED)
  message(STATUS "VTKWikiExamples: Building Qt examples")
  if(${VTK_VERSION} VERSION_GREATER "6" AND VTK_QT_VERSION VERSION_GREATER "4")
    # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC ON)
    # We have ui files, this will bring in the macro: qt5_wrap_ui
    find_package(Qt5Widgets REQUIRED QUIET)
  else()
    FIND_PACKAGE(Qt4 REQUIRED)
    INCLUDE(${QT_USE_FILE})
  endif()
  ADD_SUBDIRECTORY(Cxx/Qt)
else()
  message(STATUS "VTKWikiExamples: Not building Qt examples")
endif()

OPTION(RUN_ADMIN_TESTS "Run the admin tests" OFF)
IF( RUN_ADMIN_TESTS )
  ADD_TEST(CheckPagesForImages ${WikiExamples_SOURCE_DIR}/Admin/CheckPagesForImages)
  SET_TESTS_PROPERTIES(CheckPagesForImages PROPERTIES TIMEOUT 2000)
ENDIF( RUN_ADMIN_TESTS )
