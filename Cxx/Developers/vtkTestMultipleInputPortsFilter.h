// .NAME vtkTestMultipleInputPortsFilter
// .SECTION Description
// vtkTestMultipleInputPortsFilter

#ifndef __vtkTestMultipleInputPortsFilter_h
#define __vtkTestMultipleInputPortsFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkTestMultipleInputPortsFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkTestMultipleInputPortsFilter,vtkPolyDataAlgorithm);
  static vtkTestMultipleInputPortsFilter *New();

protected:
  vtkTestMultipleInputPortsFilter();
  ~vtkTestMultipleInputPortsFilter(){}

  int FillInputPortInformation( int port, vtkInformation* info );
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestMultipleInputPortsFilter(const vtkTestMultipleInputPortsFilter&);  // Not implemented.
  void operator=(const vtkTestMultipleInputPortsFilter&);  // Not implemented.

};

#endif
