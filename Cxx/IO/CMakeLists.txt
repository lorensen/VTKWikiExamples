PROJECT (${WIKI}IO)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkHybrid vtkGenericFiltering)
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
SET(KIT IO)
SET(NEEDS_ARGS
  ConvertFile
  DEMReader
  DumpXMLFile
  GenericDataObjectReader
  ImageReader2Factory
  IndividualVRML
  JPEGReader
  JPEGWriter
  MetaImageReader
  ParticleReader
  PNGReader
  PNGWriter
  ReadBMP
  ReadDICOM
  ReadDICOMSeries
  ReadImageData
  ReadOBJ
  ReadPDB
  ReadPlainTextTriangles
  ReadPLY
  ReadPLOT3D
  ReadPNM
  ReadPolyData
  ReadRectilinearGrid
  ReadSTL
  ReadStructuredGrid
  ReadTIFF
  ReadTextFile
  ReadUnknownTypeXMLFile
  ReadUnstructuredGrid
  SimplePointsReader
  StructuredPointsReader
  StructuredGridReader
  VRML
  WriteBMP
  WritePLY
  WritePNM
  WriteSTL
  WriteTIFF
  WriteVTI
  WriteVTU
)
 
SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)
SET(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

ADD_TEST(${KIT}-ConvertFile ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestConvertFile ${DATA}/Bunny.vtp ${TEMP}/ConvertFile.ply)

ADD_TEST(${KIT}-DumpXMLFile ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestDumpXMLFile ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-GenericDataObjectReader ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestGenericDataObjectReader ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-IndividualVRML ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestIndividualVRML ${DATA}/teapot.wrl teapot)

ADD_TEST(${KIT}-ImageReader2Factory ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageReader2Factory ${DATA}/Gourds.png)

ADD_TEST(${KIT}-JPEGReader ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestJPEGReader ${DATA}/Pileated.jpg)

ADD_TEST(${KIT}-JPEGWriter ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestJPEGWriter ${TEMP}/JPEGWriter.jpg)

ADD_TEST(${KIT}-MetaImageReader ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestMetaImageReader ${DATA}/Gourds.mha)

ADD_TEST(${KIT}-ParticleReader ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestParticleReader ${DATA}/Particles.raw)

ADD_TEST(${KIT}-PNGReader ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestPNGReader ${DATA}/Gourds.png)

ADD_TEST(${KIT}-PNGWriter ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestPNGWriter ${TEMP}/PNGWriter.png)

ADD_TEST(${KIT}-ReadBMP ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadBMP ${DATA}/masonry.bmp)

ADD_TEST(${KIT}-DEMReader ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestDEMReader ${DATA}/SainteHelens.dem)

ADD_TEST(${KIT}-ReadDICOM ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadDICOM ${DATA}/prostate.img)

ADD_TEST(${KIT}-ReadDICOMSeries ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadDICOMSeries ${DATA}/DICOMDirectory)

ADD_TEST(${KIT}-ReadImageData ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadImageData ${DATA}/vase.vti)

ADD_TEST(${KIT}-ReadOBJ ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadOBJ ${DATA}/trumpet.obj)

ADD_TEST(${KIT}-ReadPDB ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadPDB ${DATA}/lys.pdb)

ADD_TEST(${KIT}-ReadPLOT3D ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadPLOT3D ${DATA}/combxyz.bin ${DATA}/combq.bin)

ADD_TEST(${KIT}-ReadPLY ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadPLY ${DATA}/shark.ply)

ADD_TEST(${KIT}-ReadPolyData ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadPolyData ${DATA}/Torso.vtp)

ADD_TEST(${KIT}-ReadPNM ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadPNM ${DATA}/Gourds.pnm)

ADD_TEST(${KIT}-ReadRectilinearGrid ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadRectilinearGrid ${DATA}/RectilinearGrid.vtr)

ADD_TEST(${KIT}-ReadSTL ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadSTL ${DATA}/42400-IDGH.stl)

ADD_TEST(${KIT}-ReadStructuredGrid ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadStructuredGrid ${DATA}/StructuredGrid.vts)

ADD_TEST(${KIT}-ReadPlainTextTriangles ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadPlainTextTriangles ${DATA}/Triangles.txt)

ADD_TEST(${KIT}-ReadUnknownTypeXMLFile ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadUnknownTypeXMLFile ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-ReadTIFF ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadTIFF ${DATA}/ColorCells.tif)

ADD_TEST(${KIT}-ReadTextFile ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadTextFile ${DATA}/TeapotPoints.txt)

ADD_TEST(${KIT}-ReadUnstructuredGrid ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestReadUnstructuredGrid ${DATA}/tetra.vtu)

ADD_TEST(${KIT}-SimplePointsReader ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestSimplePointsReader ${DATA}/coords.txt)

ADD_TEST(${KIT}-StructuredPointsReader ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestStructuredPointsReader ${DATA}/StructuredPoints.vtk)

ADD_TEST(${KIT}-StructuredGridReader ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestStructuredGridReader ${DATA}/SampleStructGrid.vtk)

ADD_TEST(${KIT}-VRML ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestVRML ${DATA}/bridge.wrl)

ADD_TEST(${KIT}-WriteBMP ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestWriteBMP ${TEMP}/WriteBMP.bmp)

ADD_TEST(${KIT}-WritePNM ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestWritePNM ${TEMP}/WritePNM.pnm)

ADD_TEST(${KIT}-WritePLY ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestWritePLY ${TEMP}/WritePLY.ply)

ADD_TEST(${KIT}-WriteSTL ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestWriteSTL ${TEMP}/WriteSTL.stl)

ADD_TEST(${KIT}-WriteTIFF ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestWriteTIFF ${TEMP}/WriteTIFF.tif)

ADD_TEST(${KIT}-WriteVTI ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestWriteVTI ${TEMP}/WriteVTI.vti)

ADD_TEST(${KIT}-WriteVTU ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestWriteVTU ${TEMP}/WriteVTU.vtu)

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

endif()
