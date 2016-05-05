#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPolyLine.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPointSource.h>
#include <vtkMarchingContourFilter.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkVoxelModeller.h>

int main(int, char *[])
{
    // Create a point cloud
    unsigned int numberOfPoints = 50;
    vtkSmartPointer<vtkPointSource> pointSource =
      vtkSmartPointer<vtkPointSource>::New();
    pointSource->SetCenter(0.0, 0.0, 0.0);
    pointSource->SetNumberOfPoints(numberOfPoints);
    pointSource->SetRadius(5.0);
    pointSource->Update();

    vtkSmartPointer<vtkVertexGlyphFilter> vertexGlyphFilter =
      vtkSmartPointer<vtkVertexGlyphFilter>::New();
    vertexGlyphFilter->AddInputData(pointSource->GetOutput());
    vertexGlyphFilter->Update();

    vtkSmartPointer<vtkDoubleArray> scalars = vtkSmartPointer<vtkDoubleArray>::New();
    scalars->SetNumberOfTuples(numberOfPoints);
    scalars->SetNumberOfComponents(1);

     for(vtkIdType i = 0; i < numberOfPoints; ++i)
     {
         scalars->InsertValue(i,10.0f*drand48());
     }

     vtkPolyData* data = pointSource->GetOutput();
     data->GetPointData()->SetScalars(scalars);


     {
     vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
     writer->SetFileName("input.vtp");
     writer->SetInputData(data);
     writer->Update();
     }

     vtkSmartPointer<vtkVoxelModeller> voxelModeller =
       vtkSmartPointer<vtkVoxelModeller>::New();
     double bounds[6];
     data->GetBounds(bounds);
     voxelModeller->SetSampleDimensions(50,50,50);
     voxelModeller->SetModelBounds(bounds);
     voxelModeller->SetScalarTypeToFloat();
//     voxelModeller->SetMaximumDistance(.1);
     voxelModeller->SetInputData(data);
     voxelModeller->Update();

    // Create a vtkPoints object and store the points in it
    vtkSmartPointer<vtkMarchingContourFilter> marchingContourFilter =
      vtkSmartPointer<vtkMarchingContourFilter>::New();
    marchingContourFilter->SetInputData(voxelModeller->GetOutput());
    marchingContourFilter->GenerateValues(3, 0.0f, 10.0f);
//    marchingContourFilter->GenerateValues(1, 5.0f, 5.0f);
    marchingContourFilter->Update();

    {
    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName("test.vtp");
    writer->SetInputData(marchingContourFilter->GetOutput());
    writer->Update();
    }
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(marchingContourFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

  renderWindowInteractor->SetInteractorStyle( style );

  // Add the actor to the scene
  renderer->AddActor(actor);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
