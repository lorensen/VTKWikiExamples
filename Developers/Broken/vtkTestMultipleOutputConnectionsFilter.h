// .NAME vtkTestMultipleOutputConnectionsFilter
// .SECTION Description
// vtkTestMultipleOutputConnectionsFilter

#ifndef __vtkTestMultipleOutputConnectionsFilter_h
#define __vtkTestMultipleOutputConnectionsFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkTestMultipleOutputConnectionsFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkTestMultipleOutputConnectionsFilter,vtkPolyDataAlgorithm);
  static vtkTestMultipleOutputConnectionsFilter *New();

protected:
  vtkTestMultipleOutputConnectionsFilter(){}
  ~vtkTestMultipleOutputConnectionsFilter(){}

  //int FillOutputPortInformation( int port, vtkInformation* info );
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  
int RequestDataObject(
  vtkInformation*,
  vtkInformationVector** inputVector ,
  vtkInformationVector* outputVector);
  
  
private:
  vtkTestMultipleOutputConnectionsFilter(const vtkTestMultipleOutputConnectionsFilter&);  // Not implemented.
  void operator=(const vtkTestMultipleOutputConnectionsFilter&);  // Not implemented.

};

#endif
