#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyDataNormals.h>
#include <string>

int main(int argc, char *argv[])
{
  // Parse command line arguments
  if(argc != 2)
    {
    std::cout << "Required arguments: Filename" << std::endl;
    return EXIT_FAILURE;
    }

  // Get filename from command line
  std::string filename = argv[1]; //first command line argument
	
  // Read the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader = 
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  std::cout << "Reading " << filename << std::endl;
  reader->SetFileName(filename.c_str());
  reader->Update();

  // Extract the polydata
  vtkSmartPointer<vtkPolyData> polydata =
    reader->GetOutput();

  // Get the number of points in the polydata
  vtkIdType idNumPointsInFile = polydata->GetNumberOfPoints();

  vtkSmartPointer<vtkDoubleArray> array = 
    vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetArray("Distances"));
	
  if(array)
    {
    for(int i = 0; i < idNumPointsInFile; i++)
      {
      std::cout << "Got array." << std::endl;
      double dist;
      dist = array->GetValue(i);
      /*
      //if the array held arrays instead of scalars, you would use this:		  
      double location[3];
      array->GetTupleValue(i, location);
      std::cout << "Location: " << Location[0] << ","  << Location[1] << "," << Location[2] << std::endl;
      */
      std::cout << "Distance: " << dist << std::endl;
      }
    }//end if(array)
  else
    {
    std::cout << "no array." << std::endl;
    }

  return EXIT_SUCCESS;
}
