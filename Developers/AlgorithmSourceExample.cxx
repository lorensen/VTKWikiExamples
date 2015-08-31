#include <vtkSmartPointer.h>

#include "vtkTestSource.h"
#include "vtkTest.h"

int main(int, char *[])
{
  vtkTestSource* source = vtkTestSource::New();
  source->Update();
  
  vtkTest* test = source->GetOutput();
  std::cout << test->GetValue() << std::endl;
  
  return EXIT_SUCCESS;
}
