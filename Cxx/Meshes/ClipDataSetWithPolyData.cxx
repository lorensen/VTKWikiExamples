#include <vtkSmartPointer.h>
#include <vtkConeSource.h>
#include <vtkImplicitPolyDataDistance.h>
#include <vtkPointData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkFloatArray.h>
#include <vtkRectilinearGrid.h>
#include <vtkClipDataSet.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRectilinearGridGeometryFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <map>

int main (int, char *[])
{
  // Create polydata to slice the grid with. In this case, use a cone. This could
  // be any polydata including a stl file.
  vtkSmartPointer<vtkConeSource> cone =
    vtkSmartPointer<vtkConeSource>::New();
  cone->SetResolution(50);
  cone->Update();
 
  // Implicit function that will be used to slice the mesh
  vtkSmartPointer<vtkImplicitPolyDataDistance> implicitPolyDataDistance =
    vtkSmartPointer<vtkImplicitPolyDataDistance>::New();
  implicitPolyDataDistance->SetInput(cone->GetOutput());
 
  // create a grid
  int dimension = 51;
  vtkSmartPointer<vtkFloatArray> xCoords =
    vtkSmartPointer<vtkFloatArray>::New();
  for (unsigned int i = 0; i < dimension; ++i)
    {
    xCoords->InsertNextValue(-1.0 + i * 2.0 / static_cast<float>(dimension));
    }
  vtkSmartPointer<vtkFloatArray> yCoords =
    vtkSmartPointer<vtkFloatArray>::New();
  for (unsigned int i = 0; i < dimension; ++i)
    {
    yCoords->InsertNextValue(-1.0 + i * 2.0 / static_cast<float>(dimension));
    }
  vtkSmartPointer<vtkFloatArray> zCoords =
    vtkSmartPointer<vtkFloatArray>::New();
  for (unsigned int i = 0; i < dimension; ++i)
    {
    zCoords->InsertNextValue(-1.0 + i * 2.0 / static_cast<float>(dimension));
    }
  // The coordinates are assigned to the rectilinear grid. Make sure that
  // the number of values in each of the XCoordinates, YCoordinates,
  // and ZCoordinates is equal to what is defined in SetDimensions().
  vtkSmartPointer<vtkRectilinearGrid> rgrid =
    vtkSmartPointer<vtkRectilinearGrid>::New();
  rgrid->SetDimensions(xCoords->GetNumberOfTuples(),
                       yCoords->GetNumberOfTuples(),
                       zCoords->GetNumberOfTuples());
  rgrid->SetXCoordinates(xCoords);
  rgrid->SetYCoordinates(yCoords);
  rgrid->SetZCoordinates(zCoords);
 
  // Create an array to hold distance information
  vtkSmartPointer<vtkFloatArray> signedDistances =
    vtkSmartPointer<vtkFloatArray>::New();
  signedDistances->SetNumberOfComponents(1);
  signedDistances->SetName("SignedDistances");
 
  // Evaluate the signed distance function at all of the grid points
  for (vtkIdType pointId = 0; pointId < rgrid->GetNumberOfPoints(); ++pointId)
    {
    double p[3];
    rgrid->GetPoint(pointId, p);
    double signedDistance = implicitPolyDataDistance->EvaluateFunction(p);
    signedDistances->InsertNextValue(signedDistance);
    }

  // Add the SignedDistances to the grid
  rgrid->GetPointData()->SetScalars(signedDistances);
 
  // Use vtkClipDataSet to slice the grid with the polydata
  vtkSmartPointer<vtkClipDataSet> clipper =
    vtkSmartPointer<vtkClipDataSet>::New();
  clipper->SetInputData(rgrid);
  clipper->InsideOutOn();
  clipper->SetValue(0.0);
  clipper->SetValue(.1);
  clipper->Update();

  // --- mappers, actors, render, etc. ---
  // mapper and actor to view the cone
  vtkSmartPointer<vtkPolyDataMapper> coneMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  coneMapper->SetInputConnection(cone->GetOutputPort());
  vtkSmartPointer<vtkActor> coneActor =
    vtkSmartPointer<vtkActor>::New();
  coneActor->SetMapper(coneMapper);
 
  // geometry filter to view the background grid
  vtkSmartPointer<vtkRectilinearGridGeometryFilter> geometryFilter =
    vtkSmartPointer<vtkRectilinearGridGeometryFilter>::New();
  geometryFilter->SetInputData(rgrid);
  geometryFilter->SetExtent(0, dimension, 0, dimension, dimension/2, dimension/2);
  geometryFilter->Update();
 
  vtkSmartPointer<vtkPolyDataMapper> rgridMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  rgridMapper->SetInputConnection(geometryFilter->GetOutputPort());
  rgridMapper->SetScalarRange(rgrid->GetPointData()->GetArray("SignedDistances")->GetRange()); 

  vtkSmartPointer<vtkActor> wireActor =
    vtkSmartPointer<vtkActor>::New();
  wireActor->SetMapper(rgridMapper);
  wireActor->GetProperty()->SetRepresentationToWireframe();
 
  // mapper and actor to view the clipped mesh
  vtkSmartPointer<vtkDataSetMapper> clipperMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  clipperMapper->SetInputConnection(clipper->GetOutputPort());
  clipperMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> clipperActor =
    vtkSmartPointer<vtkActor>::New();
  clipperActor->SetMapper(clipperMapper);
  clipperActor->GetProperty()->SetRepresentationToWireframe();
  clipperActor->GetProperty()->SetColor(0.89,0.81,0.34); // banana
 
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(.4, .5, .6);
 
  // add the actors
//  renderer->AddActor(coneActor);
  renderer->AddActor(wireActor);
  renderer->AddActor(clipperActor);
 
  vtkSmartPointer<vtkRenderWindow> renwin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renwin);
 
  // Start
  renwin->Render();
  interactor->Start();

  // Generate a report
  vtkIdType numberOfCells = clipper->GetOutput()->GetNumberOfCells();
  std::cout << "------------------------" << std::endl;
  std::cout << "The clipped dataset contains a " << std::endl
            << clipper->GetOutput()->GetClassName() 
            <<  " that has " << numberOfCells << " cells" << std::endl;
  typedef std::map<int,int> CellContainer;
  CellContainer cellMap;
  for (vtkIdType i = 0; i < numberOfCells; i++)
    {
    cellMap[clipper->GetOutput()->GetCellType(i)]++;
    }

  CellContainer::const_iterator it = cellMap.begin();
  while (it != cellMap.end())
    {
    std::cout << "\tCell type " 
              << vtkCellTypes::GetClassNameFromTypeId(it->first)
              << " occurs " << it->second << " times." << std::endl;
    ++it;
    }

  return EXIT_SUCCESS;
}
