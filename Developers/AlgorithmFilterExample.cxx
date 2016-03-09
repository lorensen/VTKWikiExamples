#include <vtkSmartPointer.h>

#include "vtkTestFilter.h"
#include "vtkTest.h"

int main(int, char *[])
{
  vtkSmartPointer<vtkTest> inputTest = 
    vtkSmartPointer<vtkTest>::New();
  inputTest->SetValue(5.6);
  std::cout << "Input value: " << InputTest->GetValue() << std::endl;
  
  vtkSmartPointer<vtkTestFilter> filter = vtkTestFilter::New();
  filter->SetInput(InputTest);
  filter->Update();
  
  vtkTest* outputTest = filter->GetOutput();
  std::cout << "Output value: " << outputTest->GetValue() << std::endl;
  std::cout << "Input value is still: " << inputTest->GetValue() << std::endl;
  
  return EXIT_SUCCESS;
}
