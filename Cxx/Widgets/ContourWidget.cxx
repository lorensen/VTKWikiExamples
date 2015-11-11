#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkContourWidget.h>
#include <vtkOrientedGlyphContourRepresentation.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>
#include <vtkDebugLeaks.h>
#include <vtkCamera.h>
#include <vtkPlane.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkMath.h>
#include <vtkWidgetEvent.h>
#include <vtkWidgetEventTranslator.h>

int main( int argc, char *argv[] )
{
  // Create the RenderWindow, Renderer and both Actors
  //
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->SetBackground(0.1, 0.2, 0.4);
  renderWindow->SetSize(600, 600);

  vtkSmartPointer<vtkOrientedGlyphContourRepresentation> contourRep = 
      vtkSmartPointer<vtkOrientedGlyphContourRepresentation>::New();
  contourRep->GetLinesProperty()->SetColor(1, 0, 0); //set color to red

  vtkSmartPointer<vtkContourWidget> contourWidget = 
      vtkSmartPointer<vtkContourWidget>::New();
  contourWidget->SetInteractor(interactor);
  contourWidget->SetRepresentation(contourRep);
  contourWidget->On();

  for (int i = 0; i < argc; i++)
    {
    if (strcmp("-Shift", argv[i]) == 0)
      {
      contourWidget->GetEventTranslator()->RemoveTranslation( 
                                        vtkCommand::LeftButtonPressEvent );
      contourWidget->GetEventTranslator()->SetTranslation( 
                                        vtkCommand::LeftButtonPressEvent,
                                        vtkWidgetEvent::Translate );
      }
    else if (strcmp("-Scale", argv[i]) == 0)
      {
      contourWidget->GetEventTranslator()->RemoveTranslation( 
                                        vtkCommand::LeftButtonPressEvent );
      contourWidget->GetEventTranslator()->SetTranslation( 
                                        vtkCommand::LeftButtonPressEvent,
                                        vtkWidgetEvent::Scale );
      }
    }


  vtkSmartPointer<vtkPolyData> pd = vtkSmartPointer<vtkPolyData>::New();

  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
  vtkIdType* lineIndices = new vtkIdType[21];
  for (int i = 0; i< 20; i++)
    {
    const double angle = 2.0*vtkMath::Pi()*i/20.0;
    points->InsertPoint(static_cast<vtkIdType>(i), 0.1*cos(angle),
                        0.1*sin(angle), 0.0 );
    lineIndices[i] = static_cast<vtkIdType>(i);
    }

  lineIndices[20] = 0;
  lines->InsertNextCell(21,lineIndices);
  delete [] lineIndices;
  pd->SetPoints(points);
  pd->SetLines(lines);
  
  contourWidget->Initialize(pd);
  contourWidget->Render();
  renderer->ResetCamera();
  renderWindow->Render();
    
  interactor->Initialize();
  interactor->Start();
  
  contourWidget->Off();
  
  return EXIT_SUCCESS;
}
