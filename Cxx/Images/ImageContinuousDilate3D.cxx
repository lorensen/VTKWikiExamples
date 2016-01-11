#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkImageData.h>
#include <vtkImageContinuousDilate3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkXMLImageDataReader.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();

  if(argc < 2)
    {
    // Create an image
    vtkSmartPointer<vtkImageCanvasSource2D> source =
      vtkSmartPointer<vtkImageCanvasSource2D>::New();
    source->SetExtent(0, 20, 0, 20, 0, 20);
    source->Update();
    image->ShallowCopy(source->GetOutput());
    }
  else
    {
    vtkSmartPointer<vtkXMLImageDataReader> reader =
      vtkSmartPointer<vtkXMLImageDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    image->ShallowCopy(reader->GetOutput());
    }


  vtkSmartPointer<vtkImageContinuousDilate3D> dilateFilter =
    vtkSmartPointer<vtkImageContinuousDilate3D>::New();
#if VTK_MAJOR_VERSION <= 5
  dilateFilter->SetInputConnection(image->GetProducerPort());
#else
  dilateFilter->SetInputData(image);
#endif
  dilateFilter->Update();

  vtkSmartPointer<vtkDataSetMapper> originalMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  originalMapper->SetInputConnection(image->GetProducerPort());
#else
  originalMapper->SetInputData(image);
#endif
  originalMapper->Update();

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetRepresentationToPoints();

  vtkSmartPointer<vtkDataSetMapper> dilatedMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  dilatedMapper->SetInputConnection(dilateFilter->GetOutputPort());
  dilatedMapper->Update();
  
  vtkSmartPointer<vtkActor> dilatedActor =
    vtkSmartPointer<vtkActor>::New();
  dilatedActor->SetMapper(dilatedMapper);

  // Visualize
  double leftViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double rightViewport[4] = {0.5, 0.0, 1.0, 1.0};

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkRenderer> leftRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  leftRenderer->AddActor(originalActor);
  rightRenderer->AddActor(dilatedActor);

  leftRenderer->ResetCamera();
  rightRenderer->ResetCamera();

  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}
