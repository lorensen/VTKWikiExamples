#ifndef __vtkTestProgressReportFilter_h
#define __vtkTestProgressReportFilter_h
 
#include "vtkPolyDataAlgorithm.h"
 
class vtkTestProgressReportFilter : public vtkPolyDataAlgorithm 
{
public:
  vtkTypeRevisionMacro(vtkTestProgressReportFilter,vtkAlgorithm);
 
  static vtkTestProgressReportFilter *New();
 
protected:
  vtkTestProgressReportFilter(){}
  ~vtkTestProgressReportFilter(){}
 
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
 
private:
  vtkTestProgressReportFilter(const vtkTestProgressReportFilter&);  // Not implemented.
  void operator=(const vtkTestProgressReportFilter&);  // Not implemented.
 
};
 
#endif
