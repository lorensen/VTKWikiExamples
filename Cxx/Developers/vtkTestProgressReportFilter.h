#ifndef __vtkTestProgressReportFilter_h
#define __vtkTestProgressReportFilter_h
 
#include "vtkPolyDataAlgorithm.h"
 
class vtkTestProgressReportFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkTestProgressReportFilter,vtkAlgorithm);
 
  static vtkTestProgressReportFilter *New();
 
protected:
  vtkTestProgressReportFilter(){}
  ~vtkTestProgressReportFilter(){}
 
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE;
 
private:
  vtkTestProgressReportFilter(const vtkTestProgressReportFilter&);  // Not implemented.
  void operator=(const vtkTestProgressReportFilter&);  // Not implemented.
 
};
 
#endif
