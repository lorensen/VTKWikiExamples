#include <vtkAdjacencyMatrixToEdgeTable.h>
#include <vtkArrayData.h>
#include <vtkArrayPrint.h>
#include <vtkDenseArray.h>
#include <vtkGraphLayoutStrategy.h>
#include <vtkGraphLayoutView.h>
#include <vtkGraphWriter.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSimple2DLayoutStrategy.h>
#include <vtkSmartPointer.h>
#include <vtkTable.h>
#include <vtkTableToGraph.h>
#include <vtkVariant.h>
#include <vtkVariantArray.h>

int main(int, char *[])
{
   vtkSmartPointer<vtkDenseArray<double> > array =
    vtkSmartPointer<vtkDenseArray<double> >::New();

  array->Resize(3,3);

  // Indicate that nodes 0 and 1 are connected, 0 and 2 are connected, and 1 and 2 are connected (form a fully connected set of 3 nodes)
  array->SetValue(0, 1, 10);
  array->SetValue(0, 2, 15);
  array->SetValue(1, 2, 25);

  // Indicate that nothing else is connected (no self connections, etc.)
  array->SetValue(0, 0, 0);
  array->SetValue(1, 1, 0);
  array->SetValue(2, 2, 0);
  array->SetValue(1, 0, 0);
  array->SetValue(2, 0, 0);
  array->SetValue(2, 1, 0);

  vtkPrintMatrixFormat(std::cout, array.GetPointer());

  // Thes names must match the names specified to the vtkTableToGraph later.
  array->SetDimensionLabel(0, "row");
  array->SetDimensionLabel(1, "column");

  vtkSmartPointer<vtkArrayData> arrayData =
    vtkSmartPointer<vtkArrayData>::New();
  arrayData->AddArray(array);

  vtkSmartPointer<vtkAdjacencyMatrixToEdgeTable> adjacencyMatrixToEdgeTable =
    vtkSmartPointer<vtkAdjacencyMatrixToEdgeTable>::New();
  adjacencyMatrixToEdgeTable->SetInputData(arrayData);
  adjacencyMatrixToEdgeTable->Update();

  adjacencyMatrixToEdgeTable->GetOutput()->Dump();

  vtkSmartPointer<vtkTableToGraph> tableToGraph =
    vtkSmartPointer<vtkTableToGraph>::New();
  tableToGraph->SetInputConnection(adjacencyMatrixToEdgeTable->GetOutputPort());
  tableToGraph->AddLinkVertex("row");
  tableToGraph->AddLinkVertex("column");

  tableToGraph->AddLinkEdge("row", "column"); // Add the edges to the graph
  tableToGraph->Update();

  vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
    vtkSmartPointer<vtkGraphLayoutView>::New();
  graphLayoutView->AddRepresentationFromInput(tableToGraph->GetOutput());
  graphLayoutView->SetVertexLabelVisibility(true);
  graphLayoutView->SetEdgeLabelVisibility(true);
  graphLayoutView->SetEdgeLabelArrayName("value");
  graphLayoutView->ResetCamera();
  graphLayoutView->Render();

  graphLayoutView->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
