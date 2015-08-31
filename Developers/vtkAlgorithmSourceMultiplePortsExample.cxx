#include <vtkSmartPointer.h>

#include "vtkTestSource.h"
#include "vtkTestA.h"
#include "vtkTestB.h"

int main (int argc, char *argv[])
{
  vtkTestSource* source = vtkTestSource::New();
  source->Update();
  
  vtkTestA* testa = source->GetOutputA();
  vtkTestB* testb = source->GetOutputB();
  
  std::cout << testa->GetValue() << std::endl;
  
  std::cout << testb->GetValue() << std::endl;
  
  return EXIT_SUCCESS;
}
