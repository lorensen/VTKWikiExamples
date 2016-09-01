#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTrackball.h>
#include <vtkDistanceToCamera.h>

int main(int argc, char *argv[])
{
  //create a set of points
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> vertices = 
    vtkSmartPointer<vtkCellArray>::New();
  vtkIdType pid[1];
  pid[0] = points->InsertNextPoint ( 1.0, 0.0, 0.0 );
  vertices->InsertNextCell ( 1,pid );
  pid[0] = points->InsertNextPoint ( 0.0, 0.0, 0.0 );
  vertices->InsertNextCell ( 1,pid );
  pid[0] = points->InsertNextPoint ( 0.0, 1.0, 0.0 );
  vertices->InsertNextCell ( 1,pid );
  
  //create a polydata
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints ( points );
  polydata->SetVerts ( vertices );
  
  //create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInput(polydata);

  // create an actor
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // a renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(0,1,1); // Background color white

  // render an image (lights and cameras are created automatically)
  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  
  renderWindowInteractor->SetInteractorStyle( style );
  
  // begin mouse interaction
  renderWindowInteractor->Start();
    
  vtkSmartPointer<vtkDistanceToCamera> distanceToCamera = 
    vtkSmartPointer<vtkDistanceToCamera>::New();

  /*
  //write the polydata to a file
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName ( "TrianglePoints.vtp" );
  writer->SetInput ( polydata );
  writer->Write();
*/
  return EXIT_SUCCESS;
}
