#include <vtkSmartPointer.h>
#include <vtkDiagonalMatrixSource.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDiagonalMatrixSource> diagonalMatrixSource = 
      vtkSmartPointer<vtkDiagonalMatrixSource>::New();
  diagonalMatrixSource->SetExtents(5);
  diagonalMatrixSource->Update();

  diagonalMatrixSource->Print(std::cout);

  return EXIT_SUCCESS;
}
