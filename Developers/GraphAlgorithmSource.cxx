#include <vtkSmartPointer.h>
#include <vtkGraph.h>
#include <vtkMutableUndirectedGraph.h>

#include "vtkTestSource.h"

int main (int, char *[])
{
  vtkSmartPointer<vtkTestSource> source =
    vtkSmartPointer<vtkTestSource>::New();
  source->Update();
  
  vtkGraph* outputGraph = source->GetOutput();
  
  std::cout << "Output number of vertices: "
            << outputGraph->GetNumberOfVertices() << std::endl;
  
  return EXIT_SUCCESS;
}
