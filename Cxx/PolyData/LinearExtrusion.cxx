#include <vtkSmartPointer.h>
#include <vtkVectorText.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkTriangleFilter.h>

int main(int, char *[])
{
  // Create vector text
  vtkSmartPointer<vtkVectorText> vecText = 
    vtkSmartPointer<vtkVectorText>::New();
  vecText->SetText("Text!");
  vecText->Update();
    
  // Apply linear extrusion 
  vtkSmartPointer<vtkLinearExtrusionFilter> extrude = 
    vtkSmartPointer<vtkLinearExtrusionFilter>::New();
  extrude->SetInputConnection( vecText->GetOutputPort());
  extrude->SetExtrusionTypeToNormalExtrusion();
  extrude->SetVector(0, 0, 1 );
  extrude->SetScaleFactor (0.5);
  extrude->Update();
    
  vtkSmartPointer<vtkTriangleFilter> triangleFilter =
    vtkSmartPointer<vtkTriangleFilter>::New();
  triangleFilter->SetInputConnection(extrude->GetOutputPort());
  triangleFilter->Update();
    
  // write an STL file
  std::string outputFilename = "extruded.vtp";
  vtkSmartPointer<vtkXMLPolyDataWriter> writer = 
    vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName(outputFilename.c_str());
  writer->SetInputConnection(triangleFilter->GetOutputPort());
  writer->Write();

  return EXIT_SUCCESS;
}
