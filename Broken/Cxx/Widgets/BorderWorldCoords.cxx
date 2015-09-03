#include <vtkSmartPointer.h>
#include <vtkWidgetCallbackMapper.h>
#include <vtkCommand.h>
#include <vtkWidgetEvent.h>
#include <vtkObjectFactory.h>
#include <vtkActor.h>
#include <vtkBorderRepresentation.h>
#include <vtkBorderWidget.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>

#include "RegionSelectionWidget.h"

int main(int, char *[])
{
  // Sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(4.0);
  sphereSource->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<RegionSelectionWidget> regionSelectionWidget =
    vtkSmartPointer<RegionSelectionWidget>::New();
  regionSelectionWidget->SetInteractor(renderWindowInteractor);
  regionSelectionWidget->CreateDefaultRepresentation();
  regionSelectionWidget->SelectableOff();
  regionSelectionWidget->Renderer = renderer;

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->Render();

  renderWindowInteractor->Initialize();

  // Ideally we would do this:
   vtkBorderRepresentation* representation = static_cast<vtkBorderRepresentation*>(regionSelectionWidget->GetRepresentation());
   representation->GetPositionCoordinate()->SetCoordinateSystemToWorld();
   representation->GetPosition2Coordinate()->SetCoordinateSystemToWorld();
   representation->SetPosition(0, 0);
   representation->SetPosition2(5, 5);
  
  regionSelectionWidget->On();

  renderer->ResetCamera();
  renderWindow->Render();
  
  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
