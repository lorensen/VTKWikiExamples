#include <vtkSmartPointer.h>
#include <vtkCellData.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkTriangle.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataReader.h>
 
int main(int argc, char *argv[])
{
  if (argc < 2)
    {
    std::cerr << "Usage: " << argv[0] << " InputFileName(.vtp)" << std::endl;
    return EXIT_FAILURE;
    }
  //we will read Test.vtp
  std::string inputFilename = argv[1];
  
  //read the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader = 
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->Update();
	
  vtkPolyData* polydata = reader->GetOutput();
	
  vtkDoubleArray* triangleArea = vtkDoubleArray::SafeDownCast(polydata->GetCellData()->GetArray("TriangleArea"));
 
  std::cout << "Triangle area: " << triangleArea->GetValue(0) << std::endl;
  
  return EXIT_SUCCESS;
}
