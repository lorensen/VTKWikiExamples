PROJECT (Images)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "VTKWikiExamples: Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

SET(KIT Images)
if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkHybrid vtkRendering vtkWidgets)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()

#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)

if(NOT VTK_USE_SYSTEM_FREETYPE)
  message(STATUS "VTKWikiExamples: ImageText requires VTK_USE_SYSTEM_FREETYPE and will not be built")
  string(REGEX REPLACE "[^;]*ImageText.cxx"
         "" ALL_FILES "${ALL_FILES}")
endif()

foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

# Testing
SET(NEEDS_ARGS
#  HistogramBarChart
#  HistogramXYPlot
  CannyEdgeDetector
  Cast
  CenterAnImage
  Colored2DImageFusion
  CombineImages
  DrawOnAnImage
  ExtractComponents
  Flip
  ImageAccumulateGreyscale
  ImageAnisotropicDiffusion2D
  ImageCheckerboard
  ImageCityBlockDistance
  ImageMagnify
  ImageNonMaximumSuppression
  ImageRotate
  ImageSeparableConvolution
  ImageToPolyDataFilter
  ImageToStructuredPoints
  InteractWithImage
  PickPixel
  PickPixel2
  RGBToHSV
  RTAnalyticSource
  ResizeImage
  StaticImage
)
INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)
SET(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

ADD_TEST(${KIT}-CannyEdgeDetector ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestCannyEdgeDetector ${DATA}/Gourds.png)

ADD_TEST(${KIT}-Cast ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestCast  ${DATA}/Ox.jpg ${TEMP}/Cast.jpg)

ADD_TEST(${KIT}-CenterAnImage ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestCenterAnImage  ${DATA}/Ox.jpg)

ADD_TEST(${KIT}-Colored2DImageFusion ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestColored2DImageFusion  ${DATA}/Ox.jpg ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-CombineImages ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestCombineImages  ${DATA}/Ox.jpg ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-DrawOnAnImage ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestDrawOnAnImage  ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-ExtractComponents ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestExtractComponents  ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-Flip ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestFlip  ${DATA}/Gourds2.jpg ${TEMP}/Flip.jpg )

#ADD_TEST(${KIT}-HistogramBarChart ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
#  TestHistogramBarChart ${DATA}/Gourds2.jpg)

#ADD_TEST(${KIT}-HistogramXYPlot ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
#  TestHistogramXYPlot  ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-ImageAccumulateGreyscale ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageAccumulateGreyscale  ${DATA}/Ox.jpg)

ADD_TEST(${KIT}-ImageAnisotropicDiffusion2D ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageAnisotropicDiffusion2D  ${DATA}/cake_easy.jpg)

ADD_TEST(${KIT}-ImageCheckerboard ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageCheckerboard  ${DATA}/Ox.jpg ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-ImageCityBlockDistance ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageCityBlockDistance ${DATA}/Yinyang.jpg -E 15)

ADD_TEST(${KIT}-ImageDilateErode3D ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageDilateErode3D ${DATA}/Yinyang.png -E 25)

ADD_TEST(${KIT}-ImageHybridMedian2D ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageHybridMedian2D ${DATA}/Gourds.png)

ADD_TEST(${KIT}-ImageMagnify ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageMagnify ${DATA}/Gourds.png)

# The ImageNoiseSource is inherently random
ADD_TEST(${KIT}-ImageNoiseSource ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageNoiseSource -E 999999)

ADD_TEST(${KIT}-ImageNonMaximumSuppression ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageNonMaximumSuppression -E 20)

ADD_TEST(${KIT}-ImageOpenClose3D ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageOpenClose3D ${DATA}/Yinyang.png -E 25)

ADD_TEST(${KIT}-ImageToPolyDataFilter ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageToPolyDataFilter ${DATA}/Gourds.png)

ADD_TEST(${KIT}-ImageRotate ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageRotate ${DATA}/Gourds.png 45)

ADD_TEST(${KIT}-ImageSeparableConvolution ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageSeparableConvolution ${DATA}/Yinyang.png -E 25)
  
ADD_TEST(${KIT}-ImageToStructuredPoints ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageToStructuredPoints -E 25)

ADD_TEST(${KIT}-PickPixel ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestPickPixel  ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-PickPixel2 ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestPickPixel2  ${DATA}/ColorCells.tif)

ADD_TEST(${KIT}-ImageRange3D ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestImageRange3D  ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-RGBToHSV ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestRGBToHSV ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-StaticImage ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestStaticImage ${DATA}/Ox.jpg)

ADD_TEST(${KIT}-Transparency ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestTransparency ${DATA}/Gourds2.jpg)

ADD_TEST(${KIT}-RTAnalyticSource ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestRTAnalyticSource -E 20)

ADD_TEST(${KIT}-ResizeImage ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestResizeImage ${DATA}/Gourds2.jpg 640 480 1)


