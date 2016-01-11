#include <vtkSmartPointer.h>
#include <vtkVoxelModeller.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkImageCast.h>
#include <vtkXMLImageDataWriter.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
  
  double bounds[6];
  sphereSource->GetOutput()->GetBounds(bounds);
  
  vtkSmartPointer<vtkVoxelModeller> voxelModeller = 
      vtkSmartPointer<vtkVoxelModeller>::New();
  voxelModeller->SetSampleDimensions(20,20,20);
  //voxelModeller->SetSampleDimensions(100,100,100);
  voxelModeller->SetModelBounds(bounds);
  voxelModeller->SetOutputScalarTypeToUnsignedChar();
      
  voxelModeller->SetInputConnection(sphereSource->GetOutputPort());
  voxelModeller->Update();
  
  vtkSmartPointer<vtkImageCast> imageCastFilter = 
      vtkSmartPointer<vtkImageCast>::New();
  imageCastFilter->SetInputConnection(voxelModeller->GetOutputPort());
  imageCastFilter->SetOutputScalarTypeToUnsignedChar();
  imageCastFilter->Update();
  
  vtkSmartPointer<vtkXMLImageDataWriter> writer = 
      vtkSmartPointer<vtkXMLImageDataWriter>::New();
  writer->SetInputConnection(imageCastFilter->GetOutputPort());
  writer->SetFileName("voxel.vti");
  writer->Write();
  
  return EXIT_SUCCESS;
}
