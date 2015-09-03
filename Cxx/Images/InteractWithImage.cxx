#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkCommand.h>
#include <vtkCallbackCommand.h>
#include <vtkSmartPointer.h>

int main(int argc, char* argv[])
{
  // Parse input arguments
  if ( argc != 2 )
    {
    std::cout << "Required parameters: Filename" << std::endl;
    return EXIT_FAILURE;
    }

  std::string InputFilename = argv[1];

  // Read the image
  vtkSmartPointer<vtkJPEGReader> jPEGReader = 
      vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader->SetFileName(InputFilename.c_str());
  jPEGReader->Update();

  // Create an actor
  vtkSmartPointer<vtkImageActor> actor = 
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(jPEGReader->GetOutputPort());

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style = 
    vtkSmartPointer<vtkInteractorStyleImage>::New();
 
  renderWindowInteractor->SetInteractorStyle(style);
  
  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
