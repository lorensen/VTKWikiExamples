#ifndef __vtkTestFilterSelfProgressFilter_h
#define __vtkTestFilterSelfProgressFilter_h
 
#include "vtkPolyDataAlgorithm.h"
 
class vtkTestFilterSelfProgressFilter : public vtkPolyDataAlgorithm 
{
public:
  static vtkTestFilterSelfProgressFilter *New();
  vtkTypeMacro(vtkTestFilterSelfProgressFilter,vtkAlgorithm);

protected:
  vtkTestFilterSelfProgressFilter();
  ~vtkTestFilterSelfProgressFilter() VTK_OVERRIDE {}
 
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) VTK_OVERRIDE; 
 
  static void ProgressFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);
  
private:
  vtkTestFilterSelfProgressFilter(const vtkTestFilterSelfProgressFilter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkTestFilterSelfProgressFilter&) VTK_DELETE_FUNCTION;
 
};

#endif
