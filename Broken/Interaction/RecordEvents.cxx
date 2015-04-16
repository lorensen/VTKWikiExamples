#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorEventRecorder.h>

int main(int argc, char*argv[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
  
  // Add the actors to the renderer, set the background and size
  
  renderer->AddActor(actor);
  
  vtkSmartPointer<vtkInteractorEventRecorder> recorder = vtkSmartPointer<vtkInteractorEventRecorder>::New();
  recorder->SetInteractor(interactor);
  recorder->SetFileName("events.log");

  renderWindow->Render();
  interactor->Initialize();
  recorder->EnabledOn();
  recorder->Record();
  
  interactor->Start();
  
  return EXIT_SUCCESS;
}
