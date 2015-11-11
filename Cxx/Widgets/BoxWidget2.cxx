#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkBoxWidget2.h>
#include <vtkBoxRepresentation.h>
#include <vtkCommand.h>

// This does the actual work.
// Callback for the interaction
class vtkBoxCallback : public vtkCommand
{
  public:
    static vtkBoxCallback *New()
    {
      return new vtkBoxCallback;
    }
    
    virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      
      vtkBoxWidget2 *boxWidget = 
        reinterpret_cast<vtkBoxWidget2*>(caller);
      
      // Get the actual box coordinates/planes
      vtkSmartPointer<vtkPolyData> polydata = 
        vtkSmartPointer<vtkPolyData>::New();
      static_cast<vtkBoxRepresentation*>(boxWidget->GetRepresentation())->GetPolyData (polydata);
      
      // Display the center of the box
      double p[3];
      polydata->GetPoint(14,p); // As per the vtkBoxRepresentation documentation, the 15th point (index 14) is the center of the box
      std::cout << "Box center: " << p[0] << " " << p[1] << " " << p[2] << std::endl;
    }
    vtkBoxCallback(){}
    
};
 
int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  //renderer->AddActor(actor);
  
  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkBoxWidget2> boxWidget = 
    vtkSmartPointer<vtkBoxWidget2>::New();
  boxWidget->SetInteractor(renderWindowInteractor);
  //boxWidget->CreateDefaultRepresentation();
  
  vtkSmartPointer<vtkBoxRepresentation> boxRepresentation = 
    vtkSmartPointer<vtkBoxRepresentation>::New();
  boxWidget->SetRepresentation(boxRepresentation);
  
  vtkSmartPointer<vtkBoxCallback> boxCallback = 
    vtkSmartPointer<vtkBoxCallback>::New();
  //boxCallback->SphereSource = sphereSource;
 
  boxWidget->AddObserver(vtkCommand::InteractionEvent,boxCallback);
  
  // Render
  renderWindow->Render();
  
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  boxWidget->On();
  
  // Begin mouse interaction
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
