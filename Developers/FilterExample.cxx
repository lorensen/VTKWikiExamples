#include <vtkSmartPointer.h>

#include "vtkTestFilter.h"

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.0, 0.0);
  
  vtkSmartPointer<vtkPolyData> inputPolydata =   
    vtkSmartPointer<vtkPolyData>::New();
  inputPolydata->SetPoints(points);
  
  std::cout << "Input points: " << inputPolydata->GetNumberOfPoints() 
            << std::endl;
  
  vtkSmartPointer<vtkTestFilter> filter = 
    vtkSmartPointer<vtkTestFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  filter->SetInput(inputPolydata);
#else
  filter->SetInputData(inputPolydata);
#endif
  filter->Update();
  
  vtkPolyData* outputPolydata = filter->GetOutput();
  
  std::cout << "Output points: " << outputPolydata->GetNumberOfPoints() 
            << std::endl;
  
  return EXIT_SUCCESS;
}
