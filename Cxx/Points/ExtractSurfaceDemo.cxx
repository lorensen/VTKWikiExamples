#include <vtkSmartPointer.h>
#include <vtkPLYReader.h>

#include <vtkPCANormalEstimation.h>
#include <vtkSignedDistance.h>
#include <vtkExtractSurface.h>
#include <vtkPointData.h>

#include <vtkArrowSource.h>
#include <vtkMaskPoints.h>
#include <vtkGlyph3D.h>

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

static void MakeGlyphs(vtkPolyData *src, double size, vtkGlyph3D *glyph);

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " file.ply" << std::endl;
    return EXIT_FAILURE;
  }
  vtkSmartPointer<vtkPLYReader> reader =
    vtkSmartPointer<vtkPLYReader>::New();
  reader->SetFileName (argv[1]);
  reader->Update();

  double bounds[6];
  reader->GetOutput()->GetBounds(bounds);
  double range[3];
  for (int i = 0; i < 3; ++i)
  {
    range[i] = bounds[2*i + 1] - bounds[2*i];
  }

  int sampleSize = 15;

  std::cout << "Sample size is: " << sampleSize << std::endl;
  // Do we need to estimate normals?
  vtkSmartPointer<vtkSignedDistance> distance =
    vtkSmartPointer<vtkSignedDistance>::New();
  vtkSmartPointer<vtkPCANormalEstimation> normals =
    vtkSmartPointer<vtkPCANormalEstimation>::New();
  if (reader->GetOutput()->GetPointData()->GetNormals())
    {
    std::cout << "Using normals from input file" << std::endl;
    distance->SetInputConnection (reader->GetOutputPort());
    }
  else
    {
    std::cout << "Estimating normals using PCANormalEstimation" << std::endl;
    normals->SetInputConnection (reader->GetOutputPort());
    normals->SetSampleSize(sampleSize);
    normals->SetNormalOrientationToGraphTraversal();
    normals->FlipNormalsOn();
    distance->SetInputConnection (normals->GetOutputPort());
    }
  std::cout << "Range: "
            << range[0] << ", "
            << range[1] << ", "
            << range[2] << std::endl;
  int dimension = 512;
  double radius;
  radius = range[0] / static_cast<double>(dimension) * 3; // ~3 voxels
  std::cout << "Radius: " << radius << std::endl;

  distance->SetRadius(radius);
  distance->SetDimensions(dimension, dimension, dimension);
  distance->SetBounds(
    bounds[0] - range[0] * .1,
    bounds[1] + range[0] * .1,
    bounds[2] - range[1] * .1,
    bounds[3] + range[1] * .1,
    bounds[4] - range[2] * .1,
    bounds[5] + range[2] * .1);

  vtkSmartPointer<vtkExtractSurface> surface =
    vtkSmartPointer<vtkExtractSurface>::New();
  surface->SetInputConnection (distance->GetOutputPort());
  surface->SetRadius(radius * .99);
  surface->HoleFillingOn();
  surface->Update();

  vtkSmartPointer<vtkGlyph3D> glyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  if (reader->GetOutput()->GetPointData()->GetNormals())
    {
    MakeGlyphs(reader->GetOutput(), radius * 2.0, glyph3D.GetPointer());
    }
  else
    {
    MakeGlyphs(normals->GetOutput(), radius * 2.0, glyph3D.GetPointer());
    }
  vtkSmartPointer<vtkPolyDataMapper> surfaceMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  surfaceMapper->SetInputConnection(surface->GetOutputPort());
  surfaceMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkProperty> backProp =
    vtkSmartPointer<vtkProperty>::New();
  backProp->SetColor(0.8900, 0.8100, 0.3400);

  vtkSmartPointer<vtkActor> surfaceActor =
    vtkSmartPointer<vtkActor>::New();
  surfaceActor->SetMapper(surfaceMapper);
  surfaceActor->GetProperty()->SetColor(1.0000, 0.4900, 0.2500);
  surfaceActor->SetBackfaceProperty(backProp);

  vtkSmartPointer<vtkPolyDataMapper> glyph3DMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  glyph3DMapper->SetInputConnection(glyph3D->GetOutputPort());

  vtkSmartPointer<vtkActor> glyph3DActor =
    vtkSmartPointer<vtkActor>::New();
  glyph3DActor->SetMapper(glyph3DMapper);
  glyph3DActor->GetProperty()->SetColor(0.6902, 0.7686, 0.8706);
  
  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(.3, .4, .6);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(512,512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  
  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(surfaceActor);
  ren1->AddActor(glyph3DActor);

  // Generate an interesting view
  //
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(120);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->GetActiveCamera()->Dolly(1.0);
  ren1->ResetCameraClippingRange();

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
void MakeGlyphs(vtkPolyData *src, double size, vtkGlyph3D *glyph)
{
  vtkSmartPointer<vtkMaskPoints> maskPts =
    vtkSmartPointer<vtkMaskPoints>::New();
  maskPts->SetOnRatio(20);
  maskPts->RandomModeOn();
  maskPts->SetInputData(src);
  // Source for the glyph filter
  vtkSmartPointer<vtkArrowSource> arrow =
    vtkSmartPointer<vtkArrowSource>::New();
  arrow->SetTipResolution(16);
  arrow->SetTipLength(.3);
  arrow->SetTipRadius(.1);

  glyph->SetSourceConnection(arrow->GetOutputPort());
  glyph->SetInputConnection(maskPts->GetOutputPort());
  glyph->SetVectorModeToUseNormal();
//  glyph->SetColorModeToColorByVector();
  glyph->SetScaleModeToScaleByVector();
  glyph->SetScaleFactor(size);
  glyph->OrientOn();
  glyph->Update();
}
