#include <vtkPolyData.h>
#include <vtkImageData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkSmartPointer.h>
#include <vtkMath.h>
#include <vtkQuadric.h>
#include <vtkContourFilter.h>
#include <vtkSampleFunction.h>
 

  /* allocate memory for an nrow x ncol matrix */
  template<class TReal>
      TReal **create_matrix ( long nrow, long ncol )
{
  typedef TReal* TRealPointer;
  TReal **m = new TRealPointer[nrow];

  TReal* block = ( TReal* ) calloc ( nrow*ncol, sizeof ( TReal ) );
  m[0] = block;
  for ( int row = 1; row < nrow; ++row )
  {
    m[ row ] = &block[ row * ncol ];
  }
  return m;
}

  /* free a TReal matrix allocated with matrix() */
  template<class TReal>
      void free_matrix ( TReal **m )
{
  free ( m[0] );
  delete[] m;
}

int main (int argc, char *argv[])
{
  //create points
  /*
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0 ,0 ,0);
  points->InsertNextPoint(1.1 ,1 ,2);
  points->InsertNextPoint(-1,1 ,2);
  points->InsertNextPoint(1 ,-1,2);
  points->InsertNextPoint(-1,-1,2);
  points->InsertNextPoint(1 ,-1,2);
  points->InsertNextPoint(2 ,2 ,16);
  
  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
    */
  
  
  
  vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();
  
  vtkPolyData* polydata = Reader->GetOutput();
  
  vtkPoints* points = polydata->GetPoints();
  
  //fit a quadric surface
  int numberOfSamples = points->GetNumberOfPoints();
  int numberOfVariables = 6;
  double **x = create_matrix<double> (numberOfSamples, numberOfVariables);
  
  double **y = create_matrix<double> ( numberOfSamples, 1 );
  
  for(unsigned int i = 0; i < numberOfSamples; i++)
    {
    double p[3];
    points->GetPoint(i,p);

    x[i][0] = pow(p[0],2); //x^2
    x[i][1] = pow(p[1],2); //y^2
    x[i][2] = p[0] * p[1]; //x*y
    x[i][3] = p[0]; // x
    x[i][4] = p[1]; //y
    x[i][5] = 1; // constant
    //std::cout << x[i][0] << " " << x[i][1] << " " << x[i][2] << " " << x[i][3] << " " << x[i][4] << " " << x[i][5] << std::endl;
    y[i][0] = p[2]; //z

  }

  double **m = create_matrix<double> ( numberOfVariables, 1 );
    
  vtkMath::SolveLeastSquares(numberOfSamples, x, numberOfVariables, y, 1, m);
  
  std::cout << "Solution is: " << std::endl;
  for(unsigned int i = 0; i < numberOfVariables; i++)
    {
    std::cout << m[i][0] << " ";
    }
  
  std::cout << std::endl;
 
  vtkSmartPointer<vtkXMLPolyDataWriter> pointsWriter = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  pointsWriter->SetInput(polydata);
  pointsWriter->SetFileName("Points.vtp");
  pointsWriter->Write();
  
  // create the quadric function definition
  vtkSmartPointer<vtkQuadric> quadric = vtkSmartPointer<vtkQuadric>::New();
  quadric->SetCoefficients(m[0][0], m[1][0], 0, m[2][0], 0, 0, m[3][0], m[4][0], 0, m[5][0]);

  // sample the quadric function
  vtkSmartPointer<vtkSampleFunction> sample = vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(50,50,50);
  sample->SetImplicitFunction(quadric);
  double xmin = -5, xmax = 5, ymin = -5, ymax = 5, zmin = 0, zmax = 5;
  sample->SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);
  
  vtkSmartPointer<vtkContourFilter> contours = vtkSmartPointer<vtkContourFilter>::New();
  contours->SetInput(sample->GetOutput());
  contours->GenerateValues(1, 1.0, 1.0);

  vtkSmartPointer<vtkXMLPolyDataWriter> surfaceWriter = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  surfaceWriter->SetFileName("Quadratic.vtp");
  surfaceWriter->SetInput(contours->GetOutput());
  surfaceWriter->Write();  
  
  free_matrix(X);
  free_matrix(M);
  
  return 0;
}
