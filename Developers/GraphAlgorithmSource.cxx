#include <vtkSmartPointer.h>
#include <vtkGraph.h>
#include <vtkMutableUndirectedGraph.h>

#include "vtkTest GraphAlgorithmSource.h"

int main (int, char *[])
{
  vtkSmartPointer<vtkTest GraphAlgorithmSource> source =
    vtkSmartPointer<vtkTest GraphAlgorithmSource>::New();
  source->Update();
  
  vtkGraph* outputGraph = source->GetOutput();
  
  std::cout << "Output number of vertices: "
            << outputGraph->GetNumberOfVertices() << std::endl;
  
  return EXIT_SUCCESS;
}
