#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkVectorDot.h>

int main(int, char *[])
{
  // Generate data
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);
  points->InsertNextPoint(2,0,0);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Add normals
  vtkSmartPointer<vtkFloatArray> normals =
    vtkSmartPointer<vtkFloatArray>::New();
  normals->SetNumberOfComponents(3);
  normals->SetName("Normals");

  float n0[3] = {1,0,0};
  float n1[3] = {1,0,0};
  float n2[3] = {1,0,0};
  normals->InsertNextTypedTuple(n0);
  normals->InsertNextTypedTuple(n1);
  normals->InsertNextTypedTuple(n2);

  polydata->GetPointData()->SetNormals(normals);

  // Add vectors
  vtkSmartPointer<vtkFloatArray> vectors =
    vtkSmartPointer<vtkFloatArray>::New();
  vectors->SetNumberOfComponents(3);
  vectors->SetName("Vectors");

  float v0[3] = {1,0,0};
  float v1[3] = {.707,.707,0};
  float v2[3] = {0,1,0};
  vectors->InsertNextTypedTuple(v0);
  vectors->InsertNextTypedTuple(v1);
  vectors->InsertNextTypedTuple(v2);

  polydata->GetPointData()->SetVectors(vectors);

  // Compute the dot products between normals and vectors
  vtkSmartPointer<vtkVectorDot> vectorDot =
      vtkSmartPointer<vtkVectorDot>::New();
#if VTK_MAJOR_VERSION <= 5
  vectorDot->SetInputConnection(polydata->GetProducerPort());
#else
  vectorDot->SetInputData(polydata);
#endif
  vectorDot->Update();

  // Get the results
  vtkFloatArray* scalars = vtkFloatArray::SafeDownCast ( vectorDot->GetOutput()->GetPointData()->GetScalars() );

  // Output the results
  for(vtkIdType i = 0; i < scalars->GetNumberOfTuples(); i++)
    {
    std::cout << "Value " << i << " : " << scalars->GetValue(i) << std::endl;
    }

  return EXIT_SUCCESS;
}
