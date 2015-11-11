#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter ( 0.0, 0.0, 0.0 );
  sphereSource->SetRadius ( 5.0 );
  sphereSource->Update();

  vtkPolyData* polydata = sphereSource->GetOutput();

  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInput ( polydata );
#else
  mapper->SetInputData ( polydata );
#endif

  // Create an actor
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper ( mapper );

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer ( renderer );

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow ( renderWindow );

  // Add the actors to the scene
  renderer->AddActor ( actor );
  renderer->SetBackground ( 1,1,1 ); // Background color white

  // Setup the text and add it to the window
  vtkSmartPointer<vtkTextActor> textActor = 
    vtkSmartPointer<vtkTextActor>::New();
  textActor->GetTextProperty()->SetFontSize ( 24 );
  textActor->SetPosition2 ( 10, 40 );
  renderer->AddActor2D ( textActor );
  textActor->SetInput ( "Hello world" );
  textActor->GetTextProperty()->SetColor ( 1.0,0.0,0.0 );
  
  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
